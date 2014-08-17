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
 * This provides the interface of the class responsible to hold the incoming command and for parsing the arguments.  
 */

#ifndef CMD_RECEIVED_H
#define CMD_RECEIVED_H

#include <iostream>
#include <queue>

#include "CmdBase.h"

namespace cmd{

  class CmdReceived : public CmdBase
  {
    public:

      /*----------CTOR | DTOR----------*/

      CmdReceived(std::string command = "", 
          const char field_separator = ',', 
          const char cmd_separator = ';', 
          const char esc_character = '/'
          );

      virtual ~CmdReceived();

      /*----------PARSERS----------*/

      /*
       * Parses the next argument as a boolean.
       *
       * \return A bool representing the parsed argument.
       */
      bool parseBool();

      /*!
       * Parses the next argument as a bool.
       *
       * \param arg Reference of a bool to receive the parsed argument.
       */
      void parseBool(bool& arg);

      /*!
       * Parses the next argument as an integer.
       *
       * \return An integer representing the parsed argument.
       */
      int parseInt();

      /*!
       * Parses the next argument as an integer.
       *
       * \param arg Reference of an integer to receive the parsed argument.
       */
      void parseInt(int& arg);

      /*!
       * Parses the next argument as a character.
       *
       * \return A character representing the parsed argument.
       */
      char parseChar();

      /*!
       * Parses the next argument as a character.
       *
       * \param arg Reference of a character to receive the parsed argument.
       */
      void parseChar(char& arg);

      /*!
       * Parses the next argument as a float.
       *
       * \return A float representing the parsed argument.
       */
      float parseFloat();

      /*!
       * Parses the next argument as a float.
       *
       * \para arg Reference of a float to receive the parsed argument.
       */
      void parseFloat(float& arg);

      /*!
       * Parses the next argument as a double.
       *
       * \return A double representing the parsed argument.
       */
      double parseDouble();

      /*!
       * Parses the next argument as a double.
       *
       * \param arg Reference of a double to receive the parsed argument.
       */
      void parseDouble(double& arg);
      
      /*!
       * Parses the next argument as a String.
       *
       * \return A std::string representing the parsed argument.
       */
      std::string parseString();

      /*!
       * Parses the next argument as a String.
       *
       * \param arg Reference of a std::string to receive the parsed argument.
       */
      void parseString(std::string& arg);

      /*----------UTILITY----------*/

      /*!
       * Verifies the validity of the received command.
       *
       * \return A boolean. True if the command is valid and false otherwise.
       */
      bool isValid();

      /*!
       * Get the number of arguments left in the queue.
       *
       * \return An int representing the number of arguments left.
       */
      int getNumArgs();

    private:
      std::queue<std::string> args_; //holds the arguments to be processed.
      bool validity_; //says if this is a valid command or, if it is incomplete.

      char field_separator_;
      char cmd_separator_;
      char esc_character_;

      void setId(int id);
  };

}

#endif
