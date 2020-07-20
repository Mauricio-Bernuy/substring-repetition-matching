/*#include <iostream>
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
}*/


/*
 * I verify that I am the sole author of this code, 
 * except where explicitly stated to the contrary.
 * This code is based on the pseudocode in the paper, 
 * An optimal algorithm for computing the repetitions in a word - M. Crochemore
 */
/* 
 * File:   main.cpp
 * Author: ivaylo
 *
 * Created on 15 March 2017, 23:39
 */

#include <cstdlib>
#include <string.h>
#include <stdio.h>
#include <list>
#include <stack>
#include <vector>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <memory>
#include <algorithm>
#include <ostream>
#include <omp.h>
#include <chrono>
#include <iostream>

using namespace std;

//print contents of reps
void printDV(deque< shared_ptr< vector< int > > > o){
    for(int i = 0; i < o.size(); ++ i){
        if(!o[i]->empty()){
            vector<int>::iterator vit = o[i]->begin();
            printf("(");
            while(vit != o[i]->end()){
                printf("%d",*vit);
                vit++;
                if(vit != o[i]->end()){
                    printf(",");
                }
            }
            printf(")\n");
        }
    }
}

/* input: string of character
 * An optimal algorithm for computing the repetitions in a word
 * as proposed by Max. Crochemore
 * O(n log n) time
 * output: repetitions printed to std out
 */
void ikrep(char const * input){
    
    // 1    
    static int n,twon,p; // length of input, twice length, recursion level
    n = strlen(input);
    twon = n*2;
    // for each position gieves index of e-class, for each position gives 
    // index of d-class 
    int E[n], D[n]; 
    // for e-class index the positions in that e-class, for d-class index the
    // positions in that d-class
    vector< shared_ptr< list< int > > > eClass, dClass; 
    list<int>::iterator lit;
    
    stack<int> nI; // contains available indicies of e-classes    
    // init eClass and nI
    eClass.reserve(twon);
    for(int k = twon; k != 0; --k){
        nI.push(k);   
        shared_ptr< list<int> > nl(new list<int>); 
        eClass.push_back(nl);
    }    
    E[0] = 0;
    eClass[0]->push_back(0);
    
    // calculate E, update eClass, init dClass 
    dClass.reserve(n);    
    for(int i = 1; i < n; ++i){
        int j,k;
        j = 0;
        bool placed = false;
        while(!placed){
            if(eClass[j]->size() > 0 && input[i] == input[eClass[j]->front()]){
                k = j;
                placed = true;
            } else if(eClass[j + 1]->size() > 0){
                j++;
            } else{
                break;
            } 
        }
        if(!placed){
            k = nI.top();
            nI.pop();
        }
        E[i] = k;
        eClass[k]->push_back(i);        
        shared_ptr< list<int> > nl(new list<int>);
        dClass.push_back(nl);
    }

    // calculate D, update dDclass
    for(int k = 0; k < twon; ++k){
        if(eClass[k]->size() > 0){
            for(int i = 0; i < eClass[k]->size(); ++i){
                lit = eClass[k]->begin();
                advance(lit,i);
                int y = *lit;    
                lit++;
                if((i + 1) < eClass[k]->size()){
                    int diff = *lit - y;
                    D[y] = diff;
                    dClass[diff]->push_back(y); 
                } else {
                    D[y] = 0;
                    dClass[0]->push_back(y);
                }
                
            }

        }
        else{
            break;
        }
    }
    
    //init p
    p = 1;
    
    //queue of small classes
    deque<int> smcl;  
    deque<int>::iterator dit;
    //list of repetitions
    deque< shared_ptr< vector< int > > > reps; 
    
    //init small
    for(int i = 0; i < n; ++i){
        if(eClass[i]->size() > 0){
            smcl.push_back(i);
        } else {
            break;
        }
    }
    
    //2     
    while(!smcl.empty()){        
        //3 finding repetitions of length p
        while(!dClass[p]->empty()){
            int i = dClass[p]->front();
            dClass[p]->pop_front();
            do{
                i = i + p;
            } while(D[i] == p);
            int e = 1;
            do{
                i = i - p;
                e++;
                shared_ptr< vector<int> > nv(new vector<int>);
                nv->push_back(i);
                nv->push_back(p);
                nv->push_back(e);
                reps.push_back(nv);
                dClass[p]->remove(i);
            }while(i - p > 0 && D[i - p] == p);
        }
        //4 increment p
        p = p + 1;
        if(p > n/2){
            printf("Number of Repetitions: %li \n",reps.size());
            printDV(reps);            
            printf("MISSION COMPLETE\n");
            break;
        }
        //5.1 copy small classes to queue
        //queue of all indicies of eclasses in preserved increasing order
        deque< shared_ptr< vector< int > > > queue;
        //set of eclasses, used in 6.
        set<int> split;
        set<int>::iterator sit;
        //for each eclass in split a list of subclass indicies
        unordered_map<int, shared_ptr< list<int> > > subClass;
        //for each eclass k in split the last eclass used to split k 
        unordered_map<int,int> lS; 
        while(!smcl.empty()){
            int s = smcl.front();
            smcl.pop_front();
            lit = eClass[s]->begin();
            while(lit != eClass[s]->end()){
                int j = *lit;
                if(j != 0){
                    shared_ptr< vector<int> > nv(new vector<int>);
                    nv->push_back(j);
                    nv->push_back(s);
                    queue.push_back(nv);
                    int k = E[j - 1];
                    if(split.find(k) == split.end()){
                        split.insert(k);
                        shared_ptr< list<int> > nl(new list<int>);
                        nl->push_back(k);
                        subClass.insert({k,nl});
                        lS.insert({k,0});
                    }
                }
                lit++;
            }
        }
        
        //5.2 one position at a time is transfered to a new class    
        while(!queue.empty()){
            vector<int> curr = *(queue.front());
            queue.pop_front();
            int j = curr[0];
            int s = curr[1];
            int i = j - 1;
            int k = E[i];
            if(lS.at(k) != s){
                lS[k] = s;                
                subClass[k]->push_back(nI.top());
                nI.pop();
            }
            int kbar = subClass[k]->back();
            lit = eClass[k]->begin();
            while(*lit != i){
                lit++;
            }
            if(lit != eClass[k]->begin()){
                lit--;
                int iprime = *lit;
                dClass[D[iprime]]->remove(iprime);
                D[iprime] = D[iprime] + D[i];                 
                dClass[D[iprime]]->push_back(iprime);

            }
            eClass[k]->remove(i);
            eClass[kbar]->push_back(i);
            E[i] = kbar;
            dClass[D[i]]->remove(i);
            dClass[0]->push_back(i);
            D[i] = 0;

            lit = eClass[kbar]->begin();
            while(*lit != i){
                lit++;
            }
            if(lit != eClass[kbar]->begin()){
                lit--;
                int iprime = *lit;
                dClass[D[iprime]]->remove(iprime);
                int t = i - iprime;
                if(t < 0){
                    D[iprime] = 0; 
                } else {
                    D[iprime] = t;
                }              
                dClass[D[iprime]]->push_back(iprime);
            }            
        }        
        //6 calculate new value of small
        while(!split.empty()){  
            sit = split.end();
            sit--;
            int k = *sit;   
            split.erase(sit);
            if(eClass[k]->empty()){
                nI.push(k);
                subClass[k]->remove(k);                                    
            }            
            lit = subClass[k]->begin();               
            while(lit != subClass[k]->end()){    
                smcl.push_front(*lit);
                ++lit;                
            }            
        }         
    }
}

int main() {
    do{
    //check if input is nulll
    string input;
	cin>>input;
    input = input + '$';
    printf("%s\n",input.c_str());
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    ikrep(input.c_str());
    std::chrono::steady_clock::time_point endPar= std::chrono::steady_clock::now();
    std::cout << "Approach took: " << std::chrono::duration_cast<std::chrono::nanoseconds> (endPar - begin).count() <<std::endl;
    } while(1);
    return 0;
}