#include <iostream>
#include "opencv2/core/core.hpp"
#include "serial/serial.h"
#include <signal.h>

using namespace std;

bool finish = false;

void handler(int signum)
{
  cout << "\nSinal recebido: " << signum << endl;
  finish = true;
}

int main()
{ 
  signal(SIGINT, handler);

  try
  {
    serial::Serial arduino("/dev/ttyACM0", 9600); 
    string input;

    arduino.setTimeout(1, 100, 0, 100, 0);

    arduino.flush();
    arduino.flushInput();
    arduino.flushOutput();

    cout << "Digite uma string para ser enviada ao arduino: (q para sair)" << endl;

    while(true)
    { 
    cout << "--> ";
    getline(cin, input);

    if(input.length() == 1){
      if(input[0] == 'q') break;
    }

    arduino.write(input);
    }

    cout << "Saindo... Entrando no modo de leitura (EOF para finalizar)" << endl;

    while(true)
    {
      size_t numBytes = arduino.available();

      if(numBytes > 0){
        input = arduino.read(numBytes);
        cout << input;
      }
      if(finish) break;
    }

    finish = false;

    cout << "Saindo... Testando o controle de timeout com 500ms (Leitura de string grande)" << endl;

    arduino.setTimeout(5, 5000000, 0, 50000000, 0);

    while(true)
    {
      size_t read = arduino.read(input, 65535);

      if(read > 0) cout << "li " << read << " bytes" << endl;

      if(finish) break;
    }

  }
  catch(exception &e)
  {
    cout << "Exception: " << e.what() << endl;
  }

  return 0;
}
