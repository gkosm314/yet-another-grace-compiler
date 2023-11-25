#include "stmt.cpp"

class NoOp : public Stmt
{
  public:
    NoOp();
    void printAST(std::ostream &out);
};