#include <iostream>
#include <cstdlib>
#include <signal.h>
#include "serial/serial.h"

using namespace std;

void printUsage();
void parser(int argc, char *argv[]);
void handler(int signum);

uint32_t baudrate = 9600, timeout = 1;
string port("/dev/ttyACM0");
string input("");
bool finish = false;

int main(int argc, char *argv[])
{
  if(argc < 2){
    printUsage();
    return 0;
  }

  parser(argc, argv);

  signal(SIGINT, handler);

  try
  {
    serial::Serial arduino(port, baudrate);
    arduino.setTimeout(timeout, 50000000, 0, 50000000, 0);

    cout << "Teste de timeout, com interbyte de " << timeout << "ms (ctrl-c para sair)" << endl;

    while(true)
    {
      size_t read = arduino.read(input, 65535);

      if(read > 0) cout << "eu li " << read << "bytes\n";

      if(finish) break;
    }
  }
  catch(exception &e)
  {
    cout << "Exceção: " << e.what() << endl;
  }

  return 0;
}

void handler(int signum)
{
  cout << "Sinal de saida recebido: " << signum << endl;
  finish = true;
}

void printUsage()
{
  cout << "Uso: interbyte <port> <baudrate> <timeout>" << endl;
}

void parser(int argc, char *argv[])
{
  if(argc == 2){
    port = argv[1];
  }else if(argc == 3){
    port = argv[1];
    baudrate = (uint32_t) atoi(argv[2]);
  }else if(argc == 4){
    port = argv[1];
    baudrate = (uint32_t) atoi(argv[2]);
    timeout = (uint32_t) atoi(argv[3]);
  }else{
    cout << "Erro, tente novamente" << endl;
    printUsage();
    exit(0);
  }
}
