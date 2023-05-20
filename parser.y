%{
#include <cstdio>
#include <cstdlib>
#include "lexer.hpp"
%}


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
%token T_arr "arr"

%token T_id
/* %token T_writestring */
%token T_int_lit
%token T_char_lit
%token T_string_lit



%%

program:
    func_def
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
|   T_id T_id id_rest ':' fpar_type
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
|   l_value "arr" expr ';'
|   block
|   func_call ';'
|   "if" cond "then" stmt "else" stmt
|   "if" cond "then" stmt
|   "while" cond "do" stmt
|   "return" ';'
|   "return" expr ';'

block:
    '{' stmt_list '}'


stmt_list:
    /* nothing */
|   stmt_list stmt
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
    T_int_lit
|   T_char_lit
|   l_value
|   '(' expr ')'
|   func_call
|   '+' expr
|   '-' expr
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
  fprintf(stderr, "Error: %s\n", msg);
  exit(1);
}

int main() {
  int result = yyparse();
  if (result == 0) printf("Success!\n");
  return result;
}