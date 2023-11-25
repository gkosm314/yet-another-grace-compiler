#ifndef __FPARDEF_HPP__ 
#define __FPARDEF_HPP__ 

#include <iostream>
#include <vector>

#include "ast.hpp"
#include "parsedtype.hpp"
#include "id.hpp"

class FParDef : public AST
{
  public:
    FParDef(std::vector<Id *> *ids_vec, ParsedType *f, bool b);
    ~FParDef();
    void printAST(std::ostream &out) const override;

  private:
    std::vector<Id *> *ids;
    ParsedType *fpar_type;
    bool ref;
};

#endif
