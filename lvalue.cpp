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

    /* If there is a difference between the nesting level of the declaration and
     * the nesting level of the expression that uses this particular lvalue,
     * then the variable is an escape variable */
    lvalueDepth = currentScope->nestingLevel;
    varDeclDepth = e->nestingLevel;
    if(lvalueDepth > varDeclDepth)
    {
        escapeVars.insert(mangled_name);
        isEscape = true;
        /* every escape var is treated as reference to a stack allocated variable of an outer function */
        isRef = true;
    }
}

llvmAddr LValue::findLLVMAddr()
{
    llvmAddr var_addr = nullptr;
    if(!isEscape) var_addr = varMap[mangled_name];
    else var_addr = getAllocaAddrOfEscapeVar();
    
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

llvmAddr LValue::getAllocaAddrOfEscapeVar()
{
    /* type of the stack frame inside which we will find a reference to the lvalue */
    llvmType *stack_frame_type;
    /* get address of the stack frame inside which we will find a reference to the lvalue */
    llvmAddr stack_frame_addr = walkupStaticLinkChain(varDeclDepth, lvalueDepth, &stack_frame_type);
    /* get the position of the reference to the lvalue inside the stack frame */
    unsigned int field_pos = stackframePos[mangled_name];

    return Builder.CreateStructGEP(stack_frame_type, stack_frame_addr, field_pos);
}

bool LValue::hasAutocompleteDimension()
{
    return isAutocompleteParam;
}