#include <iostream>
#include "CmdMessenger.h"

using namespace std;
using namespace serial;

class Oi
{
    public:
        oi(){}
        
        void cb(cmd::CmdReceived& m){}
};

int main(int argc, char *argv[])
{
    cmd::CmdMessenger oi;
    Oi haha;

    oi.teste(haha, &Oi::cb);
    return 0;
}
