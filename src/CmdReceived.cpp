/* 
 * The MIT License
 * Copyright (c) 2014 Francisco Edno de Moura Rodrigues Filho
 */

#include <iostream>
#include <sstream>
#include <cstdlib>
#include "CmdReceived.h"

using namespace cmd;

/*----------CTOR | DTOR----------*/

CmdReceived::CmdReceived(std::string command, const char field_separator, const char cmd_separator, const char esc_character)
  :CmdBase(),
  validity_(false),
  field_separator_(field_separator),
  cmd_separator_(cmd_separator),
  esc_character_(esc_character) 
{ 
  int id = -1;

    if(command.size() > 0){

          command.resize(command.size() - 1); //resizes the command to skip the cmd_separator

          if(command.size() == 1){ //if after the resize the command size equals to 1, this means that we are dealing with an argument less command
            std::istringstream id_stream(command);
            if(id_stream >> id) { //verifies if the id is a valid one
              validity_ = true;
              CmdBase::setId(id);
            }
          }else if(command.size() == 0) validity_ = false; //if the command came only with the cmd separator, we faced a loss of data
          else
          {
            std::istringstream buf(command);
            std::string token;

            while(getline(buf, token, field_separator_)) //tokenize the command arguments.
            {
              args_.push(token);
            }

            buf.str("");
            buf.str(args_.front());  //gets the id
            args_.pop();

            id = atoi(buf.str().c_str());

            CmdBase::setId(id);

            validity_ = true;

        }//else

      }//if

}

CmdReceived::~CmdReceived()
{
}

/*----------PARSERS----------*/

bool CmdReceived::parseBool()
{
  bool arg;

  if(!args_.empty()){ //if the queue is not empty...
    std::istringstream buf(args_.front()); //input stream buffer initialized with the first element in the queue.
    args_.pop(); //pops the first element, so the next element in the queue is acessible.

    //extracts the argument, needs verification of validity, so that it can throw exceptions.
    buf >> arg;

    return arg;
  }
  else
  {
    //throw exception
    return true;
  }
}

void CmdReceived::parseBool(bool &arg)
{
  if(!args_.empty()){//if the queue is not empty...
    std::istringstream buf(args_.front()); //initialize the input stream with the first element of the queue!
    args_.pop(); //pops the first element, so the next element in the queue can be retrieved.

    buf >> arg; //extract the argument
  }
  else
  {
    //throw exception
  }
}

int CmdReceived::parseInt()
{
  int arg;

  if(!args_.empty()){ // if the queue is not empty...
    std::istringstream buf(args_.front()); //initialize the input stream buffer with the first element of the queue.
    args_.pop(); //pops the first element of the queue, so the next can be retrieved.

    //not that this needs to be checked, so exceptions may be thrown.
    buf >> arg; //extract the argument

    return arg;
  }
  else
  {
    //throw excpetion.
    return -1;
  }
}

void CmdReceived::parseInt(int &arg)
{
  if(!args_.empty()){ //if the queue is not empty
    std::istringstream buf(args_.front()); //initialize the input stream buffer with the first element of the queue
    args_.pop(); //pops the first element of the queue, so the next element can be retrieved.

    //this needs to be checked, to throw error exceptions!
    buf >> arg; //extracts the argument.
  }
  else
  {
    //throw exceptions
  }
}

char CmdReceived::parseChar()
{
  char arg;

  if(!args_.empty()){ //if the queue is not empty...
    std::istringstream buf(args_.front()); //initialize the input stream buffer with the first element of the queue.
    args_.pop(); //pops the first element, so the next can be retrieved.

    //not that this needs to be chekced, so that exceptions may be thrown
    buf >> arg; //extracts the argument from the input stream.

    return arg;
  }
  else
  {
    //throw exceptions
    return '0';
  }
}

void CmdReceived::parseChar(char &arg)
{
  if(!args_.empty()){ //if the queue is not empty...
    std::istringstream buf(args_.front()); //initialize the input stream with the first element of the queue.
    args_.pop(); //pops the first element, so the next can be retrieved.

    //not that this needs to be checked, so exceptions can be thrown.
    buf >> arg; //extracts the argument.
  }
  else
  {
    //throw exceptions.
  }
}

float CmdReceived::parseFloat()
{
  float arg;

  if(!args_.empty()){//if the queue is not empty...
    arg = (float) atof(args_.front().c_str()); //converts the first argument in the queue into a float.
    args_.pop(); //pops the first argument, so the next can be retrieved.

    return arg;
  }
  else
  {
    //throw exceptions.
    return -1.1;
  }
}

void CmdReceived::parseFloat(float &arg)
{
  if(!args_.empty()){ //if the queue is not empyt...
    arg = (float) atof(args_.front().c_str()); //converts the first element of the queue into a float.
    args_.pop(); //pops the first element of the queue, so the next can be retrieved
  }
  else
  {
    //throws exception.
  }
}

double CmdReceived::parseDouble()
{
  double arg;

  if(!args_.empty()){//if the queue is not empty...
    arg = atof(args_.front().c_str()); //converts the first argument in the queue into a float.
    args_.pop(); //pops the first argument, so the next can be retrieved.

    return arg;
  }
  else
  {
    //throw exceptions.
    return -1.1;
  }
}

void CmdReceived::parseDouble(double &arg)
{
  if(!args_.empty()){ //if the queue is not empyt...
    arg = atof(args_.front().c_str()); //converts the first element of the queue into a float.
    args_.pop(); //pops the first element of the queue, so the next can be retrieved
  }
  else
  {
    //throws exception.
  }
}

std::string CmdReceived::parseString()
{
  std::string arg = args_.front(); //grabs the first element of the queue.
  args_.pop(); //pops the first element, so the next can be retrieved.

  return arg;
}

void CmdReceived::parseString(std::string &arg)
{
  arg = args_.front();
  args_.pop();
}

/*----------UTILITY----------*/

bool CmdReceived::isValid()
{
  return validity_;
}

int CmdReceived::getNumArgs()
{
  return args_.size();
} 
