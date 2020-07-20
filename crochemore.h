#include <string>
#include <vector>
#include <deque>
#include <iostream>
#include <stack>
#include <list>
#include <set>
#include <map>
#include <unordered_map>


using namespace std;

deque<tuple<int,int,int>*> REP(string x){
    int n = x.size() + 1; int p;
    vector<int> E(n), D(n);
    vector<list<int>*> ECLASS, DCLASS;
    stack<int> NEWINDEX;
    deque<tuple<int,int>*> QUEUE;
    deque<tuple<int,int,int>*> R;
    deque<int> SMALL; 
    set<int> SPLIT;
    unordered_map<int, list<int>*> SUBCLASS;
    unordered_map<int, int> LAST_SMALL;

    for (int k = 2*n; k != 0; --k){
        NEWINDEX.push(k);
        //nl(new list<int>); 
        ECLASS.push_back(new list<int>);
    }
    
    E[0] = 0; ECLASS[0]->push_back(0);

    // (1)
    for (int i = 1; i < n; ++i){
        int j, k; j = 0;
        // check if xi occurs at j
        bool occurs = false;
        while(!occurs){
            if (!ECLASS[j]->empty() && x[i] == x[ECLASS[j]->front()]){
                k = j;
                occurs = true;
            } else if (!ECLASS[j+1]->empty()){
                j++;
            } else 
                break;
        }
        if (!occurs){
            k = NEWINDEX.top();
            NEWINDEX.pop();
        }
        E[i] = k;
        ECLASS[k]->push_back(i);
        DCLASS.push_back(new list<int>);
    }

    // 
    for (int k = 0; k < 2*n; ++k){
        if (!ECLASS[k]->empty()){
            for (int i = 0; i < ECLASS[k]->size(); ++i){
                auto it = ECLASS[k]->begin();
                advance(it,i);
                int v = *it;
                it++;
                if ((i+1) < ECLASS[k]->size()){
                    auto dif = *it - v;
                    D[v] = dif;
                    DCLASS[dif]->push_back(v);
                }
                else{
                    D[v] = 0;
                    DCLASS[0]->push_back(v);
                }
            }
        }
        else break;
    }

    p = 1; R.clear();
    for(int i = 0; i < n; ++i){
        if (!ECLASS[i]->empty()) SMALL.push_back(i);
        else break;
    }

    // (2)
    while (!SMALL.empty()){        // COMPUTATION OF REPETITIONS
        LAST_SMALL.clear();
        QUEUE.clear();
        SUBCLASS.clear();
        SPLIT.clear();

        // (3) p length repetitions
        while(!DCLASS[p]->empty()){
            int i = DCLASS[p]->front();
            DCLASS[p]->pop_front();
            do{
                i = i + p;
            }
            while(D[i] == p);
            int e = 1;
            do{
                i = i - p; e++;
                R.push_back(new tuple<int,int,int> (make_tuple(i,p,e)));
                DCLASS[p]->remove(i);
            } while(i - p > 0 && D[i - p] == p);
        }
        
        // (4) increment p
        p++;
        if (p > n/2){
            return R;
        }
        
        // clases esmol
        while(!SMALL.empty()){
            int s = SMALL.front();
            SMALL.pop_front();
            auto it = ECLASS[s]->begin();
            while (it != ECLASS[s]->end()){
                int j = *it;
                if (j != 0){
                    QUEUE.push_back(new tuple<int,int> (make_tuple(j,s)));
                    int k = E[j - 1];
                    if (SPLIT.find(k) == SPLIT.end()){
                        SPLIT.insert(k);
                        SUBCLASS.insert({k, new list<int>({k})});
                        LAST_SMALL.insert({k,0});
                    }
                }
                it++;
            }
        }

        //5.2 one position at a time is transfered to a new class
        while(!QUEUE.empty()){
            auto curr = *(QUEUE.front());
            QUEUE.pop_front();
            int j = get<0>(curr); int s = get<1>(curr);
            int i = j - 1;
            int k = E[i];
            if(LAST_SMALL.at(k) != s){
                LAST_SMALL[k] = s;                
                SUBCLASS[k]->push_back(NEWINDEX.top());
                NEWINDEX.pop();
            }
            int kbar = SUBCLASS[k]->back();
            auto lit = ECLASS[k]->begin();
            while(*lit != i){
                lit++;
            }
            if(lit != ECLASS[k]->begin()){
                lit--;
                int iprime = *lit;
                DCLASS[D[iprime]]->remove(iprime);
                D[iprime] = D[iprime] + D[i];                 
                DCLASS[D[iprime]]->push_back(iprime);

            }
            ECLASS[k]->remove(i);
            ECLASS[kbar]->push_back(i);
            E[i] = kbar;
            DCLASS[D[i]]->remove(i);
            DCLASS[0]->push_back(i);
            D[i] = 0;

            auto liter = ECLASS[kbar]->begin();
            while(*liter != i){
                liter++;
            }
            if(liter != ECLASS[kbar]->begin()){
                liter--;
                int iprime = *liter;
                DCLASS[D[iprime]]->remove(iprime);
                int t = i - iprime;
                if(t < 0){
                    D[iprime] = 0; 
                } else {
                    D[iprime] = t;
                }              
                DCLASS[D[iprime]]->push_back(iprime);
            }            
        }
        
        // 6  claculate new value of small
        while(!SPLIT.empty()){
            auto sit = SPLIT.end();
            sit--;
            int k = *sit;
            SPLIT.erase(sit);
            if(ECLASS[k]->empty()){
                NEWINDEX.push(k);
                SUBCLASS[k]->remove(k);
            }
            auto lite = SUBCLASS[k]->begin();
            while(lite != SUBCLASS[k]->end()){
                SMALL.push_front(*lite);
                ++lite;
            }
        }
    }
}

void crochemore(string input, bool printing = 0){
    auto result = REP(input);
    if (!printing) return;
    for (auto it = result.begin(); it != result.end(); ++it){
        int i,p,e;
        i = get<0>(**it); p = get<1>(**it); e = get<2>(**it);
        cout<<'['<<i<<","<<p<<","<<e<<']';
        cout<<input.substr(i,p);
        cout<<endl;
    }
}