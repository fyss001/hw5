#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here


// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    unsigned cnt=0;
    string temp=in;
    set<std::string> ans;
    for(unsigned i=0;i<temp.length();i++){
        if(temp[i]=='-'){
            cnt++;
        }
    }
    if(cnt<floating.length()) return ans;  //pruning
    if(!cnt){
        if(dict.count(in)&&floating==""){
            ans.insert(in);
        }
        return ans;
    }
    for(unsigned i=0;i<temp.length();i++){
        if(temp[i]=='-'){
            for(int j=0;j<26;j++){
                char c='a'+j;
                string next="";
                bool flag=1;
                for(unsigned k=0;k<floating.length();k++){
                    if(floating[k]!=c||!flag){
                        next+=floating[k];
                    }else{
                        flag=0;
                    }
                }
                temp[i]=c;
                set<std::string> temp_set=wordle(temp, next, dict);
                ans.insert(temp_set.begin(),temp_set.end());
            }
        }
    }
    return ans;
}

// Define any helper functions here
