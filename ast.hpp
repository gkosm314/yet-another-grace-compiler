#ifndef __AST_HPP__ 
#define __AST_HPP__ 

#include <iostream>
#include "lexer.hpp"

/* Use yylineno from lexer file, since the main is in this file we need to use extern here */
extern int yylineno;

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
  extern SymbolEntry * lookupEntry        (const char * name, LookupType type,
                                    bool err);

  extern Type          typeArray          (RepInteger size, Type refType);
  extern bool          equalType          (Type type1, Type type2);
}

class AST
{
  public:
    virtual ~AST() = default;
    virtual void printAST(std::ostream &out) const = 0;
    virtual void sem() {};
};

inline std::ostream &operator<<(std::ostream &out, const AST &ast)
{
  ast.printAST(out);
  return out;
}

inline void yyerror(const char *msg) {
  fprintf(stderr, "Error: %s at line %d\n", msg, yylineno);
  exit(1);
}

#endif
