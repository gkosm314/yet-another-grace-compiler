#ifndef __ABSTRACTLVALUE_HPP__ 
#define __ABSTRACTLVALUE_HPP__ 

#include "expr.hpp"

/* abstract class */
class AbstractLvalue : public Expr
{
  public:
    virtual llvmAddr findLLVMAddr() = 0;
    virtual llvmAddr findLLVMAddrAux(std::vector<llvm::Value*> *offsets, llvmType ** t) = 0;
    virtual bool hasAutocompleteDimension() = 0;
};

#endif
