#ifndef __RETURN_HPP__ 
#define __RETURN_HPP__ 

#include "stmt.hpp"
#include "expr.hpp"
#include "returnstack.hpp"

extern ReturnStack return_stack;

class Return : public Stmt
{
  public:
    Return(Expr *e = nullptr);
    ~Return();
    void printAST(std::ostream &out) const override;
    void sem() override;
    llvm::Value* compile() override;

  private:
    Expr      *expr;
    llvmType  *llmv_type;
};

#endif
