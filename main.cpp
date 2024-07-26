// Project Identifier: 50EB44D3F029ED934858FFFCEAC3547C68768FC9
#include "letter.cpp"
using namespace std;

int main(int argc, char * argv[]){
    lettermanClass lett;
    lett.getOpt(argc, argv);
    lett.read();
    lett.search();
    lett.output();
    return 0;
}