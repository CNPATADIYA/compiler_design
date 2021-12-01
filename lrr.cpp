#include<bits/stdc++.h>

using namespace std;

pair<char,vector<string>> pro[25];
pair<char,vector<string>> rlrpro[25];
int n,m = 0;
bool used[26];
char get_NT(){
    for(int i=0;i<26;i++){
        if(used[i]==false) return 'A'+i;
    }
    return '@';
}
bool iscycle(int i,int j){
    for(int k=0;k<m;k++){
        if(rlrpro[k].first == pro[j].first){
            for(auto &x:rlrpro[k].second){
                size_t f = x.find(pro[i].first);
                if(f!=string::npos) return true;
            }
            return false;
        }
    }
    return false;
}
bool substitute(int i,int j){
    bool isfound = false;
    int p = 0;
    for(int itr=0;itr<m;itr++){
        if(rlrpro[itr].first==pro[j].first){
            p = itr;break;
        }
    }
    for(int k=0;k<pro[i].second.size();k++){
        size_t f = pro[i].second[k].find(pro[j].first);
        if(f!=string::npos){
            isfound = true;
            string pre = pro[i].second[k].substr(0,f),pos = pro[i].second[k].substr(f+1);
            pro[i].second.erase(pro[i].second.begin()+k);
            for(auto &x:rlrpro[p].second){
                if(x=="#") pro[i].second.push_back(pre+pos);
                else    pro[i].second.push_back(pre+x+pos);
            }
        }
    }
    return isfound;
}

bool hasleftr(int i){
    char ch = pro[i].first;
    for(auto &x:pro[i].second){
        if(x[0]==ch) return true;
    }
    return false;
}
void removeleftd(int i){
    char ch = get_NT();
    used[ch-'A'] = true;
    rlrpro[m].first = pro[i].first;
    rlrpro[m+1].first = ch;
    for(auto &x:pro[i].second){
        if(x=="#"){
            string temp = ""+ch;
            rlrpro[m].second.push_back(temp);
        }else if(x[0]==pro[i].first){
            string temp = x.substr(1) + ch;
            rlrpro[m+1].second.push_back(temp);
        }else{
            rlrpro[m].second.push_back(x+ch);
        }
    }
    rlrpro[m+1].second.push_back("#");
    m+=2;
}
int main(){
    //input
    printf("No of production : ");
    cin>>n;
    for(int i=0;i<n;i++){
        string in;
        char ch;
        cin>>in;
        vector<string> v;
        ch = in[0];
        in = in.substr(3);
        string t="";
        for(int i=0;i<in.size();i++){
            
            if(in[i]=='|'){
                v.push_back(t);
                t = "";
                continue;
            }
            t+=in[i];
            
        }
        v.push_back(t);
        pro[i] = {ch,v};
        used[ch-'A'] = true;
    }

    //logic
    for(int i=0;i<n;i++){
        for(int j=0;j<i;j++){
            if(!iscycle(i,j)) continue;
            bool doitr = true;
            while(doitr){
                doitr = substitute(i,j);
            }
        }
        if(hasleftr(i))
            removeleftd(i);
        else{
            rlrpro[m] = pro[i];m++;
        }
    }

    //printing
    printf("\n\n-------------------------\n\n");
    for(int i=0;i<m;i++){
        cout<<rlrpro[i].first<<"->";
        for(auto &x:rlrpro[i].second){
            cout<<x<<"|";
        }
        printf("\n");
    }

    return 0;
}

/*
2
S->Aa|b
A->Ae|Sd|f

2
A->Ae|Sd|f
S->Aa|b

3
E->E+T|T
T->T*F|F
F->id|(E)


*/