#include <iostream>

#include "stmt.hpp"
#include "abstractlvalue.hpp"

class Assign : public Stmt 
{
  public:
    Assign(AbstractLvalue *l, Expr *e);
    ~Assign();
    
  private:
    AbstractLvalue *lval;
    Expr *expr;
};