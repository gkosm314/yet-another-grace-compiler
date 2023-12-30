#ifndef __INTCONST_HPP__ 
#define __INTCONST_HPP__ 

#include "expr.hpp"

class IntConst : public Expr 
{
  public:
    IntConst(int v);
    void printAST(std::ostream &out) const override;
    void sem() override;
    llvm::Value* compile() override;
  
  private:
    const int val; 
};

#endif
