#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>


/*
E–>TX 
X–>+TX|# 
T–>FY 
Y–>*FY|# 
F–>(E)|i
*/

char input[100];

int i;
void E();
void EP();
void T();
void TP();
void F();
void error();
void main()

{
    printf("Enter string : ");
    i=0;
    gets(input);
    E();
    printf("String Accepted!\n");
    
}
// 
void error(){
    printf("String not accepted!\n");
    exit(0);
}
void E(){
    if(input[i]=='+' || input[i]=='*' || input[i]==')' || input[i]=='\0')
        error();
    T();
    EP();
}

void EP(){

    if(input[i]=='+'){
        i++;
        T();
        EP();
    }else if(input[i]==')' || input[i]=='\0') return;
    else
        error();

}

void T(){
    if(input[i]=='+' || input[i]=='*' || input[i]==')' || input[i]=='\0')
        error();
    F();
    TP();
}

void TP(){
    if(input[i]=='*'){
        i++;
        F();
        TP();
    }else if(input[i]==')' || input[i]=='\0' || input[i]=='+') return;
    else error();

}

void F(){

    if(input[i]=='('){
        i++;
        E();
        if(input[i]!=')'){
            error();
        }
        i++;
    }
    else if((input[i]>='a'&&input[i]<='z')||(input[i]>='A'&&input[i]<='Z')||(input[i]>='0' && input[i]<='9')){
        i++;
    }
    else
        error();
}