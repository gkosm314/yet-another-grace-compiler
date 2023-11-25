#include "expr.hpp"

class UnaryOp : public Expr 
{
  public:
    UnaryOp(char o, Expr *e);
    ~UnaryOp();
    void printAST(std::ostream &out) const override;

  private:
    Expr *expr;
    char op;
};
