#include<bits/stdc++.h>
#include <fstream>
using namespace std;

unordered_map<string,int> constant_table

bool is_present(string a,string b){
    if (a.find(b) != std::string::npos) {
        return true;
    }
    return false;
}
int main(){
    ifstream fin;
    string line;
    fin.open("code.txt");
    while(fin){
        getline(fin,line);

        if is_present(line,"=") && !is_present(line,"=="){
            string 
        }
    }
    return 0;
}