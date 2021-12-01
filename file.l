%{
#include<stdio.h>
int l = 1;
int count(char str[]);
%}
start \/\*
end  \*\/
s \"
fc [0-9]+
%%
"int"|"float"|"double"|"bool"|"char"|"enum"|"void"|"struct" {printf(" DT ");}
\/\/(.*) ;
{start}(.|\n)*{end}  {l+=count(yytext);}
\n l++; {printf("\n",yytext);}
"printf"|"main" {printf(" %s ",yytext);}
"if"|"else"|"while"|"for"|"break"|"continue"|"switch"|"case"|"return"|"goto"|"sizeof"|"static"|"const"|"true"|"false"|"typedef"|"#define"|"using"|"namespace"|"std"  {printf(" KEYWORD ");}
{s}(.*){s} {printf(" STRING ");}
{fc}"."{fc} {printf(" Float ");}
[0-9]+ {printf(" NUM ");}
([_a-zA-z][0-9]*)+ {printf(" ID ");}
[+*/=%^?:<>-]|"<<"|">>"|"&&"|"||" {printf(" OP ");}
["@"|"$"|"~"]+ {printf("%s INVALID at %d",yytext,l);}

%%
int yywrap()
{
	return 1;
}
int count(char str[]){
	int c = 0;
	int i=0;
	while(str[i]!='\0'){
		if(str[i]=='\n')	c++;
		i++;
	}
	return c;
	
}
int main()
{
	yylex();
	return 0;
}