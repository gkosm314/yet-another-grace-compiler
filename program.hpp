#ifndef __PROGRAM_HPP__ 
#define __PROGRAM_HPP__ 

#include "ast.hpp"
#include "funcdef.hpp"

class Program : public AST
{
  public:
    Program(FuncDef *f);
    ~Program();
    void printAST(std::ostream &out) const override;

  private:
    FuncDef *fd;
};

#endif
