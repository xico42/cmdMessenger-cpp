#include <iostream>
#include <algorithm>
#include <vector>

#include "CmdReceived.h"

using namespace std;

double func(int i)
{
  return static_cast<double>(i);
}

int main()
{
  std::vector<int> myint;
  myint.push_back(3);
  myint.push_back(5);

  std::vector<double> mydouble;

  mydouble.resize( myint.size() );

  cout << "transforming...\n";
  std::transform(myint.begin(), myint.end(), mydouble.begin(), func);

  cout << "contents of my double: ";
  for(unsigned long i = 0; i<mydouble.size(); i++){
    cout << mydouble[i] << " ";
  }

  cout << endl;

  cout << mydouble[0]/2 << endl;

  cout << "Starting new test...\n";

  std::vector<std::string> mystring;
  mystring.push_back("aff man");
  mystring.push_back("eita man");

  std::vector<cmd::CmdReceived> mycmd;

  mycmd.resize(mystring.size());

  std::transform(mystring.begin(), mystring.end(), mycmd.begin(), cmd::CmdReceived());

  cout << "Finished Transformation\n";

  for(unsigned long i = 0; i<mycmd.size(); i++){
  }

  return 0;
}
