#file CMakeLists.txt

cmake_minimum_required(VERSION 2.6)

#Project Name
project( cmdMessenger-cpp )

#include
include_directories( ./include/ )

#executáveis
#add_executable( hello ./src/hello.cpp )
#add_executable( interbyte ./src/interbyte.cpp )
#add_executable( teste ./src/teste.cpp )
#add_executable( token ./src/token.cpp )
#add_executable( parse ./src/parser.cpp )
add_executable( led ./src/examples/led.cpp )
add_executable( sensor ./src/examples/sensor.cpp )

#bibliotecas
add_library(messenger SHARED ./src/CmdMessenger.cpp ./src/CmdBase.cpp ./src/CmdSend.cpp ./src/CmdReceived.cpp)
target_link_libraries(messenger serial)

#target_link_libraries( hello serial )
#target_link_libraries( interbyte serial )
#target_link_libraries( teste serial )
target_link_libraries( led messenger )
target_link_libraries( sensor messenger )

install(TARGETS messenger DESTINATION lib)
install(FILES include/CmdBase.h include/CmdMessenger.h include/CmdReceived.h include/CmdSend.h include/callback.h DESTINATION include/CmdMessenger)
