%{
     #include "y.tab.h"
     #include<string.h>
     #include<stdio.h>
     int cnt = 0;
     char ids[20][8];
     float Vals[20];
     int f_Input[20];
     int lookup(char*);
%}

%%
[0-9]+                   {yylval.ival = atoi(yytext); return N;}
" "                      {}
[0-9]*"."[0-9]+          {yylval.fval = atof(yytext); return FN;}
"'"(.|\\n|\\t)"'"        {yylval.ival = *(yytext+1); return N;}
[+-/*=;()]               {return yytext[0];}
[_a-zA-Z][_a-zA-Z0-9]*   {yylval.ival = lookup(yytext); return ID;}
.                        {return 0;}
%%

int lookup(char* yytxt){
     for(int i = 0; i < cnt; i++){
          if(strcmp(yytxt, ids[i]) == 0){
               printf("Found at %d\n",i);
               return i;
          }
     }
     strcpy(ids[cnt],yytxt);
     printf("creating at %d\n",cnt);
     return cnt++;
}