#ifndef __ID_HPP__ 
#define __ID_HPP__ 

#include "ast.hpp"

/* This class could be removed as it is essentially a wrapper for string::std */
class Id : public AST
{
  public:
    Id(std::string s);
    void printAST(std::ostream &out) const override;
    const char * getName() const;

  private:
    std::string name;
};



#endif
