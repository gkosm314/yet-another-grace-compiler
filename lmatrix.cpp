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
  if(t->refType == nullptr) semError("Wrong type: applied [] operator to a non-array type");
  else expr_type = t->refType;
}

llvmAddr LMatrix::findLLVMAddrAux(std::vector<llvm::Value*> *offsets, llvmType ** t)
{
  /* Compile expr */
  llvm::Value *off = expr->compile();
  if(off == nullptr)
    return nullptr;

  /* Push my offset in the vector that is passed by reference */
  offsets->insert(offsets->begin(), off);

  /* Call the aux function for your LHS
   * at the end of the recursion the llvmAddr of the matrix will be returned by the LValue node
   * every intermediate LMatrix will push_front its own offset */
  return lvalue->findLLVMAddrAux(offsets, t);
}

llvmAddr LMatrix::findLLVMAddr()
{
  /* example: for "a[4][7][2]"
   *      base_addr  = llvmAddr of "a"
   *      offsets    = <0,4,7,2> (0 is used to dereference the GEP pointer) 
   */
  std::vector<llvm::Value*> offsets;
  llvmType* base_type;
  llvmAddr  base_addr = findLLVMAddrAux(&offsets, &base_type); /* called by this object to append its offset too */

  return Builder.CreateGEP(base_type, base_addr, offsets);
}

llvm::Value* LMatrix::compile()
{
  llvmAddr var_addr = findLLVMAddr();
  if (!var_addr)
      /* Execution should never reach this point */
      return nullptr;

  /* Load the value */
  /* TODO: maybe change to return llvmAddr if this is not a int/char element */
  return Builder.CreateLoad(getLLVMType(expr_type), var_addr);    
}
