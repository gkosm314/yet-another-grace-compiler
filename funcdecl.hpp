#ifndef __FUNCDECL_HPP__ 
#define __FUNCDECL_HPP__ 

#include "localdef.hpp"
#include "header.hpp"

class FuncDecl : public LocalDef
{
  public:
    FuncDecl(Header *h);
    ~FuncDecl();
    void printAST(std::ostream &out) const;

  private:
    Header *header; 
};

#endif
