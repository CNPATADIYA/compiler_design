#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<ctype.h>

int n;
struct production{
    char lhs,rhs[25][10],first[25],follow[25];
    int no_of_map;
}pro[25];

void find_follow(char *fl,char ch);

void addtoresult(char *ft,char val){
    int k=0;
    for(k=0 ;ft[k]!='\0';k++)
        if(ft[k]==val)
            return;
    ft[k]=val;
    ft[k+1]='\0';
}

void find_first(char *ft,char ch){
    char temp_first[25];
    int foundepsilon;
    ft[0] = '\0';
    temp_first[0]  = '\0';

    if(!(isupper(ch))){
        addtoresult(ft,ch);
        return;
    }
    for(int i=0;i<n;i++){
        if(pro[i].lhs==ch){
            for(int j=0;j<pro[i].no_of_map;j++){
                if(pro[i].rhs[j][0]=='#'){
                    addtoresult(ft,'#');
                }else{
                    int k=0;
                    while (pro[i].rhs[j][k]!='\0'){
                        foundepsilon = 0;
                        if(pro[i].rhs[j][k]==pro[i].lhs){ addtoresult(ft,'#');break;}
                        find_first(temp_first,pro[i].rhs[j][k]);
                        for(int itr=0;temp_first[itr]!='\0';itr++){
                            if(temp_first[itr]=='#' && pro[i].rhs[j][k+1]!='\0') continue;
                            addtoresult(ft,temp_first[itr]);
                        }
                        
                        for(int itr=0;temp_first[itr]!='\0';itr++)
                            if(temp_first[itr]=='#'){
                                foundepsilon=1;
                                break;
                            }
                 
                        if(!foundepsilon)
                            break;
                        k++;
                    }
                    
                }
            }
        }
    }
}
void find_next(char *fl,char ch,int pro_no,int crr,int nxt2nxt){
    int k;
    if(!(isupper(ch))){
        addtoresult(fl,ch);return;
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<pro[i].no_of_map;j++){
            if(pro[i].lhs==ch){
                int k=0;
                while(pro[i].first[k]!='\0'){
                    if(pro[i].first[k]!='#'){
                        addtoresult(fl,pro[i].first[k]);
                    }else{
                        if(pro[pro_no].rhs[crr][nxt2nxt]=='\0')
                            find_follow(fl,pro[pro_no].lhs);
                        else
                            find_next(fl,pro[pro_no].rhs[crr][nxt2nxt],pro_no,crr,nxt2nxt+1);
                    }
                    k++;
                }
            }
        }
    }
}
void find_follow(char *fl,char ch){
    if(pro[0].lhs == ch) addtoresult(fl,'$');
    for(int i=0;i<n;i++){
        for(int j=0;j<pro[i].no_of_map;j++){
            for(int k=0;pro[i].rhs[j][k]!='\0';k++){
                if(pro[i].rhs[j][k]==ch){
                    if(pro[i].rhs[j][k+1]!='\0'){
                        
                        find_next(fl,pro[i].rhs[j][k+1],i,j,k+2);
                    }
                    if(pro[i].rhs[j][k+1]=='\0' && ch!=pro[i].lhs){
                        find_follow(fl,pro[i].lhs);
                        //addtoresult(fl,'$');
                    }
                        
                }
            }
        }
    } 
}
void main(){
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
    }
    for(int i=0;i<n;i++){
        find_first(pro[i].first,pro[i].lhs);
    }

    for(int i=0;i<n;i++){
        find_follow(pro[i].follow,pro[i].lhs);
    }

    //FIRST
    
    printf("\n\n ------- FIRST -------- \n");
    for(int i=0;i<n;i++){
        printf("%c  : ",pro[i].lhs);
        int j=0;
        while(pro[i].first[j]!='\0'){
            printf("%c ",pro[i].first[j]);j++;
        }
        printf("\n");
    }

    //FOLLOW
    printf("\n\n ------- FOLLOW -------- \n");
    for(int i=0;i<n;i++){
        printf("%c  : ",pro[i].lhs);
        int j=0;
        while(pro[i].follow[j]!='\0'){
            printf("%c ",pro[i].follow[j]);j++;
        }
        printf("\n");
    }

}