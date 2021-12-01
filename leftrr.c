#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>

/*
S->Aa|b
A->Ae|Sd|f

E->E+T|T
T->T*F|F
F->i

*/
int n,ans_n=0,m=0;
int used[26];
struct production{
    char lhs,rhs[25][50];
    int no_of_map;
}pro[25],ans[25],temp;

char get_nt(){
    for(int i=0;i<26;i++){
        if(used[i]==0) return 'A'+i;
    }
    return '@';
}
int has_left_recursion(int i){
    for(int j=0;j<pro[i].no_of_map;j++){
        if(pro[i].rhs[j][0]==pro[i].lhs) return 1;
    }
    return 0;
}
int substitute(int i,int j){
    int isfound1 = 0,no,isfound2 = 0;
    for(int k=0;k<pro[i].no_of_map;k++){
        for(int l = 0;pro[i].rhs[k][l]!='\0';l++){
            if(pro[i].rhs[k][l]==pro[j].lhs){
                isfound1 = 1;
                isfound2 = 1;
                no = l;
                break;
            }
        }
        if(isfound1){
            isfound1 = 0;
            for(int itr = 0;itr<pro[j].no_of_map;itr++){
                int itr3 = 0;
                while(itr3<no){
                    temp.rhs[m][itr3] = pro[i].rhs[k][itr3];
                    itr3++;
                }
                for(int itr2 = 0;pro[j].rhs[itr][itr2]!='\0';itr2++){
                    temp.rhs[m][itr3] = pro[j].rhs[itr][itr2];
                    itr3++;
                }
                no = no+1;
                while(pro[i].rhs[k][no]!='\0'){
                     temp.rhs[m][itr3] = pro[i].rhs[k][no];
                     itr3++;no++;
                }
                m++;
            }
        }else{
            for(int l = 0;pro[i].rhs[k][l]!='\0';l++){
                temp.rhs[m][l] = pro[i].rhs[k][l];m++;
            }
        }
    }
    return isfound2;
}

void remove_left_recursion(int i,char ch){
    ans[ans_n].lhs = pro[i].lhs;
    ans[ans_n].no_of_map = 0;
    ans[ans_n+1].no_of_map = 0;
    ans[ans_n+1].lhs = ch;
    for(int j=0;j<pro[i].no_of_map;j++){
        if(pro[i].lhs!=pro[i].rhs[j][0]){
            int itr = 0;
            for(int k=0;pro[i].rhs[j][k]!='\0';k++){
                ans[ans_n].rhs[ans[ans_n].no_of_map][itr] = pro[i].rhs[j][k];
                itr++;
            }
            ans[ans_n].rhs[ans[ans_n].no_of_map][itr] = ch;
            ans[ans_n].no_of_map++;
        }else{
            int itr = 0;
            for(int k=1;pro[i].rhs[j][k]!='\0';k++){
                ans[ans_n+1].rhs[ans[ans_n+1].no_of_map][itr] = pro[i].rhs[j][k];
                itr++;
            }
            ans[ans_n+1].rhs[ans[ans_n+1].no_of_map][itr] = ch;itr++;
            
            ans[ans_n+1].no_of_map++;
        }
    }
    ans[ans_n+1].rhs[ans[ans_n+1].no_of_map][0] = '#';
    ans[ans_n+1].no_of_map++;
    ans_n+=2;
}
void main(){
    for(int i=0;i<26;i++) used[i] = 0;
    printf("No of production : ");scanf("%d",&n);
    for(int i=0;i<n;i++){
        pro[i].no_of_map = 0;
        int j = 0;
        char temp[25];
        scanf("%s",temp);
        pro[i].lhs = temp[0];
        int kk = 3,ll=0;
        while(temp[kk]!='\0'){
            if(temp[kk]=='|'){ j++;ll=0;kk++;continue;}
            pro[i].rhs[j][ll] = temp[kk];
            ll++;
            kk++;
        
        }
        pro[i].no_of_map = j+1;
        used[pro[i].lhs - 'A'] = 1;
    }

    for(int i=0;i<n;i++){
        int ischange = 0;
        for(int j=0;j<i;j++){
            struct production temp_;
            temp = temp_;
            temp.no_of_map = 0;
            m=0;
            int again = 1;
            again = substitute(i,j);
            if(again) ischange = 1;
            /*while(again){
                again = substitute(i,j);
            }*/
    
        }
        if(ischange){
            pro[i].no_of_map = m;
            
            for(int k=0;k<m;k++){
                for(int l = 0;pro[i].rhs[k][l]!='\0';l++){
                    pro[i].rhs[k][l] = temp.rhs[k][l];
                    
                }
                
            }
        }
        
        printf("\n");
        if(has_left_recursion(i)){
            char NT = get_nt();
            remove_left_recursion(i,NT);
        }else{
            ans[ans_n].lhs = pro[i].lhs;
            for(int j=0;j<pro[i].no_of_map;j++){
                int itr = 0;
                for(int k=0;pro[i].rhs[j][k]!='\0';k++){
                    ans[ans_n].rhs[ans[ans_n].no_of_map][itr] = pro[i].rhs[j][k];
                    itr++;
                }
                ans[ans_n].no_of_map++;
            }
            ans_n++;
        }
    }
    printf("\n--------------------- \n");
    for(int i=0;i<ans_n;i++){
        printf("%c->",ans[i].lhs);
        for(int j=0;j<ans[i].no_of_map;j++){
            for(int k=0;ans[i].rhs[j][k]!='\0';k++){
                printf("%c",ans[i].rhs[j][k]);
            }
            printf("|");
        }
        printf("\n");
    }
}