#ifndef __AST_HPP__ 
#define __AST_HPP__ 

#include <iostream>

/* This is needed in order to link C with C++ */
extern "C" {
  #include "symbol.h"
  
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

  extern Type          typeArray          (RepInteger size, Type refType);
  extern bool          equalType          (Type type1, Type type2);
}

/* This enum is used during the parsing.
   It is different from the enums used in "symbol.h", which are used for the semantic analysis. */
enum DATA_TYPE { DATA_TYPE_int, DATA_TYPE_char, DATA_TYPE_void };

class AST
{
  public:
    virtual ~AST() = default;
    virtual void printAST(std::ostream &out) const = 0;
    virtual void sem() {};
};

/* Forward declarations for util.hpp */
std::ostream &operator<<(std::ostream &out, const AST &ast);
std::ostream &operator<<(std::ostream &out, const Type &t);
void yyerror(const char *msg);
Type toType(DATA_TYPE datatype_arg);

#endif
