#ifndef __STMT_HPP__ 
#define __STMT_HPP__ 

#include "ast.hpp"
#include "util.hpp"
#include "returnstack.hpp"

extern ReturnStack return_stack;

/* abstract class */
class Stmt : public AST
{
  public:
    bool willReturn() { return will_return; }
  protected:
    bool will_return = false;
};

#endif
