#ifndef __ID_HPP__ 
#define __ID_HPP__ 

#include "abstractlvalue.hpp"

class Id : public AbstractLvalue
{
  public:
    Id(std::string s);
    void printAST(std::ostream &out) const override;
    const char * getName() const;

  private:
    std::string name;
};



#endif
