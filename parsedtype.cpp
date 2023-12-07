#include "parsedtype.hpp"

ParsedType::ParsedType(DATA_TYPE t, std::vector<int> *dims_vec) : data_type(t), dims(dims_vec) {};

ParsedType::~ParsedType() { delete dims; }

void ParsedType::printAST(std::ostream &out) const {
  out << "ParsedType(";
  switch (data_type)
  {
    case DATA_TYPE_int:
      out << "int";
      break;
    case DATA_TYPE_char:
      out << "char";
      break;
    default:
      exit(1); /* Will never be reached */
      break;
  }
  if (dims != nullptr) {
    for (const auto &s : *dims) {
      out << "[";
      if (s != INT_CONST_BRACKET_LIST_DIMENSION_AUTOCOMPLETE) out << s; 
      out << "]";
    }
  }
  out << ")";
}

Type toType(ParsedType *t)
{
  /* Formula : baseType_(i+1) = typeArray( new_dimension , baseType_(i) )
   * Example : int[5][12][3]
   *   initial -> baseType_0                             = int
   *   iter. 1 -> baseType_1 = typeArray(3,  int)        = int[3]
   *   iter. 2 -> baseType_2 = typeArray(12, int[3])     = int[12][3]
   *   iter. 3 -> baseType_3 = typeArray(5,  int[12][3]) = int[5][12][3]
   */

  /* Attention: we iterate the dimensions in reverse order because:
   *    var a : int[5][12][3] is     array[5] of array[12] of array[3] of int
   *                          is NOT array[3] of array[12] of array[5] of int
   *
   * This is important for the semantic analysis of LMatrix, since:
   *    typeof(a[i])  IS  (array[12] of array[3] of int)
   *                  NOT (array[12] of array[5] of int)
   */

  /* Assumptions:
   *     - t->datatype is not DATATYPE_void 
   *     - only t->dims[0] could potentially be < 0
   *       (this occurs when we autocomplete first dimension of fpardef)
   */

  /* This toType() call always returns a basic type so no delete is needed*/
  Type baseType = toType(t->data_type);
  Type tempType;

  /* If no dimensions are given, return the basic type (int or char),
   * otherwise, build the complex type by iterating over the dimensions 
   */
  for (auto it = t->dims->rbegin(); it != t->dims->rend(); ++it)
  {
    tempType = typeArray(*it, baseType);
    baseType = tempType;    
  }

  return baseType;
}