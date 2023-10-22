%{
#include <cstdio>
#include <cstdlib>

#include "ast.hpp"
#include "lexer.hpp"

/* Use yylineno from lexer file, since the main is in this file we need to use extern here */
extern int yylineno;

%}


%define parse.error verbose /* For debug purposes*/

%token T_and "and"
%token T_int "int"
%token T_then "then"
%token T_char "char"
%token T_mod "mod"
%token T_var "var"
%token T_div "div"
%token T_not "not"
%token T_while "while"
%token T_do "do"
%token T_nothing "nothing"
%token T_else "else"
%token T_or "or"
%token T_fun "fun"
%token T_ref "ref"
%token T_if "if"
%token T_return "return"
%token T_leq "leq"
%token T_geq "geq"
%token T_arr "arr" /* Short for arrow, the assignement op <- */

%token T_id
/* %token T_writestring */
%token T_int_lit
%token T_char_lit
%token T_string_lit

%left "or"
%left "and"
%precedence "not"
%nonassoc '=' '#' '>' '<' "leq" "geq"
%left '+' '-'
%left '*' "div" "mod"
%precedence UNARY /*unary minus and plus signs*/

%expect 1

%union {
    Stmt *stmt;
    Expr *expr;
    Condition *cond;
    LocalDef *localdef;
    FuncDef *funcdef;
    AbstractLvalue *abstractlvalue;
    char char_val;
    int  int_val;
    std::string *str_val;
}

%%

program:
    func_def { }
;

func_def:
    header local_def_list block
;

local_def_list:
    /* nothing */
|   local_def_list local_def;
;

header:
    "fun" T_id '(' fpar_def_list ')' ':' ret_type
;

fpar_def_list:
    /* nothing */
|   fpar_def fpar_def_rest
;

fpar_def_rest:
    /* nothing */
|   ';' fpar_def fpar_def_rest
;

fpar_def:
    "ref" T_id id_rest ':' fpar_type
|   T_id id_rest ':' fpar_type
;

id_rest:
/* nothing */
|   ',' T_id id_rest
;

data_type:
    "int"
|   "char"
;

type:
    data_type int_const_bracket_list
;

int_const_bracket_list:
    /* nothing */
|   '[' T_int_lit ']' int_const_bracket_list
;

ret_type:
    data_type
|   "nothing"
;

fpar_type:
    data_type '[' ']' int_const_bracket_list
|   data_type int_const_bracket_list
;

local_def:
    func_def
|   func_decl
|   var_def
;

func_decl:
    header ';'
;

var_def:
    "var" T_id id_rest ':' type ';'
;

stmt:
    ';'
|   l_value "arr" expr ';'            /*{ $$ = new Assign($1, $3);   } */
|   block                             /*{ $$ = $1;                   } */
|   func_call ';'                     /*{ $$ = new FuncCallStmt($1); } */
|   "if" cond "then" stmt "else" stmt /*{ $$ = new If($2, $4, $6);   } */
|   "if" cond "then" stmt             /*{ $$ = new If($2, $4);       } */
|   "while" cond "do" stmt            /*{ $$ = new While($2, $4);    } */
|   "return" ';'                      /*{ $$ = new Return();         } */
|   "return" expr ';'                 /*{ $$ = new Return($2);       } */

block:
    '{' stmt_list '}'                 /*{ $$ = $2;                   } */


stmt_list:
    /* nothing */                     /*{ $$ = new Block();          } */
|   stmt_list stmt                    /*{ $1->append($2); $$ = $1;   } */
;

func_call:
    T_id '(' expr_list ')'
;


expr_list:
    /* nothing */
|   expr expr_rest
;

expr_rest:
    /* nothing */
|   ',' expr expr_rest
;

l_value:
    T_id
|   T_string_lit
|   l_value '[' expr ']'
;

expr:
    T_int_lit             /*{ $$ = new IntConst($1);  }*/
|   T_char_lit            /*{ $$ = new CharConst($1); }*/
|   l_value
|   '(' expr ')'
|   func_call
|   '+' expr %prec UNARY 
|   '-' expr %prec UNARY
|   expr '+' expr
|   expr '-' expr
|   expr '*' expr
|   expr T_div expr
|   expr T_mod expr
;

cond:
    '(' cond ')'
|   "not" cond
|   cond "and" cond
|   cond "or" cond
|   expr '=' expr
|   expr '#' expr
|   expr '<' expr
|   expr '>' expr
|   expr T_leq expr
|   expr T_geq expr
;

%%

void yyerror(const char *msg) {
  fprintf(stderr, "Error: %s at line %d\n", msg, yylineno);
  exit(1);
}

/* int main() {
  int result = yyparse();
  if (result == 0) printf("Success!\n");
  return result;
} */