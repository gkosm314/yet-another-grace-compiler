#include <iostream>

#include "localdef.hpp"
#include "header.hpp"

class FuncDecl : public LocalDef
{
  public:
    FuncDecl(Header *h);
    ~FuncDecl();
    void printAST(std::ostream &out);

  private:
    Header *header; 
};