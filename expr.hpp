#ifndef __EXPR_HPP__ 
#define __EXPR_HPP__ 

#include "ast.hpp"

/* abstract class */
class Expr : public AST
{
  public:
    Type getType();
    void type_check(Type expected_type);

  protected:
    Type expr_type = nullptr;
};

#endif
