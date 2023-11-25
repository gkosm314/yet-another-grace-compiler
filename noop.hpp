#ifndef __NOOP_HPP__ 
#define __NOOP_HPP__ 

#include "stmt.hpp"

class NoOp : public Stmt
{
  public:
    NoOp();
    void printAST(std::ostream &out) const;
};

#endif
