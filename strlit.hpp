#ifndef __STRLIT_HPP__ 
#define __STRLIT_HPP__ 

#include "abstractlvalue.hpp"

class StrLit : public AbstractLvalue
{
  public:
    StrLit(std::string s);
    void printAST(std::ostream &out) const override;

  private:
    std::string str;
};

#endif
