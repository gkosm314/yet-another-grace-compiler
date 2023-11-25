#include <iostream>

#include "expr.hpp"

class CharConst : public Expr 
{
  public:
    CharConst(char c);
    void printAST(std::ostream &out) const override;
 
  private:
    char val;
};