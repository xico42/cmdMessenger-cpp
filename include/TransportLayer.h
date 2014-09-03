#ifndef TRANSPORT_LAYER_H
#define TRANSPORT_LAYER_H

#include <cstddef>
#include <string>

#include "v8stdint.h"

using std::size_t;

/*!
 * Pure abstract class, or interface, that provides
 * abstraction of transport layer into CmdMessenger.
 */
class TransportLayer
{
    public:
        TransportLayer(){}
        virtual ~TransportLayer(){}

        virtual size_t bytesAvailable() const = 0 ;
        virtual size_t read(uint8_t* data, size_t num_bytes) = 0;
        virtual size_t write(const uint8_t* data, size_t num_bytes) = 0;
        virtual size_t write(const std::string &data) = 0;
        virtual void open()=0;
        virtual void close()=0;
        virtual bool isOpen() const =0;
        virtual void setTimeout(int read_timeout_constant, int write_timeout_constant, int inter_byte_timeout=0, int read_timeout_multiplier=0, int write_timeout_multiplier=0)=0;
};

#endif
