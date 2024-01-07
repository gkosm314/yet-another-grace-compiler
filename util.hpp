#ifndef __UTIL_HPP__ 
#define __UTIL_HPP__ 

#include <iostream>
#include "ast.hpp"

#define INT_CONST_BRACKET_LIST_DIMENSION_AUTOCOMPLETE -1

std::ostream &operator<<(std::ostream &out, const AST &ast);

std::ostream &operator<<(std::ostream &out, const Type &t);

void yyerror(const char *msg);

void semInitLibraryFunctions();

Type toType(DATA_TYPE datatype_arg);

extern llvm::LLVMContext TheContext;
extern llvm::IRBuilder<> Builder;
extern std::unique_ptr<llvm::Module> TheModule;

typedef llvm::Type llvmType;

extern llvmType *i32;
extern llvmType *i64;

llvmType *getLLVMType(Type t);

llvm::ConstantInt* c8(char c);
llvm::ConstantInt* c64(int n);

void codegenInitLibraryFunctions();
void codegenMain(llvm::Function* program_func);

std::string mangle(const char * name, unsigned int scope_id);

#endif