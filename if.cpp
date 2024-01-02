#include "if.hpp"

If::If(Condition *c, Stmt *s1, Stmt *s2) : cond(c),  stmt1(s1), stmt2(s2) {}

If::~If() { delete cond; delete stmt1; delete stmt2; }

void If::printAST(std::ostream &out) const {
  out << "If(" << *cond << ", " << *stmt1;
  if (stmt2 != nullptr) out << ", " << *stmt2;
  out << ")";
}

void If::sem()
{
  cond->type_check(typeBoolean);
  stmt1->sem();
  if (stmt2 != nullptr) stmt2->sem();

  /* If the function has already returned we should not generate code */
  checkIfStmtIsAfterReturn();  
}

llvm::Value* If::compile() 
{
  /* Compile condition */
  llvm::Value *v = cond->compile();

  /* Grab current function */
  llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();

  /* Create basic blocks*/
  llvm::BasicBlock *ThenBB  = llvm::BasicBlock::Create(TheContext, "then", TheFunction);
  llvm::BasicBlock *ElseBB  = llvm::BasicBlock::Create(TheContext, "else", TheFunction);
  llvm::BasicBlock *AfterBB = llvm::BasicBlock::Create(TheContext, "endif", TheFunction);
  
  /* Check condition and branch to "then" or to "else" */
  Builder.CreateCondBr(v, ThenBB, ElseBB);

  /* Compile "then" */
  Builder.SetInsertPoint(ThenBB);
  stmt1->compile();
  Builder.CreateBr(AfterBB);

  /* Compile "else" */
  Builder.SetInsertPoint(ElseBB);
  if (stmt2 != nullptr)
    stmt2->compile();
  Builder.CreateBr(AfterBB);

  /* Setup compilation for the code that follows after the if-statement */
  Builder.SetInsertPoint(AfterBB);

  return nullptr;
}