#include "logicalcond.hpp"
#include "symbol.h"

LogicalCond::LogicalCond(Condition *l, char o, Condition *r): c1(l), op(o), c2(r) {}

LogicalCond::~LogicalCond() { delete c1; delete c2; }

void LogicalCond::printAST(std::ostream &out) const {
  out << op << "(" << *c1;
  if (c2 != nullptr)
    out << ", " << *c2 << ")";
}

void LogicalCond::sem()
{
  c1->type_check(typeBoolean);
  if (c2 != nullptr)
    c2->type_check(typeBoolean);

  expr_type = typeBoolean;
}

llvm::Value* LogicalCond::compile() {
  llvm::Value *L = c1->compile();
  llvm::Value *R;

  if (!L)
    return nullptr;
  
  /* 'not' logical condition*/
  if (op == 'n')
    return Builder.CreateNot(L, "logicalnottemp");
  
  /* 'and' and 'or' logical conditions */ 
  /* Grab current function and create basic blocks */
  llvm::Function *TheFunction = Builder.GetInsertBlock()->getParent();
  llvm::BasicBlock *NoSkipBB  = llvm::BasicBlock::Create(TheContext, "noskip", TheFunction);
  llvm::BasicBlock *SkipBB    = llvm::BasicBlock::Create(TheContext, "skip", TheFunction);
  llvm::BasicBlock *CurBB = Builder.GetInsertBlock();
  
  /* 
   * Short circuit:
   * and: If L is false, then we skip R 
   * or: If L is true, then we skip R
   */
  if (op == 'a')
    Builder.CreateCondBr(L, NoSkipBB, SkipBB);
  else if (op == 'o')
    Builder.CreateCondBr(L, SkipBB, NoSkipBB);
  else
    /* Execution should never reach this point */
    return nullptr;
  
  /* Compile c2 */
  Builder.SetInsertPoint(NoSkipBB);
  R = c2->compile();

  /* Create the Instruction */ 
  llvm::Value *opVal;
  if (op == 'a')
    opVal = Builder.CreateAnd(L, R, "logicalandtemp");
  else if (op == 'o')
    opVal = Builder.CreateOr(L, R, "logicalandtemp");
  else 
    /* Execution should never reach this point */
    return nullptr;
  
  /*
   * This is important, in case of multiple chained logical operations we want the phi instruction below
   * to have the correct incoming edge
  */
  llvm::BasicBlock *OpValBB = Builder.GetInsertBlock();
  Builder.CreateBr(SkipBB);

  /* SkipBB */
  Builder.SetInsertPoint(SkipBB);
  llvm::PHINode *val = Builder.CreatePHI(L->getType(), 2, "phival");
  val->addIncoming(L, CurBB);
  val->addIncoming(opVal, OpValBB);
  return val;
}