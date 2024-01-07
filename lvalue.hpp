#ifndef __LVALUE_HPP__ 
#define __LVALUE_HPP__ 

#include "abstractlvalue.hpp"
#include "id.hpp"

/* This class could be removed as it is essentially a wrapper for string::std */
class LValue : public AbstractLvalue
{
  public:
    LValue(Id *i);
    ~LValue();
    void printAST(std::ostream &out) const override;
    void sem() override;
    llvm::Value* compile() override;
    llvmAddr findLLVMAddr() override;
    llvmAddr findLLVMAddrAux(std::vector<llvm::Value*> *offsets, llvmType ** t) override;

  private:
    Id *id;
    std::string mangled_name;
    bool isRef = false;
    bool isAutocompleteParam = false;
};



#endif
