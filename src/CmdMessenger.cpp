/*!
 * \file CmdMessenger.cpp
 * \author Rodrigues Filho
 * \version 0.1
 *
 * \section LICENSE
 * \todo this license
 * 
 * \section Description
 * This file implements the main class of this project, the cmd::CmdMessenger class.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

#include "CmdSend.h"
#include "CmdMessenger.h"

using namespace cmd; 

/*----------CTOR | DTOR----------*/

CmdMessenger::CmdMessenger(const std::string &port,
    uint32_t baudrate,
    const char field_separator,
    const char cmd_separator,
    const char esc_character,
    Timeout timeout,
    bytesize_t bytesize,
    parity_t parity,
    stopbits_t stopbits,
    flowcontrol_t flowcontrol)
  :serial_port_(port, baudrate, timeout, bytesize, parity, stopbits, flowcontrol),
  field_separator_(field_separator),
  cmd_separator_(cmd_separator),
  esc_character_(esc_character)
{
  default_callback_ = 0;

  if(serial_port_.isOpen()) CmdMessenger::flush();
}

CmdMessenger::~CmdMessenger()
{
}

/*----------CMD MESSENGER SPECIFIC----------*/

bool CmdMessenger::send(const Cmd &command, bool ack, int ack_id, int simple_timeout)
{
  std::stringstream ss; //stream to hold the command to be sent.

  if(!command.getNumArgs()) 
    ss << command.getId() << cmd_separator_; // if there are no arguments to be sent, the stream receives only the command id and the command separator.
  else
  {
    //otherwise, if there are some arguments, we will have to iterate over the std::vector args_    
    ss << command.getId() << field_separator_;    

    for(unsigned long i=0; i<command.args_.size() - 1; i++){ //Note that we go from i = 0, to i = args_.size() - 1, because after the last argument a cmd_separator must be added.
      ss << command.args_[i] << field_separator_; //adds an argument and the field separator to the stream.
    }

    ss << command.args_.back() << cmd_separator_; //finishes the command. Now it is ready to be sent.

  } // else

  serial_port_.write(ss.str()); //sends the command!
  
  if(ack){ // if ack is required 
    return CmdMessenger::waitCmd(ack_id, simple_timeout); //Verifies if the command arrived or not and returns true if received (false otherwise).
  } 

  return true; //if ack is not required, the function returns true anyway.
}

bool CmdMessenger::waitCmd(int cmd_id, int simple_timeout)
{
}

void CmdMessenger::attach(CallBack callback)
{
  default_callback_ = makeFunctor((CallBackFunctor*)0, callback);
}

void CmdMessenger::attach(int cmd_id, CallBack callback)
{
  callbacks_[cmd_id] = makeFunctor((CallBackFunctor*)0, callback);
}

void CmdMessenger::feedInSerialData()
{
    size_t num_bytes = serial_port_.available(); //get the number of bytes available in the port.
    std::string buf_str = buf_.str(); 
    uint8_t *raw_data = 0;
    size_t bytes_read = 0;

    raw_data = new uint8_t[num_bytes]; //allocate memory to hold the command
    bytes_read = serial_port_.read(raw_data, num_bytes); //read the serial port and get the number of bytes actually read.

    //convert the special character, so that it can be directly compared with the raw_data
    uint8_t cmd_separator = static_cast<uint8_t>(cmd_separator_);
    uint8_t esc_character = static_cast<uint8_t>(esc_character_);

    char last_buf_char = *buf_str.rbegin(); //last char of the old buffer. This is done so that we can check escaping.

    uint8_t byte_read;
    for(size_t i=0; i<bytes_read; i++){ //go over the pointer 

        byte_read = raw_data[i]; 
        
        if(i > 0){ // if this is not the first time in the loop
            if( byte_read == cmd_separator ){ //check if this is the cmd_separator
                if(raw_data[i-1] == esc_character){ //if the last byte is the escaping character, put it in the buffer
                    buf_ << (char) byte_read;
                }
                else
                {//if the last was not the escaping character...
                    //we faced the end of a command
                    buf_ << (char) byte_read;

                    //Once the command is completed, create the object to handle it!
                    CmdReceived command = CmdReceived(buf_.str(), field_separator_, cmd_separator_, esc_character_);

                    //Now, check if there is a callback attached to it.
                    if( callbacks_.count(command.getId()) ){
                        callbacks_[command.getId()](command); //If there's, call the callback.
                    }
                    else
                    {// If there's no callback, check if theres a default callback attached.
                        if(default_callback_) default_callback_(command);
                    } 

                    //std::cout << "command found: " << buf_.str();

                    buf_.str("");
                }
            }
            else
            {//if it is not the cmd_separator, it is a simple character. So put it on the buffer
                buf_ << (char) byte_read;
            }
        }
        else
        { // if this is the first time in the loop, we threat things a bit different, to check the old buffer.
                 if( byte_read == cmd_separator ){//check if this is the cmd_separator.
                     //check if the old buffer is empty. If it's, somethings wrong, so just ignore it.
                    if(!buf_str.empty()){ 
                        if(last_buf_char == esc_character) buf_ << (char) byte_read; //if the last buf char is a escaping character, escape it.
                        else
                        { //if the last char in the old buffer is not a escaping character, we faced the end of a command.
                            buf_ << (char) byte_read; 

                            //Create the CmdReceived object to handle the command.
                            CmdReceived command = CmdReceived(buf_.str(), field_separator_, cmd_separator_, esc_character_);

                            if( callbacks_.count(command.getId()) ){ //check if there is a callback.
                                callbacks_[command.getId()](command);
                            }
                            else
                            {//if there's no callback attached, call the default (if defined)
                                if(default_callback_) default_callback_(command);
                            }

                            //std::cout << "command found: " << buf_.str();

                            buf_.str("");
                        }
                    }
                }
                else
                {
                    buf_ << (char) byte_read;
                }        
        }

    }

    delete[] raw_data; //free the alocated memory

}
/*----------SERIAL SPECIFIC----------*/

//These methods simply call the methods in the serial::Serial serial_port_ object. For more information about each one
//refer to the serial::Serial documentation!

void CmdMessenger::open()
{
  serial_port_.open();
  CmdMessenger::flush();
}

bool CmdMessenger::isOpen() const
{
  return serial_port_.isOpen();
}

void CmdMessenger::close()
{
  serial_port_.close();
}

void CmdMessenger::flush()
{
    serial_port_.flushInput();
    serial_port_.flushOutput();
    serial_port_.flush();
}

/*----------SETTERS AND GETTERS----------*/

void CmdMessenger::setFieldSep(const char field_separator)
{
  field_separator_ = field_separator;
}

char CmdMessenger::getFieldSep() const
{
  return field_separator_;
}

void CmdMessenger::setCmdSep( const char cmd_separator )
{
  cmd_separator_ = cmd_separator;
}

char CmdMessenger::getCmdSep() const
{
  return cmd_separator_;
}

void CmdMessenger::setEscChar( const char esc_character )
{
  esc_character_ = esc_character;
}

char CmdMessenger::getEscChar() const
{
  return esc_character_;
}

void CmdMessenger::setPort(const std::string &port)
{
  serial_port_.setPort(port);
}

void CmdMessenger::setTimeout(Timeout &timeout)
{
  serial_port_.setTimeout(timeout);
}

void CmdMessenger::setTimeout(uint32_t inter_byte_timeout, uint32_t read_timeout_constant, uint32_t read_timeout_multiplier, uint32_t write_timeout_constant, uint32_t write_timeout_multiplier)
{
  serial_port_.setTimeout( inter_byte_timeout, read_timeout_constant, read_timeout_multiplier, write_timeout_constant, write_timeout_multiplier);
}

std::string CmdMessenger::getPort() const
{
  return serial_port_.getPort();
}

void CmdMessenger::setBaudRate(uint32_t baudrate)
{
  serial_port_.setBaudrate(baudrate);
}

uint32_t CmdMessenger::getBaudrate() const
{
  return serial_port_.getBaudrate();
}

void CmdMessenger::setByteSize(bytesize_t bytesize)
{
  serial_port_.setBytesize(bytesize);
}

bytesize_t CmdMessenger::getByteSize() const
{
  return serial_port_.getBytesize();
}

void CmdMessenger::setParity(parity_t parity)
{
  serial_port_.setParity(parity);
}

parity_t CmdMessenger::getParity() const
{
  return serial_port_.getParity();
}

void CmdMessenger::setStopBits(stopbits_t stopbits)
{
  serial_port_.setStopbits(stopbits);
}

stopbits_t CmdMessenger::getStopBits() const
{
  return serial_port_.getStopbits();
}

void CmdMessenger::setFlowControl(flowcontrol_t flowcontrol)
{
  serial_port_.setFlowcontrol(flowcontrol);
}

flowcontrol_t CmdMessenger::getFlowControl() const
{
  return serial_port_.getFlowcontrol();
} 
