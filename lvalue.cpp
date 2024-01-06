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

llvm::AllocaInst* LValue::findAllocaInst()
{
    return varMap[mangled_name];
}

llvm::Value* LValue::compile()
{
    llvm::AllocaInst *var_addr = varMap[mangled_name];
    if (!var_addr)
        /* Execution should never reach this point */
        return nullptr;

    /* Load the value */
    return Builder.CreateLoad(var_addr->getAllocatedType(), var_addr);    
}