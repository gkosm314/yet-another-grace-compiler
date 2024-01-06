#ifndef __FPARDEF_HPP__ 
#define __FPARDEF_HPP__ 

#include <vector>

#include "ast.hpp"
#include "parsedtype.hpp"
#include "id.hpp"

class FParDef : public AST
{
  public:
    FParDef(std::vector<Id *> *ids_vec, ParsedType *f, bool ref);
    ~FParDef();
    void printAST(std::ostream &out) const override;
    void setFunction(SymbolEntry *e);
    void sem() override;
    Type getType();
    std::vector<Id*> *getIds();

    /* codegen for parameter definition handled in header.cpp */

  private:
    std::vector<Id*> *ids;
    ParsedType *param_parsed_type;
    Type param_type;
    PassMode pass_mode;

    /* Symbol entry of the function to which this param belongs */
    SymbolEntry *f;
};

#endif
