%{

#include <string>
#include <stdio.h>
#include "ast.hpp"
#include "parser.hpp"

#define T_eof 0

void ERROR (const char msg []);

%}


L    [a-zA-Z]
D    [0-9]
W    [ \t\n\r]
HEX_VAL  [0-9a-f][0-9a-f]

%x COMMENT
%x SINGLE_COMMENT
%x STRING
%x STRING_ESCAPE

%option noyywrap
%option yylineno


%%


"and"     { return T_and; }
"int"     { return T_int; }
"then"    { return T_then; }
"char"    { return T_char; }
"mod"     { return T_mod; }
"var"     { return T_var; }
"div"     { return T_div; }
"not"     { return T_not; }
"while"   { return T_while; }
"do"      { return T_do; }
"nothing" { return T_nothing; }
"else"    { return T_else; }
"or"      { return T_or; }
"fun"     { return T_fun; }
"ref"     { return T_ref; }
"if"      { return T_if; }
"return"  { return T_return; }


[\+\-\*\=\#\<\>\(\)\[\]\{\}\,\;\:] { return yytext[0]; }
"<=" { return T_leq; }
">=" { return T_geq; }
"<-" { return T_arr; }

{L}[a-zA-Z0-9\_]* {  yylval.str_val = new std::string(yytext, yyleng); return T_id; }

{D}+ { yylval.int_val = atoi(yytext); return T_int_lit; }


\"                      { BEGIN(STRING); yylval.str_val = new std::string(); }
<STRING>\"              { BEGIN(INITIAL); return T_string_lit; }
<STRING>\\              { BEGIN(STRING_ESCAPE); }
<STRING>\n              { ERROR("Newline inside string"); }
<STRING>[^\"\\\n]+      { yylval.str_val->append(yytext, yyleng); }


<STRING_ESCAPE>"n"  { yylval.str_val->append(1, '\n'); BEGIN(STRING); }
<STRING_ESCAPE>"0"  { yylval.str_val->append(1, '\0'); BEGIN(STRING); }
<STRING_ESCAPE>"t"  { yylval.str_val->append(1, '\t'); BEGIN(STRING); }
<STRING_ESCAPE>"r"  { yylval.str_val->append(1, '\r'); BEGIN(STRING); }
<STRING_ESCAPE>"\\" { yylval.str_val->append(1, '\\'); BEGIN(STRING); }
<STRING_ESCAPE>"'"  { yylval.str_val->append(1, '\''); BEGIN(STRING); }
<STRING_ESCAPE>"\"" { yylval.str_val->append(1, '\"'); BEGIN(STRING); }
<STRING_ESCAPE>"x"{HEX_VAL} {
    int result;
    (void) sscanf( yytext + 1, "%x", &result); /* Skip the char x when calculating the value */
    yylval.str_val->append(1, result);
    BEGIN(STRING);
}

<STRING_ESCAPE>\n { ERROR("New line after escape"); }
<STRING_ESCAPE>. { ERROR("Invalid character after escape"); }


"$$"                    { BEGIN(COMMENT); }
<COMMENT>"$$"           { BEGIN(INITIAL); } 
<COMMENT>"$"            {}
<COMMENT>[^$]+          {}

"$"                     { BEGIN(SINGLE_COMMENT); }
<SINGLE_COMMENT>\n      { BEGIN(INITIAL);        } 
<SINGLE_COMMENT>[^\n]+  {}

\'"\\n"\'  { yylval.char_val = '\n'; return T_char_lit; }
\'"\\0"\'  { yylval.char_val = '\0'; return T_char_lit; }
\'"\\t"\'  { yylval.char_val = '\t'; return T_char_lit; }
\'"\\r"\'  { yylval.char_val = '\r'; return T_char_lit; }
\'"\\\\"\' { yylval.char_val = '\\'; return T_char_lit; }
\'"\\'"\'  { yylval.char_val = '\''; return T_char_lit; }
\'"\\\""\' { yylval.char_val = '\"'; return T_char_lit; }

\'"\\x"{HEX_VAL}\' {     
    int result;
    (void) sscanf( yytext + 3, "%x", &result); /* Skip the chars '\x when calculating the value */
    yylval.char_val = result;
    return T_char_lit; 
}
\'([ -~]{-}[\\])\' { yylval.char_val = yytext[1]; return T_char_lit; }


{W}+ { /* nothing */ }

. { ERROR("Illegal token"); }


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
