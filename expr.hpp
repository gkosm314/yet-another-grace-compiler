#ifndef __EXPR_HPP__ 
#define __EXPR_HPP__ 

#include "ast.hpp"
#include "util.hpp"

/* abstract class */
class Expr : public AST
{
  public:
    Type getType();
    void type_check(Type expected_type);
    void type_check_param(Type expected_type);
    virtual bool isLvalue();

  protected:
    Type expr_type = nullptr;
};

bool check_assignable_operands(Expr *left, Expr *right);

#endif
