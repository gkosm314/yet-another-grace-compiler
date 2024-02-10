#ifndef __PARSEDTYPE_HPP__ 
#define __PARSEDTYPE_HPP__ 

#include <vector>

#include "ast.hpp"

class ParsedType : public AST
{
  public:
    ParsedType(DATA_TYPE t, std::vector<int> *dims_vec);
    ~ParsedType();
    void printAST(std::ostream &out) const override;
    friend Type toType(ParsedType *t);

  private:
    DATA_TYPE data_type;
    /*
    Possibilites for dims:
    - dims.size() == 0 : The type is a basic one meaning either int or char (not an arr)
    - dims[0] == INT_CONST_BRACKET_LIST_DIMENSION_AUTOCOMPLETE : The type is defined in a function definition without the first dimension eg fun reverse (ref s : char[])
    - In all other cases the dims vector holds the actual dimensions passed by the programmer
    */
    std::vector<int> *dims;
};

#endif
