#ifndef __ID_HPP__ 
#define __ID_HPP__ 

#include "abstractlvalue.hpp"

class Id : public AbstractLvalue
{
  public:
    Id(std::string s);
    void printAST(std::ostream &out) const override;

  private:
    std::string str;
};



#endif
