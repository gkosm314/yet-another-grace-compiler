#include "stmt.hpp"
#include "condition.hpp"

class If : public Stmt
{
  public:
    If(Condition *c, Stmt *s1, Stmt *s2 = nullptr);
    ~If();
    void printAST(std::ostream &out);
  private:
    Condition *cond;
    Stmt      *stmt1;
    Stmt      *stmt2;
};
