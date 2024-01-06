#ifndef __ABSTRACTLVALUE_HPP__ 
#define __ABSTRACTLVALUE_HPP__ 

#include "expr.hpp"

/* abstract class */
class AbstractLvalue : public Expr
{
  public:
    bool isLvalue() override;
    /* TODO: think if this should be pure virtual (=0) */
    virtual llvm::AllocaInst * findAllocaInst() { return nullptr; }
};

#endif
