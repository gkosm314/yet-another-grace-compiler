%{

#include "parser.hpp"

#define T_eof 0

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

{D}+ { return T_int_lit; }

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
<STRING>\" { BEGIN(INITIAL); return T_string_lit; }
<STRING>[^\"]+ {}

{W}+ { /* nothing */ }


. { ERROR("Illegeal token"); }


%%

void ERROR (const char msg []) {
    fprintf(stderr, "ERROR: %s at line %d (ASCII: %d)\n", msg, yylineno, yytext[0]);
    exit(1);
}

