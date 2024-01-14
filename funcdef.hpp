#ifndef __FUNCDEF_HPP__ 
#define __FUNCDEF_HPP__ 

#include <vector>

#include "localdef.hpp"
#include "vardef.hpp"
#include "header.hpp"
#include "block.hpp"

class FuncDef : public LocalDef
{
  public:
    FuncDef(Header *h,  std::vector<LocalDef *> *vector_def, Block *b);
    ~FuncDef();
    void printAST(std::ostream &out) const override;
    void hasProgramSignature();
    void sem() override;
    llvm::Function* compile() override;

    virtual void setOuterFunc(std::string outer_func_mangled_name) override;

  private:
    Header *header;
    std::vector<LocalDef*> *local_defs;
    Block *block;
    bool void_ret_type_without_ret_stmt = false;

    void createStackFrame(llvmType *stack_frame_type);
    llvmType * generateStackFrameStruct();
};

#endif
