#ifndef __ABSTRACTLVALUE_HPP__ 
#define __ABSTRACTLVALUE_HPP__ 

#include "expr.hpp"

/* abstract class */
class AbstractLvalue : public Expr
{
  public:
    /* TODO: think if this should be pure virtual (=0) */
    virtual llvmAddr findLLVMAddr() { return nullptr; }
    virtual llvmAddr findLLVMAddrAux(std::vector<llvm::Value*> *offsets, llvmType ** t) { return nullptr; }
    virtual bool hasAutocompleteDimension() = 0;
};

#endif
