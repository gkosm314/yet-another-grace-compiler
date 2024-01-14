#ifndef __FPARDEF_HPP__ 
#define __FPARDEF_HPP__ 

#include <vector>

#include "util.hpp"
#include "ast.hpp"
#include "parsedtype.hpp"
#include "id.hpp"

class FParDef : public AST
{
  public:
    FParDef(std::vector<Id *> *ids_vec, ParsedType *f, bool ref);
    ~FParDef();
    void printAST(std::ostream &out) const override;
    void setFunction(SymbolEntry *e);
    void sem() override;
    llvm::Value* compile() override; /* This function is empty - we should never use it */
    llvm::Value* compile(std::vector<std::string> * signature_mangled_names, std::vector<llvmType*> * signature_types);

    void pushFieldsForStackFrameStruct(std::vector<std::string> *names, std::vector<llvmType*> *types, std::vector<bool> *isref);

  private:
    std::vector<Id*> *ids;
    ParsedType *param_parsed_type;
    Type param_type;
    PassMode pass_mode;

    /* Symbol entry of the function to which this param belongs */
    SymbolEntry *f;
    unsigned int scope_id;
};

#endif
