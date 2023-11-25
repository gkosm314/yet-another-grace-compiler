#include "stmt.hpp"
#include "condition.hpp"

class While : public Stmt 
{
  public:
    While(Condition *c, Stmt *s);
    ~While();
    void printAST(std::ostream &out) const override;

  private:
    Condition *cond;
    Stmt *stmt;
};