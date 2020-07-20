#include <iostream>
#include <vector>
#include <string>
#include <chrono>
#include <random>
#include <fstream>
#include <bitset>
#include "brute_force.h"
#include "main_lorentz.h"
#include "crochemore.h"
#include "FSX10.h"

std::mt19937 rng(std::chrono::high_resolution_clock::now().time_since_epoch().count());

#define loop while(true) 
//      Description
//      Asympthotic (already known)

#define WORST 0
#define RANDOM 1
#define FIBONACCI 2

int fibo(int n){
    if(n<=1)
        return n;
    return fibo(n-1)+fibo(n-2);
}

std::string getFiboString(int num){
    int m=0;
    std::string result="";
    std::string binary;
    for(int i; i <= num; i++){
        binary = std::bitset<8>(fibo(m)).to_string();
        m++;
        result += binary;
    }
    return result;
}

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
    if(CASE == FIBONACCI){
        test = getFiboString(stringsize);
    }


    std::chrono::time_point<std::chrono::system_clock> start, end; 
    std::cout<<std::endl<<std::endl;
    std::cout<<"testing string: "<<test<<std::endl;
    std::cout<<"string size: "<<test.size();
    std::cout<<std::endl<<"_______________________"<<std::endl;

    // Main Lorentz test //
    start = std::chrono::system_clock::now(); 
    for (auto i=0; i <numtests; i++){
        main_lorentz(test);
    }
    end = std::chrono::system_clock::now(); 
    std::chrono::duration<double> elapsed_seconds = end - start; 

    float lorentz_avg = (elapsed_seconds.count()*1000/numtests);

    std::cout<<"Main-Lorentz Result"<<std::endl<<"Avg running time ("<<numtests<<" tests): "<<lorentz_avg<<"ms"<<std::endl;
    if (printend){std::cout<<"Found Substrings: "<<std::endl; main_lorentz(test,0,true);}
    std::cout<<std::endl<<"_______________________"<<std::endl;
    // Crochemore test //
    start = std::chrono::system_clock::now(); 
    for (auto i=0; i <numtests; i++){
        FSX10(test);
    }
    end = std::chrono::system_clock::now(); 
    std::chrono::duration<double> elapsed_seconds1 = end - start;

    float croch_avg = (elapsed_seconds1.count()*1000/numtests);

    std::cout<<"FSX10/Crochemore Result"<<std::endl<<"Avg running time ("<<numtests<<" tests): "<<croch_avg<<"ms"<<std::endl;
    if (printend){std::cout<<"Found Substrings: "<<std::endl; FSX10(test,true);}
    std::cout<<std::endl<<"_______________________"<<std::endl;
    
    //BF test//

    start = std::chrono::system_clock::now(); 
    for (auto i=0; i <numtests; i++){
        bf_algorithm(test);
    }
    end = std::chrono::system_clock::now(); 
    std::chrono::duration<double> elapsed_seconds2 = end - start; 

    float brute_avg = (elapsed_seconds2.count()*1000/numtests);

    std::cout<<"Brute Force Result"<<std::endl<<"Avg running time ("<<numtests<<" tests): "<<brute_avg<<"ms"<<std::endl;
    if (printend){std::cout<<"Found Substrings: "; brute_force(test);}
    std::cout<<std::endl<<std::endl;
    //write on table
    std::ofstream file("fibo_result.csv", ios_base::app);
    file << brute_avg << ", " << lorentz_avg << ", " << croch_avg << "\n"; 

}


int main(){
    //exec();
    int tst = 10;
    test(tst, 5, WORST);
    test(tst, 10, WORST);





    //string test = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaasasasaaaaaaaaaaa";

    //FSX10((char*)test.c_str()); 

    /*while (true)
        crochemore("aaaaaaaaaa");

    string test = "aaaaaaaaaaaaaaa";
    int numtests = 1000;
    std::chrono::time_point<std::chrono::system_clock> start, end; 
     start = std::chrono::system_clock::now(); 
    for (auto i=0; i <numtests; i++){
        REP(test);
    }
    end = std::chrono::system_clock::now(); 
    std::chrono::duration<double> elapsed_seconds1 = end - start; 
    std::cout<<"Crochemore Result"<<std::endl<<"Avg running time ("<<numtests<<" tests): "<<(elapsed_seconds1.count()*1000/numtests)<<"ms"<<std::endl;
    std::cout<<std::endl<<"_______________________"<<std::endl;
    */
}
