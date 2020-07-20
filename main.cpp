#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include "brute_force.h"
#include "main_lorentz.h"

std::mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());

#define loop while(true) 
//      Description
//      Asympthotic (already known)

#define WORST 0
#define RANDOM 1

    

void exec(){
    loop{
        std::string in;
        std::cout<<std::endl<<">>";
        std::cin>>in;
        std::cout<<"Main-Lorentz Result"<<std::endl;
        main_lorentz(in);
        std::cout<<"_______________________"<<std::endl;
        std::cout<<"Brute Force Result";
        brute_force(in);
    }
}


void test(int numtests, int stringsize, int CASE, int compchars = 2, bool printend = false){
    std::string test;
    if (CASE == WORST){
        //std::string worst = WORSTSTRING;
        std::string worsttest(stringsize,'a');
        test = worsttest;
    }
    else if (CASE == RANDOM){
        std::uniform_int_distribution<> randfill(65, (65 + compchars - 1));
        for (int i = 0; i < stringsize; ++i) {
            char ins = randfill(rng);
            test.push_back(ins);
        }
    }
    std::chrono::time_point<std::chrono::system_clock> start, end; 
    std::cout<<std::endl<<std::endl;
    std::cout<<"testing string: "<<test<<std::endl;
    std::cout<<"string size: "<<test.size();
    std::cout<<std::endl<<"_______________________"<<std::endl;
    start = std::chrono::system_clock::now(); 
    for (auto i=0; i <numtests; i++){
        main_lorentz(test);
    }
    end = std::chrono::system_clock::now(); 
    std::chrono::duration<double> elapsed_seconds = end - start; 
    std::cout<<"Main-Lorentz Result"<<std::endl<<"Avg running time ("<<numtests<<" tests): "<<(elapsed_seconds.count()*1000/numtests)<<"ms"<<std::endl;
    if (printend){std::cout<<"Found Substrings: "<<std::endl; main_lorentz(test,0,true);}
    std::cout<<std::endl<<"_______________________"<<std::endl;
    start = std::chrono::system_clock::now(); 
    for (auto i=0; i <numtests; i++){
        bf_algorithm(test);
    }
    end = std::chrono::system_clock::now(); 
    std::chrono::duration<double> elapsed_seconds2 = end - start; 
 
    std::cout<<"Brute Force Result"<<std::endl<<"Avg running time ("<<numtests<<" tests): "<<(elapsed_seconds2.count()*1000/numtests)<<"ms"<<std::endl;
    if (printend){std::cout<<"Found Substrings: "; brute_force(test);}
    std::cout<<std::endl<<std::endl;
}


int main(){
    //exec();

    test(100000, 5, WORST);
    test(100000, 10, WORST);
    test(100000, 50, WORST);
    test(10000, 100, WORST);
    test(1000, 250, WORST);
    test(1000, 500, WORST);
    test(1000, 750, WORST);
}
