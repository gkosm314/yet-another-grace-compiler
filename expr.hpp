#ifndef __EXPR_HPP__ 
#define __EXPR_HPP__ 

#include "ast.hpp"

/* abstract class */
class Expr : public AST
{
  public:
    void type_check(Type expected_type);

  protected:
    Type expr_type;
};

#endif
