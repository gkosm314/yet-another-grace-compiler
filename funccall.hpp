#ifndef __FUNCCALL_HPP__ 
#define __FUNCCALL_HPP__ 

#include <vector>

#include "lvalue.hpp"
#include "expr.hpp"
#include "id.hpp"

enum FUNC_CALL_ARG
{
  FUNC_CALL_ARG_PASS_BY_VALUE,
  FUNC_CALL_ARG_PASS_BY_REF,
  FUNC_CALL_ARG_PASS_BY_REF_WITH_AUTOCOMPLETE
};

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
    std::vector<FUNC_CALL_ARG> parameters_pass_mode;

    unsigned int callDepth;
    unsigned int calleDeclDepth;
};

#endif
