#include "ast.hpp"

inline std::ostream &operator<<(std::ostream &out, const AST &ast)
{
  ast.printAST(out);
  return out;
}