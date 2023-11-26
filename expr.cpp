#include "expr.hpp"

void Expr::type_check(Type expected_type)
{
    sem();

    if(!equalType(expr_type, expected_type))
    {
        yyerror("Type mismatch");
    }
}