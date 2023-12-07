#ifndef __RETURN_HPP__ 
#define __RETURN_HPP__ 

#include "stmt.hpp"
#include "expr.hpp"

#include <vector>

extern std::vector<Type> ret_types_stack;

class Return : public Stmt
{
  public:
    Return(Expr *e = nullptr);
    ~Return();
    void printAST(std::ostream &out) const override;
    void sem() override;

  private:
    Expr *expr;
};

#endif
