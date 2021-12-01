%{
#include<stdio.h>
#include<ctype.h>
int yylex();
void yyerror(char *msg);
void yywrap();
extern float value[20];
%}
%union{
    int ival;
    float fval;
}
%right '='
%left '+' '-'
%left '*' '/'
%token <ival> N ID
%token <fval> FN
%type <fval> E
%%
SS : SS S
   | S
   ;
S : E ';'       {printf("Answer = %f\n",$1);}
  ;
E : E '+' E     {$$=$1+$3;}
  | E '-' E     {$$=$1-$3;}
  | E '*' E     {$$=$1*$3;}
  | E '/' E     {$$=$1/$3;}
  | ID '=' E    {$$=value[$1]=$3;}
  | N           {$$=$1;}
  | FN          {$$=$1;}
  | ID          {$$=value[$1];}
  |'(' E ')'	{$$=$2;}
  ;
%%
int main(){
	yyparse();
	return 0;
}
void yyerror(char *msg){
	printf("%s\n",msg);
}
void yywrap(){

}