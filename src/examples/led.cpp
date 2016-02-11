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
    cmd::CmdMessenger arduino(argv[1], 115200);
    cmd::Cmd led(ksetled);

    cmd::Timeout timeout = cmd::Timeout::simpleTimeout(1000);
    arduino.setTimeout(timeout);

    while(true)
    {
      cout << "'1' turns on, '0' turns off, 'q' quits: ";
      cin >> op;
      cout << endl;

      switch(op)
      {
        case '1':
          led << true << CmdEnd();
          arduino.send(led);

          cout << led.getNumArgs() << endl;
          led.clear();
          break;

        case '0':
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
    cout << "Usage: led 'port_name'\n";
  }

  return 0;
}
