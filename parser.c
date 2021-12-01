#include<stdio.h>

/*
E –> T E’ 
E’ –> + T E’ | e 
T –> F T’ 
T’ –> * F T’ | e 
F –> ( E ) | id
*/

char inp;

void E();
void EP();
void T();
void TP();
void F();


void E(){
    T();EP();
    if(inp!=';')
        printf("error\n");
    else
        printf("success fully parsed\n");
}
void EP(){
    if(inp=='+' || inp=='-'){
        scanf("%c",&inp);
        T();EP();
    }
}
void T(){
    F();TP();
}
void TP(){
    if(inp=='*' || inp=='/'){
        scanf("%c",&inp);
        F();TP();
    }
}
void F(){
    if(inp=='('){
        scanf("%c",&inp);
        E();
        if(inp==')'){
            scanf("%c",&inp);
        }else{
            
            printf("Error\n");
        }
    }else if(inp>='0' && inp<='9')
        scanf("%c",&inp);
    else{
        
        printf("Error\n");
    }
}

int main(){
    scanf("%c",&inp);
    E();
    return 0;
}