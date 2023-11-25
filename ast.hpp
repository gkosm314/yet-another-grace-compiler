#include <iostream>

extern void ERROR(const char msg[]);

class AST
{
  public:
    virtual ~AST() = default;
    virtual void printAST(std::ostream &out) const = 0;
    virtual void sem() {};
};