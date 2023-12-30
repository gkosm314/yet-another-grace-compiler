#ifndef __FUNCDEF_HPP__ 
#define __FUNCDEF_HPP__ 

#include <vector>

#include "localdef.hpp"
#include "header.hpp"
#include "block.hpp"

class FuncDef : public LocalDef
{
  public:
    FuncDef(Header *h,  std::vector<LocalDef *> *vector_def, Block *b);
    ~FuncDef();
    void printAST(std::ostream &out) const override;
    void hasProgramSignature();
    void sem() override;
    llvm::Value* compile() override;

  private:
    Header *header;
    std::vector<LocalDef*> *local_defs;
    Block *block;
};

#endif
