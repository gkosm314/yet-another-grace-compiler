#include "condition.hpp"

class NumericCond : public Condition
{
  public:
    NumericCond(Expr *l, char o, Expr *r);
    ~NumericCond();
    void printAST(std::ostream &out) const override;

  private:
    Expr *left;
    char op;
    Expr *right;
};
