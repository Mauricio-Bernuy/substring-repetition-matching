
#include <string>
#include <vector>
#include <deque>
#include <iostream>
#include <stack>
#include <list>

using namespace std;


void REP(string x){
    int n = x.size();
    vector<int> E(n), D(n);
    vector<list<int>*> ECLASS, DCLASS;
    stack<int> NEWINDEX;

    ECLASS.resize(2*n, new list<int>);
    for (int k = 2*n; k > 0; --k){
        NEWINDEX.push(k);
    }

    // (1)
    DCLASS.resize(n, new list<int>);
    for (int i = 1; i < n; ++i){
        int j, k; j = 0;
        // check if xi occurs at j
        bool occurs = false;
        while(!occurs){
            if (ECLASS[j]->empty() && x[i] == x[ECLASS[j]->front()]){
                k = j;
                occurs = true;
            } else if (!ECLASS[j+1]->empty()){
                j++;
            } else break;
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

            }
        }
    }
}