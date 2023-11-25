#include <iostream>
#include <vector>

#include "localdef.hpp"
#include "parsedtype.hpp"
#include "id.hpp"

class VarDef : public LocalDef
{
  public:
    VarDef(std::vector<Id *> *ids_vec, ParsedType *t);
    ~VarDef();
    void printAST(std::ostream &out) const override;

  private:
    std::vector<Id *> *ids; // Will never be nullptr by construction of parser
    ParsedType *type;
};
