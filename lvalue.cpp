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
            yyerror("LValue cannot be a function!");
            break;
        default:
            yyerror("lvalue-sem(): invalid entry - execution should never reach this point");
            break;
    }
}