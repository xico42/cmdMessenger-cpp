#include <iostream>
#include "serial/serial.h"

using namespace serial;
using namespace std;

void func(Serial& port)
{
    cout << port.getPort() << endl;
}

int main()
{
    Serial arduino;
    Serial *arduino2;

    arduino.setPort("Aff");

    func(arduino);

    cout << "Assignment...\n";

    arduino2 = &arduino;

    cout << arduino2->getPort() << endl;

    return 0;
}
