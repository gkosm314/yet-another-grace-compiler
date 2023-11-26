#ifndef __CHARCONST_HPP__ 
#define __CHARCONST_HPP__ 

#include "expr.hpp"

class CharConst : public Expr 
{
  public:
    CharConst(char c);
    void printAST(std::ostream &out) const override;
    void sem() override;
 
  private:
    char val;
};

#endif
