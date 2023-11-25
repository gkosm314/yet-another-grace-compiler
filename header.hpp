#ifndef __HEADER_HPP__ 
#define __HEADER_HPP__ 

#include <vector>

#include "ast.hpp"
#include "fpardef.hpp"

class Header : public AST
{
  public:
    Header(Id *i, std::vector<FParDef *> *vec_defs, DATA_TYPE dt);
    ~Header();
    void printAST(std::ostream &out) const override;

  private:
    Id *id;
    std::vector<FParDef *> *fpar_defs;
    DATA_TYPE ret_type;
};

#endif
