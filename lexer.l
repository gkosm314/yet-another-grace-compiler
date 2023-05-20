%{

#define T_eof 0
#define T_and 1001
#define T_int 1002
#define T_then 1003
#define T_char 1004
#define T_mod 1005
#define T_var 1006
#define T_div 1007
#define T_not 1008
#define T_while 1009
#define T_do 1010
#define T_nothing 1011
#define T_else 1012
#define T_or 1013
#define T_fun 1014
#define T_ref 1015
#define T_if 1016
#define T_return 1017
#define T_leq 1018
#define T_geq 1019
#define T_arr 1020
#define T_id 1021
#define T_char_lit 1023
#define T_writestring 1024

void ERROR (const char msg []);

%}


L [a-zA-Z]
D [0-9]
W [ \t\n\r]
P [ -~]
HEX "\\x"[0-9][0-9]
E [\n\t\r\0\\\'\"\x[0-9][0-9]]

%x COMMENT
%x SINGLE_COMMENT
%x STRING

%option noyywrap
%option yylineno

%%

"and" { return T_and; }
"int" { return T_int; }
"then" { return T_then; }
"char" { return T_char; }
"mod" { return T_mod; }
"var" { return T_var; }
"div" { return T_div; }
"not" { return T_not; }
"while" { return T_while; }
"do" { return T_do; }
"nothing" { return T_nothing; }
"else" { return T_else; }
"or" { return T_or; }
"fun" { return T_fun; }
"ref" { return T_ref; }
"if" { return T_if; }
"return" { return T_return; }


[\+\-\*\=\#\<\>\(\)\[\]\{\}\,\;\:] { return yytext[0]; }
"<=" { return T_leq; }
">=" { return T_geq; }
"<-" { return T_arr; }


{L}[a-zA-Z0-9\_]* { return T_id; }

{D}+ { return T_int; }

\'("\\n"|"\\0"|"\\t"|"\\r"|"\\\\"|"\\'"|"\\\"")\' { return T_char_lit; }
\'{HEX}\' { return T_char_lit; }
\'([ -~]{-}[\\])\' { return T_char_lit; }


"$$" { BEGIN(COMMENT); printf("Found start of multline comment ... \n"); }
<COMMENT>"$$" { BEGIN(INITIAL); printf("... found end of multline comment \n"); } 
<COMMENT>"$" {}
<COMMENT>[^$]+ {}

"$" { BEGIN(SINGLE_COMMENT); printf("Found start of single comment ... \n"); }
<SINGLE_COMMENT>\n { BEGIN(INITIAL); printf("... found end of single comment \n"); } 
<SINGLE_COMMENT>[^\n]+ {}

\" { BEGIN(STRING); }
<STRING>\" { BEGIN(INITIAL); return 20000; }
<STRING>[^\"]+ {}

{W}+ { /* nothing */ }


. { ERROR("Illegeal token"); }


%%

void ERROR (const char msg []) {
    fprintf(stderr, "ERROR: %s at line %d (ASCII: %d)\n", msg, yylineno, yytext[0]);
    exit(1);
}


int main() {
  int token;
  do {
    token = yylex();
    printf("token = %d, lexeme = \"%s\"\n", token, yytext);
  } while(token != T_eof);
  return 0;
}
