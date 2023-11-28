#include "lmatrix.hpp"

LMatrix::LMatrix(AbstractLvalue *lval, Expr *e) : lvalue(lval), expr(e) {}

LMatrix::~LMatrix() { delete lvalue; delete expr; }

void LMatrix::printAST(std::ostream &out) const {
  out << *lvalue;
  out << "[";
  out << *expr;
  out << "]";  
}

void LMatrix::sem()
{
  /* LMatrix is of the form LVALUE[EXPR] 
   * Example for a[5*3][4/2][8+6]: LVALUE = a[15][2], EXPR = 8+6
   */

  /* Perform semantic analysis for EXPR and ensure it is an integer */
  expr->type_check(typeInteger);

  /* Perform semantic analysis for LVALUE (recursively) */
  lvalue->sem();
  
  /* refCount is not increased for this assignment, because refCount is not used
   * to count pointer pointing to a Type object. refCount is used to count the
   * number of other Types that use a given type as refType.
   */
  Type t = lvalue->getType();

  /* The [] operator gets one element from an array.
   * Example: if   a    is of type "array of array of int"
   *          then a[i] is of type "array of int"
   * We check that you do not apply the [] operator to a type that is not array
   * Remember: basic types (typeInteger/typeChar/typeVoid) have refType = NULL
   */
  if(t->refType == nullptr) yyerror("Wrong type: applied [] operator to a non-array type");
  else expr_type = t->refType;
}