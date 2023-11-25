#ifndef __RETURN_HPP__ 
#define __RETURN_HPP__ 

#include "stmt.hpp"
#include "expr.hpp"

class Return : public Stmt
{
  public:
    Return(Expr *e = nullptr);
    ~Return();
    void printAST(std::ostream &out) const override;

  private:
    Expr *expr;
};

#endif
