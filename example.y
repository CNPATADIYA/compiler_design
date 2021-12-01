%{
#include<stdio.h>
#include<ctype.h>
int yylex();
void yyerror(char *msg);
void yywrap();
%}
%token ID NUM IF ELSE FOR WHILE
%%
SS : SS S
   | S
   ;
S : A ';'
  | IFST
  | FORS
  | WHILES
  | BLK
  ;
BLK : '{' SS '}'
	;
IFST : IF '(' A ')' S 
	 | IF '(' A ')' S ELSE S
	 ;
FORS : FOR '(' A ';' A ';' A ')' S
	 ;
WHILES : WHILE '(' A ')' S
	   ;
A : ID '=' A
  | E
  ;
E : E '+' T
  | E '-' T
  | E '*' T
  | E '/' T
  | '(' E ')'
  | E '>' T
  | E '<' T
  | E '+' '+'
  | E '-' '-'
  | E '>' '=' T
  | E '<' '=' T
  | E '&' '&' T
  | E '|' '|' T
  | E '!' '=' T
  | E '+' '=' T
  | E '*' '=' T
  | E '-' '=' T
  | E '/' '=' T
  | T
  ;
T : ID
  | NUM
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
