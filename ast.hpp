#ifndef __AST_HPP__ 
#define __AST_HPP__ 

#include <iostream>

extern void ERROR(const char msg[]);

class AST
{
  public:
    virtual ~AST() = default;
    virtual void printAST(std::ostream &out) const = 0;
    virtual void sem() {};
};

inline std::ostream &operator<<(std::ostream &out, const AST &ast)
{
  ast.printAST(out);
  return out;
}

#endif
