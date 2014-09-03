#file CMakeLists.txt

cmake_minimum_required(VERSION 2.6)

#Project Name
project( cmdMessenger-cpp )

#include
include_directories( ./include/ )

#executáveis
#add_executable( led ./src/examples/led.cpp )
#add_executable( sensor ./src/examples/sensor.cpp )

add_executable( tst ./src/tst.cpp )

#bibliotecas
add_library(messenger SHARED ./src/CmdMessenger.cpp ./src/CmdBase.cpp ./src/CmdSend.cpp ./src/CmdReceived.cpp)
add_library(serial_transport SHARED ./src/SerialTransport.cpp)
target_link_libraries(messenger serial)

#target_link_libraries( led messenger )
#target_link_libraries( sensor messenger )
target_link_libraries( tst serial )

install(TARGETS messenger serial_transport DESTINATION lib)
install(FILES include/CmdBase.h include/CmdMessenger.h include/CmdReceived.h include/CmdSend.h include/callback.h include/TransportLayer.h include/SerialTransport.h DESTINATION include/CmdMessenger)
