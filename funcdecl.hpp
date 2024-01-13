#ifndef __FUNCDECL_HPP__ 
#define __FUNCDECL_HPP__ 

#include "localdef.hpp"
#include "header.hpp"

class FuncDecl : public LocalDef
{
  public:
    FuncDecl(Header *h);
    ~FuncDecl();
    void printAST(std::ostream &out) const override;
    void sem() override;
    llvm::Value* compile() override;

    virtual void setOuterFunc(std::string outer_func_mangled_name) override;

  private:
    Header *header; 
};

#endif
