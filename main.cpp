#include <iostream>
#include <vector>
#include <string>
#include "brute_force.h"
#include "main_lorentz.h"


#define loop while(true) 
// todo TIMING TESTS
//      Description
//      Asympthotic (already known)
void exec(){
    loop{
        std::string in;
        std::cout<<std::endl<<">>";
        std::cin>>in;
    }
}

int main(){
    //exec();

    main_lorentz("ab12ab12");
    brute_force("abaaba");
}