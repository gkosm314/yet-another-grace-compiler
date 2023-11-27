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
 /* Formula : baseType_(i+1) = typeArray( dim[i] , baseType_(i) )
  * Example : int[5][12][3]
  *    initial -> baseType_0                             = int
  *    iter. 1 -> baseType_1 = typeArray(5,  int)        = int[5]
  *    iter. 2 -> baseType_2 = typeArray(12, int[5])     = int[5][12]
  *    iter. 3 -> baseType_3 = typeArray(3,  int[5][12]) = int[5][12][3]
  */

 /* Assumptions:
  *     - t->datatype is not DATATYPE_void 
  *     - only t->dims[0] could potentially be < 0 (autocomplete first dimension of fpardef)
  */

  Type baseType = toType(t->data_type);
  Type tempType;

  /* If no dimensions are given, return the basic type (int or char),
   * otherwise, build the complex type by iterating over the dimensions 
   */
  for(int n : *(t->dims))
  {
    tempType = typeArray(n, baseType);
    baseType = tempType;
  }

  return baseType;
}