#include <iostream>

#include "abstractlvalue.hpp"

class LMatrix : public AbstractLvalue
{
  public:
    LMatrix(AbstractLvalue *lval, Expr *e);
    ~LMatrix();
    void printAST(std::ostream &out) const override;

  private:
    AbstractLvalue *lvalue;
    Expr *expr;
};