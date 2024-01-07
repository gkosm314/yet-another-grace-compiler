#ifndef __FUNCCALL_HPP__ 
#define __FUNCCALL_HPP__ 

#include <vector>

#include "lvalue.hpp"
#include "expr.hpp"
#include "id.hpp"

/* In situations like a <- f(); the rhs has to implement eval() */ 
class FuncCall : public Expr 
{
  public:
    FuncCall(Id *f, std::vector<Expr *> *par);
    ~FuncCall();
    void printAST(std::ostream &out) const override;
    void sem() override;
    llvm::Value* compile() override;

  private:
    Id *func_name;
    std::string mangled_name;
    std::vector<Expr*> *parameters_expr_list;
    std::vector<bool>   parameters_pass_by_ref;
};

#endif
