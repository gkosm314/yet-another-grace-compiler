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
extern std::unique_ptr<llvm::legacy::FunctionPassManager> TheFPM;
extern std::unique_ptr<llvm::Module> TheModule;

typedef llvm::Type llvmType;

extern llvmType *i32;
extern llvmType *i64;

llvmType *getLLVMType(Type t);

llvm::ConstantInt* c8(char c);
llvm::ConstantInt* c32(int n);
llvm::ConstantInt* c64(int n);

void codegenInitLibraryFunctions();
void codegenInitFPM();
void codegenMain(llvm::Function* program_func);

std::string mangle(const char * name, unsigned int scope_id);

std::string getStackFrameName(std::string mangled_function_name);
std::string getStackFrameStructName(std::string mangled_function_name);

#define TOP_LEVEL_FUNCTION_MAXIMUM_SCOPE 2

bool isTopLevelFunc(std::string mangled_function_name);

llvmAddr walkupStaticLinkChain(unsigned int decl_depth, unsigned int usage_depth, llvmType **final_stack_frame_type = nullptr);

#endif