#include "ast.hpp"
#include "symbol.h"

/* abstract class */
class Expr : public AST
{
  public:
    
  protected:
    Type expr_type;
};