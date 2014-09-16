#include <iostream>
#include "serial/serial.h"

using namespace serial;
using namespace std;

void func(Serial& port)
{
    cout << port.getPort() << endl;
}

class transport
{
    public:
    transport(Serial* port)
    {
        port_ = port;
    }

    void print()
    {
        cout << "Porta na classe: " << port_->getPort() << endl;
    }

    private:
    Serial *port_;
};

int main()
{
    Serial arduino;
    Serial *arduino2;

    arduino.setPort("Aff");

    func(arduino);

    cout << "Assignment...\n";

    arduino2 = &arduino;

    cout << arduino2->getPort() << endl;

    cout << "Com classes\n";

    transport teste(arduino2);
    teste.print();

    cout << arduino.available() << endl;

    return 0;
}
