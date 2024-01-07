#include "assign.hpp"

Assign::Assign(AbstractLvalue *l, Expr *e) : lval(l), expr(e) {}

Assign::~Assign() { delete lval; delete expr; }

void Assign::printAST(std::ostream &out) const {
  out << *lval << " <- " << *expr;
}

void Assign::sem()
{
  /* We check that lval is not a function inside lval->sem() */
  if (!check_assignable_operands(lval, expr)) semError("Bad types (assign)");
  /* If the function has already returned we should not generate code */
  checkIfStmtIsAfterReturn();
}

llvm::Value* Assign::compile()
{
  /* Compile expr to assign */
  llvm::Value *val = expr->compile();
  if (!val)
    return nullptr;

  /* Find the llvmAddr that corresponds to the variable we want to change */
  llvmAddr var_addr = lval->findLLVMAddr();
  if (var_addr == nullptr)
    return nullptr;

  Builder.CreateStore(val, var_addr);
  return nullptr;
}