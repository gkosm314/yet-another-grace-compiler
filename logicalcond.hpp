#ifndef __LOGICALCOND_HPP__ 
#define __LOGICALCOND_HPP__ 

#include "condition.hpp"

class LogicalCond : public Condition
{
  public:
    LogicalCond(Condition *l, char o, Condition *r = nullptr);
    ~LogicalCond();
    void printAST(std::ostream &out) const override;
    void sem() override;

  private:
    Condition *c1;
    char op;
    Condition *c2;
};

#endif
