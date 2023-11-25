#include <iostream>

#include "abstractlvalue.hpp"

class Id : public AbstractLvalue
{
  public:
    Id(std::string s);
    void printAST(std::ostream &out) const override;

  private:
    std::string str;
};

