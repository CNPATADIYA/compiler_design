%{
 #include<stdio.h>
 #include<math.h>
 #include<stdlib.h>
 extern float values[20];
 extern int fOrI[20];
 void yyerror(char*);
 void yywrap();
 int yylex();
 typedef struct Type{int dt; float val;} Type;
 void updval(float,Type*);
 struct Type* getNode(struct Type*,struct Type*);
%}
%union{
     int ival;
     float fval;
     struct Type *tval;
}
%right '='
%left '+' '-'
%left '*' '/' '%'
%right '^'
%token <ival> N ID
%token <fval> FN
%type  <tval> E

%%
SS   : SS S
     | S
     ;

S    : E ';'        {if($1->dt == 0) printf("Answer: %d",(int)($1->val)); else printf("Answer: %f",$1->val);}
     ;

E    : E '+' E      {$$=getNode($1,$3);      updval($1->val+$3->val,($$));      free($1);      free($3);}

     | E '-' E      {$$=getNode($1,$3);      updval($1->val-$3->val,($$));      free($1);      free($3);}

     | E '*' E      {$$=getNode($1,$3);      updval($1->val*$3->val,($$));      free($1);      free($3);}

     | E '/' E      {if($3->val == 0){ char* msg="Divison By Zero"; yyerror(msg); return 0;} else{ $$=getNode($1,$3); updval($1->val/$3->val,($$));} free($1); free($3);}

     | E '%' E      {$$=getNode($1,$3);      if($$->dt == 1) {char* msg="Both Operands must be Int"; yyerror(msg); return 0;}     if($3->val == 0){ char* msg="Divison By Zero"; yyerror(msg); return 0;}    else{ $$=getNode($1,$3); updval((int)($1->val)%(int)($3->val),($$));}      free($1);      free($3);}

     | E '^' E      {$$=getNode($1,$3);      updval(pow($1->val,$3->val),($$)); free($1);      free($3);}

     | ID '=' E     {$$=getNode($3,$3);      values[$1]=$3->val;      $$->val = $3->val;       fOrI[$1] = $3->dt;  free($3);}

     | FN           {$$=(Type*)malloc(sizeof(Type));   $$->val=$1;    $$->dt=1;}

     | N            {$$=(Type*)malloc(sizeof(Type));   $$->val=$1;    $$->dt=0;}

     | ID           {$$=(Type*)malloc(sizeof(Type));   $$->val=values[$1];      $$->dt=fOrI[$1];}
     
     | '(' E ')'    {$$=getNode($2,$2); $$->val=$2->val;    $$->dt=$2->dt;      free($2);}
     ;
%%

int main(){
     yyparse();
     return 0;
}

struct Type* getNode(struct Type* a, struct Type* b){
     struct Type* node = (struct Type*)malloc(sizeof(struct Type));
     node->dt = (a->dt+b->dt != 0);
     return node;
}

void updval(float a, Type* node){
     if(node->dt == 0){
          node->val = (int)(a);
     }
     else{
          node->val = a;
     }
}

void yyerror(char *msg){
     printf("***ERROR: %s***",msg);
}

void yywrap(){
     return ;
}
