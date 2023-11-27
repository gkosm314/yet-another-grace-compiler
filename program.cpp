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