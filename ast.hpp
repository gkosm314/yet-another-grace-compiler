#ifndef __AST_HPP__ 
#define __AST_HPP__ 

#include <iostream>
#include <llvm/IR/Value.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LegacyPassManager.h>
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include <llvm/IR/Verifier.h>
#include <llvm/Transforms/InstCombine/InstCombine.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Scalar/GVN.h>
#include <llvm/Transforms/Utils.h>

#include <set>

/* This is needed in order to link C with C++ */
extern "C" {
  #include "symbol.h"

  extern Scope       * currentScope;
  
  extern void          initSymbolTable    (unsigned int size);
  extern void          destroySymbolTable (void);
  extern void          openScope          (void);
  extern void          closeScope         (void);

  extern SymbolEntry * newVariable        (const char * name, Type type);
  extern SymbolEntry * newFunction        (const char * name);
  extern SymbolEntry * newParameter       (const char * name, Type type, 
                                           PassMode     mode, SymbolEntry * f);

  extern void          forwardFunction    (SymbolEntry * f);
  extern void          endFunctionHeader  (SymbolEntry * f, Type type);
  extern void          destroyEntry       (SymbolEntry * e);
  extern SymbolEntry * lookupEntry        (const char * name, LookupType type, bool err);

  extern Type          typeArray          (RepInteger size, Type refType, bool autocompleteFlag);
  extern bool          equalType          (Type type1, Type type2);

  bool                 equalTypeAutocomplete (Type type1, Type type2);
}

/* This enum is used during the parsing.
   It is different from the enums used in "symbol.h", which are used for the semantic analysis. */
enum DATA_TYPE { DATA_TYPE_int, DATA_TYPE_char, DATA_TYPE_void };

/* Maps the mangled name of each variable to the corresponding llvmAddr */
typedef llvm::Value* llvmAddr;
extern std::map<std::string, llvmAddr> varMap;

/* This set contains the mangled names of variables that are escape variables.
 * In other words, this set contains the mangled names of variables that are used in a nested scope.
 * Mangled names are unique accross the whole program -> no ambiguity.
 */
extern std::set<std::string> escapeVars;

/* Maps every (non-toplevel) function to the function that defines it
 * Both the key and the value are mangled function names that uniquely identify each function 
 */
extern std::map<std::string, std::string> outerFunc;

/* Maps every function to its depth Keys are mangled function names that uniquely identify each function */
extern std::map<std::string, unsigned int> funcDepth;

/* Maps every escape variable to its position in the stack frame of the function that defines it. 
 * Keys are mangled variable names that uniquely identify each variable. */
extern std::map<std::string, unsigned int> stackframePos;

class AST
{
  public:
    AST();
    virtual ~AST() = default;
    virtual void printAST(std::ostream &out) const = 0;
    virtual void sem() {};
    virtual llvm::Value *compile() { return nullptr; };

  protected:
    int lineno;
    void semError(const char *msg);
};

/* Forward declarations for util.hpp */
std::ostream &operator<<(std::ostream &out, const AST &ast);
std::ostream &operator<<(std::ostream &out, const Type &t);
void yyerror(const char *msg);
Type toType(DATA_TYPE datatype_arg);

extern bool run_optimizations;

#endif
