#include <iostream>
#include <vector>

#include "stmt.hpp"

/* A vector of statements */ 
class Block : public Stmt
{
  public:
    Block();
    ~Block();
    void append(Stmt *s);
    void printAST(std::ostream &out) const override;

  private:
    std::vector<Stmt*> stmt_list;
};