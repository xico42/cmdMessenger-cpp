#include <iostream>
#include "CmdMessenger.h"

using namespace std;

enum
{
    ksensor_nt,
    ksensor_st
};

void callback_nt(cmd::CmdReceived& command)
{
    cout << "\n---Command received: " << command.getId() << " Distance: " << command.parseInt() << endl;
}

void callback_st(cmd::CmdReceived& command)
{
    cout << "\n---Command received: " << command.getId() << " Distance: " << command.parseInt() << endl;
}

void default_cb(cmd::CmdReceived& command)
{
    cout << "\n---Command without callback: " << command.getId() << endl;
}

int main()
{
    cmd::CmdMessenger arduino("/dev/ttyACM0", 9600);
    arduino.attach(ksensor_nt, callback_nt);
    arduino.attach(ksensor_st, callback_st);
    arduino.attach(default_cb);
    while(true)
    {
            arduino.feedInSerialData();
    }
    return 0;
}

