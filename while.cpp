#include "while.hpp"

While::While(Condition *c, Stmt *s) : cond(c), stmt(s) {}

While::~While() { delete cond; delete stmt; }

void While::printAST(std::ostream &out) const {
  out << "While(" << *cond << "," << *stmt << ")";
}

void While::sem()
{
  cond->type_check(typeBoolean);
  stmt->sem();
}

llvm::Value* While::compile()
{
  /* Grab current function */
  llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();

  /* Create basic blocks*/
  llvm::BasicBlock *WhileCondBB = llvm::BasicBlock::Create(TheContext, "loop", TheFunction);
  llvm::BasicBlock *WhileBodyBB  = llvm::BasicBlock::Create(TheContext, "body", TheFunction);
  llvm::BasicBlock *AfterWhileBB = llvm::BasicBlock::Create(TheContext, "endwhile", TheFunction);
  
  /* Enter condition basic block */
  Builder.CreateBr(WhileCondBB);
  /* Compile condition */
  Builder.SetInsertPoint(WhileCondBB);
  llvm::Value *Cond = cond->compile();
  /* Check condition */
  Builder.CreateCondBr(Cond, WhileBodyBB, AfterWhileBB);

  /* Compile body */
  Builder.SetInsertPoint(WhileBodyBB);
  stmt->compile();
  /* Jump to condition in order to re-evaluate it */
  Builder.CreateBr(WhileCondBB);

  /* Setup compilation for the code that follows after the while-statement*/
  Builder.SetInsertPoint(AfterWhileBB);

  return nullptr;
}