%{
#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include "y.tab.h"
int cnt=0;
char names[20][8];
float value[20] = {0};
//extern int yylval;
int lookup(char str[]);

%}
%%
[0-9]+  			{yylval.ival=atoi(yytext); return N;}
[0-9]*"."[0-9]+  	{yylval.fval=atof(yytext); return FN;}
[-()=+*/;] 	{return yytext[0];}
([_a-zA-Z][0-9]*)+ 	{yylval.ival=lookup(yytext); return ID;}
%%

int lookup(char str[]){
    int i;
    for(i=0;i<cnt;i++){
        if(strcmp(names[i],str)==0) return i;
    }
    cnt++;
    strcpy(names[i],str);
    return i;
}

