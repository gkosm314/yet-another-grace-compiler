#ifndef __EXPR_HPP__ 
#define __EXPR_HPP__ 

#include "ast.hpp"
#include "symbol.h"

/* abstract class */
class Expr : public AST
{
  public:
    
  protected:
    Type expr_type;
};

#endif
