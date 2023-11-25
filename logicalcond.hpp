#include "condition.hpp"

class LogicalCond : public Condition
{
  public:
    LogicalCond(Condition *l, char o, Condition *r = nullptr);
    ~LogicalCond();
    void printAST(std::ostream &out) const override;

  private:
    Condition *c1;
    char op;
    Condition *c2;
};