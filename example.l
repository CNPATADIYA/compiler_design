%{
#include "y.tab.h"
%}
%%
[-+/*><&|!;(){}=]			{return yytext[0];}
[0-9]+				{return NUM;}
"for"				{return FOR;}
"while"				{return WHILE;}
"if"				{return IF;}
"else"				{return ELSE;}
([_a-zA-Z][0-9]*)+	{return ID;}
%%