#include "SerialTransport.h"

using namespace cmd;

/*----------INTERFACE----------*/

size_t SerialTransport::bytesAvailable() const
{
    return serial_port_.available();
}
