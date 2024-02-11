#ifndef __PROGRAM_HPP__ 
#define __PROGRAM_HPP__ 

#include "ast.hpp"
#include "funcdef.hpp"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/Support/Host.h"


class Program : public AST
{
  public:
    Program(FuncDef *f);
    ~Program();
    void printAST(std::ostream &out) const override;
    void sem() override;
    llvm::Value* compile() override;
    void dumpFinalCode(std::string Filename);
    void dumpIntermediateCode(std::string Filename);

  private:
    FuncDef *fd;
};

#endif
