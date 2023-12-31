#include "program.hpp"

Program::Program(FuncDef *f) : fd(f) {}

Program::~Program() { delete fd; }

void Program::printAST(std::ostream &out) const {
  out << "Program(" << *fd << ")";
}

void Program::sem()
{
  fd->hasProgramSignature();
  fd->sem();
}

llvm::Value* Program::compile()
{
  llvm_codegen();

  /* Compile */
  fd->compile();
  
  /* Verify the IR */
  bool bad = verifyModule(*TheModule, &llvm::errs());
  if (bad) {
    std::cerr << "The IR is bad!" << std::endl;
    TheModule->print(llvm::errs(), nullptr);
    std::exit(1);
  }

  /* Print out the IR */
  TheModule->print(llvm::outs(), nullptr);
  return nullptr;
}