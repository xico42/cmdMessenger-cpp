#ifndef TRANSPORT_LAYER_H
#define TRANSPORT_LAYER_H

#include <cstddef>

using std::size_t;

class TransportLayer
{
    public:
        TransportLayer();
        virtual ~TransportLayer();

        virtual size_t bytesAvailable() = 0;
        virtual void read(unsigned char* data, size_t num_bytes) = 0;
        virtual void write(const unsigned char* data) = 0;
};

#endif
