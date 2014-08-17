#include <iostream>

#include "CmdMessenger.h"

using namespace std;

enum
{
  ksetled
};

int main(int argc, char *argv[])
{
  if(argc == 2){

    char op;
    cmd::CmdMessenger arduino(argv[1], 9600);
    cmd::Cmd led(ksetled);

    cmd::Timeout timeout = cmd::Timeout::simpleTimeout(1000);
    arduino.setTimeout(timeout);

    while(true)
    {
      cout << "'l' liga, 'd' desliga, 'q' sai: ";
      cin >> op;
      cout << endl;

      switch(op)
      {
        case 'l':
          led << true << CmdEnd();
          arduino.send(led);
          led.clear();
          break;

        case 'd':
          led << false << CmdEnd();
          arduino.send(led);
          led.clear();
          break;

        case 'q':
          break;
      }

      if(op == 'q') break;

      cout << "feeding in serial data\n";

      arduino.feedInSerialData();

    }

  }
  else
  {
    cout << "Uso: led 'port'\n";
  }

  return 0;
}

//! \endcode
