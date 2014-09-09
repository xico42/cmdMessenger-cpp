#include "SerialTransport.h"

using namespace cmd;

/*----------INTERFACE----------*/

size_t SerialTransport::bytesAvailable() 
{
    return serial_port_.available();
}

size_t SerialTransport::read( uint8_t *data, size_t num_bytes )
{
    return serial_port_.read( data, num_bytes );
}

size_t SerialTransport::write( const uint8_t *data, size_t num_bytes )
{
    return serial_port_.write( data, num_bytes );
}

size_t SerialTransport::write( const std::string &data )
{
    return serial_port_.write(data);
}

void SerialTransport::open()
{
    serial_port_.open();
}

void SerialTransport::close()
{
    serial_port_.close();
}

bool SerialTransport::isOpen() const
{
    return serial_port_.isOpen();
}

void SerialTransport::setTimeout(int read_timeout_constant, int write_timeout_constant, int inter_byte_timeout, int read_timeout_multiplier, int write_timeout_multiplier)
{
    serial_port_.setTimeout(inter_byte_timeout, read_timeout_constant, read_timeout_multiplier, write_timeout_constant, write_timeout_multiplier);
}
