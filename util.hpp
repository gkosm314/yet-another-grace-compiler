#ifndef __UTIL_HPP__ 
#define __UTIL_HPP__ 

#include <iostream>
#include "ast.hpp"

#define INT_CONST_BRACKET_LIST_DIMENSION_AUTOCOMPLETE -1

std::ostream &operator<<(std::ostream &out, const AST &ast);

std::ostream &operator<<(std::ostream &out, const Type &t);

void yyerror(const char *msg);

Type toType(DATA_TYPE datatype_arg);

void semInitLibraryFunctions();

extern llvm::LLVMContext TheContext;
extern llvm::IRBuilder<> Builder;
extern std::unique_ptr<llvm::Module> TheModule;
#endif