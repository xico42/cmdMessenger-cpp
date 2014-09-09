#ifndef TRANSPORT_LAYER_H
#define TRANSPORT_LAYER_H

#include <cstddef>
#include <string>

#include "v8stdint.h"

using std::size_t;

/*!
 * Pure abstract class, or interface, that provides
 * abstraction of transport layer into CmdMessenger. To add a new transport layer
 * simply inherit this class and implement it.
 *
 * The implementations should include all necessary settings of the transport, and before
 * passing any object to CmdMessenger, the transport layer must be fully configured already.
 */
class TransportLayer
{
    public:
        virtual ~TransportLayer(){}

        /*!
         * Pure virtual method. It should return the number of bytes
         * available, in some buffer, to be read by CmdMessenger.
         */
        virtual size_t bytesAvailable() = 0 ;

        /*!
         * Pure virtual method. The implementation should receive a pointer to the data
         * the number of bytes desired for the reading, allocate the vector, assign the data
         * and return the number of bytes actually read.
         *
         * \return a size_t indicating the number of bytes read.
         */
        virtual size_t read(uint8_t* data, size_t num_bytes) = 0;

        /*!
         * The implmentation of this pure virtual method should receive as argument a 
         * pointer, and number of bytes to write in the transport layer from the data passed.
         *
         * \return The number of bytes written
         */
        virtual size_t write(const uint8_t* data, size_t num_bytes) = 0;

        /*!
         * The implementation of this method should receive an string, containing data
         * to write, write the data and return the number of bytes written.
         */
        virtual size_t write(const std::string &data) = 0;

        /*!
         * This method should open the transport layer. Open the transport layer means
         * prepare it for communication and store the incoming data in some sort of buffer
         */
        virtual void open()=0;

        /*!
         * Closes the transport layer, that is, finishes the communication.
         */
        virtual void close()=0;

        /*!
         * The implementation should check if the transport layer is already opened
         * and return the result.
         *
         * \return True if already opened and false otherwise.
         */
        virtual bool isOpen() const =0;

        /*!
         * Sets the timeout for incoming and outcoming data. When timed out, the write
         * and read methods should return, even if the process is not completed,
         * with the number of bytes read or written.
         *
         * This style of timeout setting is inherited from the Serial Library. IT
         * allow a more accuate control of data flow, rather than setting simple
         * timeouts.
         */
        virtual void setTimeout(int read_timeout_constant, int write_timeout_constant, int inter_byte_timeout=0, int read_timeout_multiplier=0, int write_timeout_multiplier=0)=0;
};

#endif
