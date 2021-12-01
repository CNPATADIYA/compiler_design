%{
     
 #include<stdio.h>
 #include<math.h>
 #include<stdlib.h>
 #include<string.h>
 
 void yyerror(char*);
 void yywrap();
 int yylex();

 extern float Vals[20];
 extern int f_Input[20];
 extern char ids[20][8];

 typedef struct Type{int dt; float val; char* code; char* name;} Type;
 void updval(float,Type*);
 struct Type* GET_NODE(struct Type*,struct Type*);
 int count;
 FILE* fp;
 char* Create_New();
 char* Create_Code_Const(struct Type*);
 char* Create_Output(struct Type*,struct Type*,struct Type*,char);
 char* Create_Code_Assignment(struct Type*,struct Type*);

 void freeMe(struct Type*);
 char* copy(char*);
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

S    : E ';'        {/*printf("\n%s",$1->code);*/}
     ;

E    : E '+' E      {$$=GET_NODE($1,$3);      updval($1->val+$3->val,($$));   $$->name=Create_New();   $$->code=Create_Output($1,$3,$$,'+');  freeMe($1);      freeMe($3);}

     | E '-' E      {$$=GET_NODE($1,$3);      updval($1->val-$3->val,($$));   $$->name=Create_New();   $$->code=Create_Output($1,$3,$$,'-');  freeMe($1);      freeMe($3);}

     | E '*' E      {$$=GET_NODE($1,$3);      updval($1->val*$3->val,($$));   $$->name=Create_New();   $$->code=Create_Output($1,$3,$$,'*');  freeMe($1);      freeMe($3);}

     | E '/' E      {if($3->val == 0){ char* msg="Divison By Zero"; yyerror(msg); return 0;} else{ $$=GET_NODE($1,$3); updval($1->val/$3->val,($$)); $$->name=Create_New();   $$->code=Create_Output($1,$3,$$,'/');} freeMe($1); freeMe($3);}

     | ID '=' E     {$$=GET_NODE($3,$3);      Vals[$1]=$3->val;      $$->val = $3->val;       f_Input[$1] = $3->dt;  $$->name=copy(ids[$1]); $$->code=Create_Code_Assignment($3,$$); freeMe($3);}

     | FN           {$$=(Type*)malloc(sizeof(Type));   $$->val=$1;    $$->dt=1;      $$->name=Create_New();  $$->code=Create_Code_Const($$);}

     | N            {$$=(Type*)malloc(sizeof(Type));   $$->val=$1;    $$->dt=0;      $$->name=Create_New();  $$->code=Create_Code_Const($$);}

     | ID           {$$=(Type*)malloc(sizeof(Type));   $$->val=Vals[$1];      $$->dt=f_Input[$1];    $$->name=copy(ids[$1]); $$->code=(char*)malloc(0);}
     
     | '(' E ')'    {$$=$2;}
     ;
%%

char* copy(char* name){
     char* nname = (char*)malloc((strlen(name)+1)*sizeof(char));
     sprintf(nname,"%s",name);
     return nname;
}

void freeMe(struct Type* a){
     free(a->name);
     free(a->code);
     free(a);
}

int main(){
     count = 0;
     yyparse();
     return 0;
}

char* Create_Output(struct Type* a, struct Type* b, struct Type* c, char signature){
     int len = 1+1+4;
     len += strlen(a->code);
     len += strlen(a->name);
     len += strlen(b->code);
     len += strlen(b->name);
     len += strlen(c->name)+1;
     len++;
     len++;
     char* code = (char*)malloc(len*sizeof(char));
     sprintf(code,"%s%s%s=%s%c%s;\n",a->code,b->code,c->name,a->name,signature,b->name);
     printf("MOV %s, %s\n",c->name,a->name);
     switch(signature) {
          case '+':
               printf("ADD %s, %s\n",c->name,b->name);
               break;
          case '-':
               printf("SUB %s, %s\n",c->name,b->name);
               break;
          case '*':
               printf("MUL %s, %s\n",c->name,b->name);
               break;
          case '/':
               printf("DIV %s, %s\n",c->name,b->name);
               break;
          default:
               printf("\n+++ Sign Not Found +++\n\n");
     }
     return code;
}

char* Create_Code_Assignment(struct Type* a, struct Type* b){
     int len = 1+1+4;
     len += strlen(a->code);
     len += strlen(b->name)+1+strlen(a->name);
     char* code = (char*)malloc(len*sizeof(char));
     sprintf(code,"%s%s=%s;\n",a->code,b->name,a->name);
     printf("MOV %s, %s\n",b->name,a->name);
     return code;
}

char* Create_Code_Const(struct Type* a){
     int len = 1+1+4;
     len += strlen(a->name);
     if(a->dt == 1){
          len += snprintf(NULL,0,"%f",a->val);
     }
     else{
          len += snprintf(NULL,0,"%d",(int)(a->val));
     }
     len++;
     char* code = (char*)malloc(len*sizeof(char));
     
     if(a->dt == 1) {
          sprintf(code,"%s=%f;\n",a->name,a->val);
          
          printf("MOV %s, %f\n",a->name,a->val);
     }
     else {
          sprintf(code,"%s=%d;\n",a->name,(int)(a->val));
          
          printf("MOV %s, %d\n",a->name,(int)(a->val));
     }
     return code;

}

char* Create_New(){
     count++;
     int len = snprintf(NULL,0,"%d",count);
     char* str = (char*)malloc(len+2);
     snprintf(str,len+2,"t%d",count);
     return str;
}

struct Type* GET_NODE(struct Type* a, struct Type* b){
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
     printf("+++ERROR: %s+++",msg);
}

void yywrap(){
     return ;
}
