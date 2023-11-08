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

%token<id> T_id
/* %token T_writestring */
%token<int_val> T_int_lit
%token<char_val> T_char_lit
%token<str_val> T_string_lit

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
    Block *block;
    Condition *cond;
    LocalDef *localdef;
    FuncDef *funcdef;
    AbstractLvalue *abstractlvalue;
    FuncCall *funccall;
    Id *id;
    char char_val;
    int  int_val;
    std::string *str_val;
    std::vector<Expr *> *vector_expr;
    std::vector<LocalDef *> *vector_local_def;
    std::vector<FParDef *> *vector_fpar_def;
    Header *header;
    FParDef *fpar_def;
    std::vector<Id *> *id_defs;
    Type *type;
    DATA_TYPE data_type;
    FuncDecl* func_decl;
    VarDef* var_def;
    std::vector<int> *int_vec;
}

%type<stmt> stmt 
%type<expr> expr 
%type<block> block stmt_list
%type<cond> cond 
%type<abstractlvalue> l_value
%type<funccall> func_call
%type<char_val> '+' '-' '*' '=' '#' '<' '>'
%type<vector_expr> expr_list expr_rest
%type<funcdef> func_def
%type<vector_local_def> local_def_list
%type<header> header
%type<localdef> local_def
%type<vector_fpar_def> fpar_def_list fpar_def_rest
%type<fpar_def> fpar_def
%type<id_defs> id_rest
%type<type> fpar_type type
%type<data_type> data_type ret_type
%type<int_vec> int_const_bracket_list int_const_bracket_list_var
%type<func_decl> func_decl
%type<var_def> var_def

%%

program:
    func_def { }
;

func_def:
    header local_def_list block { $$ = new FuncDef($1, $2, $3); }
;

local_def_list:
    /* nothing */             { $$ = new std::vector<LocalDef *>(); }  
|   local_def_list local_def  { $1->push_back($2); $$ = $1;         } 
;

header:
    "fun" T_id '(' fpar_def_list ')' ':' ret_type { $$ = new Header($2, $4, $7); }
;

fpar_def_list:
    /* nothing */           { $$ = new std::vector<FParDef *>(); }
|   fpar_def_rest fpar_def  { $1->push_back($2); $$ = $1;        }
;

fpar_def_rest:
    /* nothing */               { $$ = new std::vector<FParDef *>(); }
|   fpar_def_rest fpar_def ';'  { $1->push_back($2); $$ = $1;        }
;

fpar_def:
    "ref" id_rest T_id ':' fpar_type { $2->push_back($3); $$ = new FParDef($2, $5, true);  }
|   id_rest T_id ':' fpar_type       { $1->push_back($2); $$ = new FParDef($1, $4, false); }
;

id_rest:
    /* nothing */    { $$ = new std::vector<Id *>(); }
|   id_rest T_id ',' { $1->push_back($2); $$ = $1;   }
;

data_type:
    "int"   { $$ = DATA_TYPE_int;  }
|   "char"  { $$ = DATA_TYPE_char; } 
;

type:
    data_type int_const_bracket_list_var         { $$ = new Type($1, $2); }
;

int_const_bracket_list_var:
    /* nothing */                                { $$ = new std::vector<int>(); }
|   int_const_bracket_list_var '[' T_int_lit ']' { $1->push_back($3); $$ = $1;  }
;

ret_type:
    data_type  { $$ = $1;                }
|   "nothing"  { $$ = DATA_TYPE_nothing; }
;

int_const_bracket_list:
    ']'                                       { $$ = new std::vector<int>(); $$->push_back(INT_CONST_BRACKET_LIST_DIMENSION_AUTOCOMPLETE); }
|   T_int_lit ']'                             { $$ = new std::vector<int>(); $$->push_back($1);                                            }
|   int_const_bracket_list '[' T_int_lit ']'  { $1->push_back($3); $$ = $1;                                                                }
;

fpar_type:
    data_type                            { $$ = new Type($1, new std::vector<int>()); }
|   data_type '[' int_const_bracket_list { $$ = new Type($1, $3);                     }
;

local_def:
    func_def  { $$ = $1; }
|   func_decl { $$ = $1; }
|   var_def   { $$ = $1; }
;

func_decl:
    header ';' { $$ = new FuncDecl($1); }
;

var_def:
    "var" id_rest T_id ':' type ';'  { $2->push_back($3); $$ = new VarDef($2, $5); }
;

stmt:
    ';'                               { /* nothing */              }
|   l_value "arr" expr ';'            { $$ = new Assign($1, $3);   }
|   block                             { $$ = $1;                   }
|   func_call ';'                     { $$ = new FuncCallStmt($1); }
|   "if" cond "then" stmt "else" stmt { $$ = new If($2, $4, $6);   }
|   "if" cond "then" stmt             { $$ = new If($2, $4);       }
|   "while" cond "do" stmt            { $$ = new While($2, $4);    }
|   "return" ';'                      { $$ = new Return();         }
|   "return" expr ';'                 { $$ = new Return($2);       }

block:
    '{' stmt_list '}'                 { $$ = $2;                   }


stmt_list:
    /* nothing */                     { $$ = new Block();          }
|   stmt_list stmt                    { $1->append($2); $$ = $1;   }
;

func_call:
    T_id '(' expr_list ')'  { $$ = new FuncCall($1, $3); }
;


expr_list:
    /* nothing */           { $$ = new std::vector<Expr *>(); }
|   expr_rest expr          { $1->push_back($2); $$ = $1;     }
;

expr_rest:
    /* nothing */           { $$ = new std::vector<Expr *>(); }
|   expr_rest expr ','      { $1->push_back($2); $$ = $1; }
;

l_value:
    T_id                  { $$ = new Id(yylval.str_val);     }
|   T_string_lit          { $$ = new StrLit(yylval.str_val); }
|   l_value '[' expr ']'
;

expr:
    T_int_lit             { $$ = new IntConst($1);       }
|   T_char_lit            { $$ = new CharConst($1);      }
|   l_value               { $$ = $1;                     }
|   '(' expr ')'          { $$ = $2;                     }
|   func_call             { $$ = $1;                     }
|   '+' expr %prec UNARY  { $$ = new UnaryOp($1, $2);    }
|   '-' expr %prec UNARY  { $$ = new UnaryOp($1, $2);    }
|   expr '+' expr         { $$ = new BinOp($1, '+', $3); }
|   expr '-' expr         { $$ = new BinOp($1, '-', $3); }
|   expr '*' expr         { $$ = new BinOp($1, '*', $3); }
|   expr T_div expr       { $$ = new BinOp($1, '/', $3); }
|   expr T_mod expr       { $$ = new BinOp($1, '%', $3); }
;

cond:
    '(' cond ')'          { $$ = $2;                           }
|   "not" cond            { $$ = new LogicalCond($2, 'n');     }
|   cond "and" cond       { $$ = new LogicalCond($1, 'a', $3); }
|   cond "or" cond        { $$ = new LogicalCond($1, 'o', $3); }
|   expr '=' expr         { $$ = new NumericCond($1, $2, $3);  }
|   expr '#' expr         { $$ = new NumericCond($1, $2, $3);  }
|   expr '<' expr         { $$ = new NumericCond($1, $2, $3);  }
|   expr '>' expr         { $$ = new NumericCond($1, $2, $3);  }
|   expr T_leq expr       { $$ = new NumericCond($1, 'l', $3); }
|   expr T_geq expr       { $$ = new NumericCond($1, 'g', $3); }
;

%%

void yyerror(const char *msg) {
  fprintf(stderr, "Error: %s at line %d\n", msg, yylineno);
  exit(1);
}

int main() {
  int result = yyparse();
  if (result == 0) printf("Success!\n");
  return result;
}