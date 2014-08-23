#ifndef SERIAL_TRANSPORT_H
#define SERIAL_TRANSPORT_H

#include "TransportLayer.h"
#include "serial/serial.h"

namespace cmd{

  using std::invalid_argument;

  using serial::IOException;
  using serial::SerialException;
  using serial::PortNotOpenedException;

  using serial::Timeout;

  //using bytesize_t enum
  using serial::bytesize_t;
  using serial::fivebits;
  using serial::sixbits;
  using serial::sevenbits;
  using serial::eightbits;

  //using flowcontrol_t enum
  using serial::flowcontrol_t;
  using serial::flowcontrol_none;
  using serial::flowcontrol_software;
  using serial::flowcontrol_hardware;

  //using parity_t enum
  using serial::parity_t;
  using serial::parity_none;
  using serial::parity_odd;
  using serial::parity_even;

  //using stopbits_t enum
  using serial::stopbits_t;
  using serial::stopbits_one;
  using serial::stopbits_two;
  using serial::stopbits_one_point_five;


class SerialTransport : public TransportLayer
{
    public:
        SerialTransport();
        virtual ~SerialTransport();

      /*----------INTERFACE----------*/

        size_t bytesAvailable() const;
        void read(unsigned char *data, size_t num_bytes);
        void write(const unsigned char *data);
        void setTimeout(int read_timeout_constant, int write_timeout_constant, int inter_byte_timeout=0, int read_timeout_multiplier=0, int write_timeout_multiplier=0);

      /*!
       * Opens the serial port, as long as it is set and not already opened.
       *
       * \throw std::invalid_argument
       * \throw serial::SerialException
       * \throw serial::IOException
       */
      void open();

      /*
       * Gets the open status of the serial port.
       *
       * \return True if already opened and false otherwise.
       */
      bool isOpen() const;

      /*!
       * Closes the serial port
       */
      void close();

      /*----------SERIAL SPECIFIC----------*/



      /*----------SETTERS AND GETTERS----------*/
      /*!
       * Sets the serial port for communication.
       *
       * \param port A std::string representing the serial port. It may look something like this:
       *  - In Linux: "/dev/ttyACM0"
       *  - In Windows: "COM1"
       */
      void setPort(const std::string &port);

      /*!
       * Gets the port set for the serial communication.
       *
       * \return A std::string representing the serial port.
       *
       * \throw std::invalid_argument
       */
      std::string getPort() const;

      void setTimeout(Timeout &timeout);
      Timeout getTimeout() const;

      /*!
       * Sets the baudrate for the data transmission in the port.
       *
       * Possible baudrates depends on the system, but some safe baudrates (for arduino as an example) include: 300, 1200, 2400, 4800, 9600, 19200, 57600, 115200.
       *
       * \param baudrate An integer that sets the baudrate.
       */
      void setBaudRate(uint32_t baudrate);
      uint32_t getBaudrate() const;

      void setByteSize(bytesize_t bytesize);
      bytesize_t getByteSize() const;

      void setParity(parity_t parity);
      parity_t getParity() const;

      void setStopBits(stopbits_t stopbits);
      stopbits_t getStopBits() const;

      void setFlowControl(flowcontrol_t flowcontrol);
      flowcontrol_t getFlowControl() const;

    private:
        serial::Serial serial_port_;

}; //end of class

}//end of cmd namespace

#endif
