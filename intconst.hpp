#include "expr.hpp"

class IntConst : public Expr 
{
  public:
    IntConst(int v);
    void printAST(std::ostream &out) const override;
  
  private:
    const int val; 
};