#ifndef __WHILE_HPP__ 
#define __WHILE_HPP__ 

#include "stmt.hpp"
#include "condition.hpp"

class While : public Stmt 
{
  public:
    While(Condition *c, Stmt *s);
    ~While();
    void printAST(std::ostream &out) const override;
    void sem() override;

  private:
    Condition *cond;
    Stmt *stmt;
};

#endif
