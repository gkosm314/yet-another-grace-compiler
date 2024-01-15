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
};

#endif
