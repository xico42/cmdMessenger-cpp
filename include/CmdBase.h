/*!
 * \file CmdBase.h
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
 * This provides a base interface for commands in this CmdMessenger C++ implementation.
 * Here, the empty class CmdEnd is also defined.
 *
 */

#ifndef CMD_BASE_H
#define CMD_BASE_H

/*!
 * An empyt class that indicates the end of a command
 */
class CmdEnd{};

/*!
 * Base class for commands (Send and Received commands).
 */
class CmdBase
{
  public:
    CmdBase(int id = 0);
    virtual ~CmdBase();

    void setId(int id);
    int getId() const;

  private:
    int id_;
};

#endif
