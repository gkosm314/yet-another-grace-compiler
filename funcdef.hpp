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

    std::string mangled_name;

    /* This vector defines the types of the fields inside the struct
    * For every escaping parameter/variable we need a field that store a reference to the escaping variable
    * We maintain the same order that is used in local_defs vector.
    */
    std::vector<std::string> escapeNames; /* mangled */
    std::vector<llvmType*> escapeTypes;
    std::vector<bool> escapeIsRef;

    void createStackFrame(llvmType *stack_frame_type);
    void populateStackFrame();
    llvmType * generateStackFrameStruct();

    void optimize(llvm::Function *f);
};

#endif
