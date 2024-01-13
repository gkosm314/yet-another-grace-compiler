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
            /* If the parameter was passed by reference, we have to dereference it to use its value */
            if(e->u.eParameter.mode == PASS_BY_REFERENCE)
            {
                isRef = true;
                if(e->u.eParameter.type->autocompleteSize) isAutocompleteParam = true;
            }
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

    /* Difference between the nesting level of the declaration and
     * the nesting level of the expression that uses this particular lvalue */
    nestingDepth = currentScope->nestingLevel - e->nestingLevel;
    if(nestingDepth > 0) escapeVars.insert(mangled_name);
}

llvmAddr LValue::findLLVMAddr()
{
    llvmAddr var_addr = varMap[mangled_name];
    if (!var_addr)
        /* Execution should never reach this point */
        return nullptr;

    /* Returns the stack address of the value (from alloca)
     *   -   normal variable        -> the stack address is inside the map      (direct access)
     *   -  reference to a variable -> the stack address is the value I store   (indirect access - dereference)
     */
    if(!isRef) return var_addr;
    else return Builder.CreateLoad(llvm::PointerType::get(getLLVMType(expr_type), 0), var_addr);
}

llvmAddr LValue::findLLVMAddrAux(std::vector<llvm::Value*> *offsets, llvmType ** t)
{
    /* TODO: add comments*/
    /* TODO: validate that this works even if the parameter was passed to an outer function and we used it as an escape parameter*/
    if(!isAutocompleteParam)
    {
        /* push 0 in the beginning of the offsets to dereference the GEP pointer */
        offsets->insert(offsets->begin(), c64(0));
    }

    /* end of the recursion - return the address and the type of the matrix */
    *t = getLLVMType(expr_type);
    return findLLVMAddr();
}

llvm::Value* LValue::compile()
{
    llvmAddr var_addr = findLLVMAddr();
    if (!var_addr)
        /* Execution should never reach this point */
        return nullptr;

    /* Load the value */
    return Builder.CreateLoad(getLLVMType(expr_type), var_addr);
}
