#include <iostream>

#include "CmdMessenger.h"
#include "SerialTransport.h"

using namespace std;

enum
{
  ksetled
};

int main(int argc, char *argv[])
{
  if(argc == 2){

    char op;
    cmd::SerialTransport *serial_port = new cmd::SerialTransport(argv[1], 9600);
    cmd::CmdMessenger arduino(serial_port);
    cmd::Cmd led(ksetled);

    serial_port->setTimeout(1000, 1000);

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
