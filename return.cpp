#include "return.hpp"
#include "ast.hpp"
#include "lexer.hpp"
#include "symbol.h"

Return::Return(Expr *e) : expr(e) {}

Return::~Return() { 
  delete expr;
}

void Return::printAST(std::ostream &out) const {
  out << "Return(";
  if (expr != nullptr)
  {
    out << ", ";
    out << *expr;
  }
  out << ")";
}

void Return::sem()
{
  /* This is a reference to a stack object that will be popped
     at the end of the function definition. We should not store it. */  
  Type expected_ret_type = return_stack.getType();
  
  /* Check that return statement returns the correct type */
  if(equalType(expected_ret_type, typeVoid))
  {
    /* void function may end with "return;" but not with "return e;" */
    if(expr != nullptr) semError("Return did not expect an expression");
  }
  else if(equalType(expected_ret_type, typeInteger) || equalType(expected_ret_type, typeChar))
  {
    /* int/char functions should return int/var expression respectively */
    if(expr != nullptr) expr->type_check(expected_ret_type);
    else semError("Return expected an expression");
  }
  else
  {
    // We should never reach this point
    semError("Return has bad expected_ret_type - execution should never reach this point!");
  }

  /* Update the stack in order to:
   *  - check if the function has a return statement (for non-void functions)
   *  - avoid generating code for statements that follow */
  return_stack.setFound();

  /* If the function has already returned we should not generate code */
  checkIfStmtIsAfterReturn();

  llmv_type = getLLVMType(expected_ret_type);
}


llvm::Value* Return::compile()
{
  llvm::Value *RetVal;

  if(expr != nullptr) {
    RetVal = expr->compile();
    Builder.CreateRet(RetVal);
  }
  else
    Builder.CreateRetVoid();
  
  return nullptr;
}