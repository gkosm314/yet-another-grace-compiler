#include <iostream>
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

  private:
    Header *header;
    std::vector<LocalDef *> *local_defs;
    Block *block;
};