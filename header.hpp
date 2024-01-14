#ifndef __HEADER_HPP__ 
#define __HEADER_HPP__ 

#include <vector>

#include "ast.hpp"
#include "util.hpp"
#include "fpardef.hpp"
#include "returnstack.hpp"

extern ReturnStack return_stack;

class Header : public AST
{
  public:
    Header(Id *i, std::vector<FParDef *> *vec_defs, DATA_TYPE dt);
    ~Header();
    void printAST(std::ostream &out) const override;
    size_t getParametersCount();
    Type getReturnType();
    void setForward();
    void sem() override;
    llvm::Function* compile() override;

    std::string getMangledName();
    std::vector<llvmType*> getParamLLVMTypes();
    std::vector<std::string> getParamMangledNames();

    void pushStaticLinkForStackFrameStruct(std::vector<std::string> *names, std::vector<llvmType*> *types);
    void pushFieldsForStackFrameStruct(std::vector<std::string> *names, std::vector<llvmType*> *types, std::vector<bool> *isref);

  private:
    Id *id;
    std::vector<FParDef*> *fpar_defs;
    Type ret_type;
    
    std::string mangled_name;
    bool isForward = false;

    /* The following fields are valid only after compile() has been called*/
    std::vector<llvmType*>   param_types;
    std::vector<std::string> mangled_param_names;
};

#endif
