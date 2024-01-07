#ifndef __LMATRIX_HPP__ 
#define __LMATRIX_HPP__ 

#include "abstractlvalue.hpp"

class LMatrix : public AbstractLvalue
{
  public:
    LMatrix(AbstractLvalue *lval, Expr *e);
    ~LMatrix();
    void printAST(std::ostream &out) const override;
    void sem() override;
    llvm::Value* compile() override;

    llvmAddr findLLVMAddrAux(std::vector<llvm::Value*> *offsets, llvmType ** t) override;
    llvmAddr findLLVMAddr() override;

  private:
    AbstractLvalue *lvalue;
    Expr *expr;
};

#endif
