#include <iostream>
#include <sstream>
#include <cstdlib>

using namespace std;

int main()
{
  istringstream is;  
  bool b;
  double d;
  float f;

  is.str("1");

  if(is >> b){
    cout << "deu certo\n";
  }
  else cout << "Não deu certo\n";

  std::string str("34.5");

  char *pEnd = 0;

  strtod(str.c_str(), &pEnd);

  if(!pEnd){
    cout << "apenas double\n";
  }
  else cout << "tem mais coisas: " << pEnd << (sizeof(pEnd)) << endl;

  return 0;

  
}
