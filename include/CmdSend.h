/*!
 * \file CmdReceived.h
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
 * This is the interface of the class that provides an easy interface for manipulating commands to be sent. It has the << operator overloaded, for simple addition of arguments in a command.
 * Note that to finish a command you should add as argument an instance of the CmdEnd class.
 */

#ifndef CMD_SEND_H
#define CMD_SEND_H

#include <iostream>
#include <sstream>
#include <vector>

#include "CmdBase.h"

namespace cmd{ 

  class CmdSend : public CmdBase
  {
    public:

      /*----------CTOR | DTOR----------*/
      CmdSend(int id = 0);
      virtual ~CmdSend();

      /*----------ARGUMENTS----------*/
      template <typename T>
      void add(T arg)
      {
        if(state_){
          std::stringstream ss;
          ss << arg;
          args_.push_back(arg);
        }
      }

      void add(CmdEnd end);

      template <typename T>
      CmdSend& operator<<(T arg)
      {
        if(state_){
          std::stringstream ss;
          ss << arg;
          args_.push_back(ss.str());
        } 
        return *this;
      }

      void operator<<(CmdEnd end);

      void clear();

      /*----------GETTERS----------*/

      /*!
       * Gets the state of the command.
       *
       * \return A bool that represents the state. True if the command is ready to be sent and false if it is not.
       */
      bool getState() const; 
      int getNumArgs() const;

    private:
      std::vector<std::string> args_;
      bool state_;

      //setting the CmdMessenger as friend,
      //allows a CmdMessenger object to acces the std::vector<std::string> args_ directly.
      friend class CmdMessenger;
  }; 

}

#endif
