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
  /* If the compiled stmt is a return statement or a block that contains a return statement,
   * then appending a "br" is useless and will lead to invalid LLVM IR
   * because the "ThenBB" BasicBlock will have two terminators */
  if(!stmt1->willReturn())
    Builder.CreateBr(AfterBB);

  /* Compile "else" */
  Builder.SetInsertPoint(ElseBB);
  if (stmt2 != nullptr)
    stmt2->compile();
  /* If the compiled stmt is a return statement or a block that contains a return statement,
   * then appending a "br" is useless and will lead to invalid LLVM IR
   * because the "ElseBB" BasicBlock will have two terminators */
  if (!stmt2 || !stmt2->willReturn())
    Builder.CreateBr(AfterBB);

  /* Setup compilation for the code that follows after the if-statement */
  Builder.SetInsertPoint(AfterBB);

  return nullptr;
}