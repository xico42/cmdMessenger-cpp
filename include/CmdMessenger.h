/*!
 * \file CmdMessenger.h
 *
 * \author Rodrigues Filho
 * \version 0.1
 *
 * \section LICENSE
 *
 * The MIT License
 *
 * Copyright (c) 2014 Francisco Edno de Moura Rodrigues Filho
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be
 *  included in all copies or substantial portions of the Software.
 *   
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 *  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 *  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
 *  LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
 *  OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
 *  WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * \section DESCRIPTION
 * This provides a cross platform interface to use with the CmdMessenger messaging library. As transport layer the 
 * Serial Library, a cross-platform, simple to use library for using serial ports on computers by William Woodall (wjwwood@gmail.com) and John Harrison (ash@greaterthaninfinity.com), was chosen.
 * This is the main interface to use this CmdMessenger implementation.
 */

/*!
 * \todo Exceptions for parsing erros and empty queues
 * \todo Improve the parser to implement escaping (check how this was done in the arduino implementation).
 */

#ifndef CMD_MESSENGER_H
#define CMD_MESSENGER_H

#include <iostream>
#include <map>

#include "SerialTransport.h"

#include "callback.h"

#include "CmdSend.h"
#include "CmdReceived.h"

namespace cmd{

  typedef CmdSend Cmd;
  typedef CBFunctor1wRet<CmdReceived&, void> CallBackFunctor;
  typedef void (*CallBack)(CmdReceived&);

  class CmdMessenger
  {
    public:
      /*----------CTOR | DTOR---------- */

      /*!
       * Creates a CmdMessenger object and configures the serial port. If a port is not specified it might be set with a call to cmd::CmdMessenger::open
       *
       * \param port A std::string containing the name of the serial port to be used.
       *  -In windows systems it may look like this: COM1
       *  -In Unix systems it may look like this: /dev/ttyACM0
       *
       * \param field_separator A const char containing the field separator. It separates the arguments in a command to be sent or read.
       * \param cmd_separator A const char containing the command separator character. It defines the end of a command to be sent or read.
       * \param esc_character A const char containing the escape character. It defines the character usded to escape special characters in a command to be sent or read.
       *
       * \param baudrate An integer that defines that baudrate for the serial port.
       * \param timeout A serial::Timeout object that defines the reading and writing timeouts. This object is acessible through the cmd namespace.
       *  \see CmdMessenger::setTimeout
       * \param bytesize Size of each byte in the serial transmission of data, default is eightbits, possible values are: fivebits, sixbits, sevenbits, eightbits.
       * \param parity Method of parity, the default value is parity_none, possible values are: parity_odd, parity_even and parity_none.
       * \param stopbits Number of stopbits used, the default is stopbits_one, possible values are: stopbits_one, stopbits_two and stopbits_one_point_five.
       * \param flowcontrol Type of flowcontrol used, the default is flowcontrol_none, possible values are: flowcontrol_none, flowcontrol_hardware and flowcontrol_software.
       */

      explicit CmdMessenger( const char field_separator = ',', 
          const char cmd_separator = ';', 
          const char esc_character = '/'
          );

      /*!
       * Destructor
       */
      virtual ~CmdMessenger();

      /*----------CMD MESSENGER SPECIFIC----------*/

      /*!
       * Attaches a default callback for commands without a specific callback
       *
       * \param callback A function of type 'void func(CmdReceived&)'
       */
      void attach(CallBack callback);

      /*!
       * Attaches a class method as the default callback for commands without a specific callback.
       *
       * \param callback_method A method of type 'void func(CmdReceived&)'.
       * \param object_ref The object instance of the class.
       */
      template<typename T>
      void attach(void (T::*callback_method)(CmdReceived&), T& object_ref)
      {
          default_callback_ = makeFunctor((CallBackFunctor*)0, object_ref, callback_method);
      }

      /*!
       * Attaches a callback to a command.
       *
       * \param cmd_id Id of the command to attach a callback to.
       * \param callback Callback to attach.
       */
      void attach(int cmd_id, CallBack callback);

      /*!
       * Attaches a class method as a callback to a command.
       *
       * \param cmd_id Id of the command to attach a callback to.
       * \param callback_method A method to attach as a callback.
       * \param object_ref An instance of a object of the class.  
       */
      template<typename T>
      void attach(int cmd_id, void (T::*callback_method)(CmdReceived&), T& object_ref)
      {
          callbacks_[cmd_id] = makeFunctor((CallBackFunctor*)0, object_ref, callback_method);
      }

      /*!
       * Sends a command. If ack is desired, it will block till the specified command id is received or timeout is expired.
       *
       * \param command The command to be sent.
       * \param ack A boolean that defines if an ack will be required or not. If true, the function will wait for the ack.
       * \param ack_id The id of the ack command.
       * \param simple_timeout Simple timeout for the ack. If not specified, the timeout already set will be used. Note that this does not change the timeout already set.
       */
      bool send(const Cmd& command, bool ack=false, int ack_id = 0, int simple_timeout = -1); 

      /*!
       * Waits for an specific command. This is used mainly because some examples, in the official CmdMessenger for arduino, send a command in the setup() function when everything is ready. I 
       * noted that sometimes the serial port is opened before, or after, this message can be sent. Anyway, it used to bring some bugs into my test codes. This function
       * will not drop the commands read before the specified command, it will put them in a container and then, when a call to CmdMessenger::feedInSerialData is made, the specified
       * callbacks will be called.
       *
       * \param cmd_id The id of the command to be waited for.
       * \param simple_timeout Simple timeout to wait for the command. If not specified, the timeout already set will be used. Note that this does not change the timeout already set.
       */
      bool waitCmd(int cmd_id, int simple_timeout = -1);

      /*!
       * Feeds in the serial data. That means, the commands in the buffer will be read and callbacks are gonna be called.
       */
      void feedInSerialData();

      /*----------SETTERS AND GETTERS-------------*/

      /*!
       * Sets the field separator character, i.e., the character used to separate commands.
       *
       * \param field_separator A character that sets the field separator, the default value is: ','.
       */
      void setFieldSep(const char field_separator);

      /*!
       * Gets the field separator character used to separate arguments in a command
       *
       * \return A character that sets the field separator.     
       * 
       * \see CmdMessenger::setFieldSep
       */
      char getFieldSep() const;

      /*!
       * Sets the command separator, in other words, the character that defines the end of a command.
       *
       * \param cmd_separator A character that sets the command separator, the default value is ';'.
       */
      void setCmdSep(const char cmd_separator);

      /*!
       * Gets the command separator character used to define the end of a command.
       *
       * \return A character that sets the command separator.
       *
       * \see CmdMessenger::setCmdSep
       */
      char getCmdSep() const;

      /*!
       * Sets the escape character used to escape special characters (like the field and command separators).
       *
       * \param esc_character A character that sets the escape character, the defaul value is '/'.
       */
      void setEscChar(const char esc_character);

      /*!
       * Gets the escape character used to escape special characters.
       *
       * \return A character that sets the escape character.
       *
       * \see CmdMessenger::setEscChar
       */
      char getEscChar() const;

    private: 
      /*SERIAL PORT VARIABLES*/

      TransportLayer *serial_port_;

      std::ostringstream buf_;
      std::vector<uint8_t> raw_data_buf_;

      /*Cmd Messenger*/
      //protocol configurations
      char field_separator_; //character to separate arguments
      char cmd_separator_;   //character to finalize a command
      char esc_character_;   //character to escape special characters

      //Callback
      std::map<int, CallBackFunctor> callbacks_;
      CallBackFunctor default_callback_;
  }; // CmdMessenger class

} //end of namespace cmd

#endif
