#include <sstream>
#include <iostream>
#include <vector>

using namespace std;

int main() {
    vector<string> strings;
    std::string str = "denmark,sweden,india,us;";
    if(str.size() > 0) str.resize( str.size() - 1);
    istringstream f(str);
    string s;    
    while (getline(f, s, ',')) {
        cout << s << endl;
        strings.push_back(s);
    }
}
