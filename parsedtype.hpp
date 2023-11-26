#ifndef __PARSEDTYPE_HPP__ 
#define __PARSEDTYPE_HPP__ 

#include <vector>

#include "ast.hpp"

#define INT_CONST_BRACKET_LIST_DIMENSION_AUTOCOMPLETE -1

/* This enum is used during the parsing.
   It is different from the enums used in "symbol.h", which are used for the semantic analysis. */
enum DATA_TYPE { DATA_TYPE_int, DATA_TYPE_char, DATA_TYPE_nothing };

class ParsedType : public AST
{
  public:
    ParsedType(DATA_TYPE t, std::vector<int> *dims_vec);
    ~ParsedType();
    void printAST(std::ostream &out) const override;

  private:
    DATA_TYPE data_type;
    /*
    Possibilites for dims:
    - dims.size() == 0 : The type is a basic one meaning either int or char (not an arr)
    - dims[0] == INT_CONST_BRACKET_LIST_DIMENSION_AUTOCOMPLETE : The type is defined in a function definition without the first dimension eg fun reverse (ref s : char[])
    TODO: Make sure that the user can't somehow define the dimension to be equal to INT_CONST_BRACKET_LIST_DIMENSION_AUTOCOMPLETE eg fun reverse (ref s : char[-1]) should produce an error
    - In all other cases the dims vector holds the actual dimensions passed by the programmer
    */
    std::vector<int> *dims;
};

#endif
