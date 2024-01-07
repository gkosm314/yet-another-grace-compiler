#include "lvalue.hpp"

LValue::LValue(Id *i) : id(i) {}

LValue::~LValue()
{
    delete id;
}

void LValue::printAST(std::ostream &out) const
{
    out << "LValue(" << *id << ")";
}

void LValue::sem()
{
    /* If the lvalue is not found, lookupEntry will throw an error */
    SymbolEntry *e = lookupEntry(id->getName(), LOOKUP_ALL_SCOPES, true);

    switch (e->entryType)
    {
        case ENTRY_VARIABLE:
            expr_type = e->u.eVariable.type;
            break;
        case ENTRY_PARAMETER:
            expr_type = e->u.eParameter.type;
            break;
        case ENTRY_FUNCTION:
            semError("LValue cannot be a function!");
            break;
        default:
            semError("lvalue-sem(): invalid entry - execution should never reach this point");
            break;
    }   

    /* Keep mangled name */
    mangled_name = mangle(id->getName(), e->scopeId);
}

llvmAddr LValue::findLLVMAddr()
{
    return varMap[mangled_name];
}

llvmAddr LValue::findLLVMAddrAux(std::vector<llvm::Value*> *offsets, llvmType ** t)
{
    /* push 0 in the beginning of the offsets to dereference the GEP pointer */
    offsets->insert(offsets->begin(), c64(0));
    *t = getLLVMType(expr_type);
    /* end of the recursion - return the base of the matrix */
    return findLLVMAddr();
}

llvm::Value* LValue::compile()
{
    llvmAddr var_addr = varMap[mangled_name];
    if (!var_addr)
        /* Execution should never reach this point */
        return nullptr;

    /* Load the value */
    return Builder.CreateLoad(getLLVMType(expr_type), var_addr);    
}
