#ifndef __UTIL_HPP__ 
#define __UTIL_HPP__ 

#include <iostream>
#include "ast.hpp"

std::ostream &operator<<(std::ostream &out, const AST &ast);

std::ostream &operator<<(std::ostream &out, const Type &t);

void yyerror(const char *msg);

Type toType(DATA_TYPE datatype_arg);

#endif