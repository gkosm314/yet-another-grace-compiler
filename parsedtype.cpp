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