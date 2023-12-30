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
  protected:
    bool generate_code = true; /* By default we generate code for a statement*/
    void checkIfStmtIsAfterReturn()
    {
      if(return_stack.returnFound()) generate_code = false;
    }
};

#endif
