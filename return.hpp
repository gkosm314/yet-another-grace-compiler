#ifndef __RETURN_HPP__ 
#define __RETURN_HPP__ 

#include "stmt.hpp"
#include "expr.hpp"

class Return : public Stmt
{
  public:
    Return(DATA_TYPE parsed_ret_type, Expr *e = nullptr);
    ~Return();
    void printAST(std::ostream &out) const override;
    void sem() override;

  private:
    Type  expected_ret_type;
    Expr *expr;
};

#endif
