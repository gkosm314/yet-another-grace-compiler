#include "expr.hpp"

Type Expr::getType()
{
    /* Assumption: sem() or type_check() was called before this is called */
    return expr_type;
}

void Expr::type_check(Type expected_type)
{
    sem();

    if(!equalType(expr_type, expected_type))
    {
        yyerror("Type mismatch");
    }
}
