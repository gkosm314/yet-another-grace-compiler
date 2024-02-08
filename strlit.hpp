#ifndef __STRLIT_HPP__ 
#define __STRLIT_HPP__ 

#include <string>

#include "abstractlvalue.hpp"

class StrLit : public AbstractLvalue
{
  public:
    StrLit(std::string s);
    ~StrLit();
    void printAST(std::ostream &out) const override;
    void sem() override;
    llvmAddr findLLVMAddr() override;
    bool hasAutocompleteDimension() override;

  private:
    std::string str;
};

#endif
