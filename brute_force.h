#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> bf_algorithm(std::string input_string){
    std::vector<std::string> result;
    int n = input_string.size()-1;
    for (auto d = 0; d < n; d++){
        int j = n - d;
        int k = -1;  // 1st substring instance start
        int l = -1;  // 2nd substring instance start
        int m = 0;  // substring length
        for (auto i = 0; i <= d; i++){
            if (input_string[i] == input_string[j]){
                m++;
                if (k == -1){
                    // set starting point of a maximal repeated substring
                    k = i;
                    l = j;
                }
            }
            else if (k != -1){
                // end of a maximal repeated substring
                result.push_back(input_string.substr(k, m));
                k = -1;
                l = -1;
                m = 0;
            }
            j++;
        }
        if (k != -1){
            // end of a maximal repeated substring
            result.push_back(input_string.substr(k, m));
        }
    }
    return result;
}

void brute_force(std::string input){
    auto res = bf_algorithm(input);
    std::cout<<std::endl;
    for(auto i = 0; i < res.size(); i++)
        std::cout<<'['<<i+1<<']'<<res[i]<<std::endl;
}