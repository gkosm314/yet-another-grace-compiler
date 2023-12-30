#ifndef __BLOCK_HPP__ 
#define __BLOCK_HPP__ 

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
    void sem() override;
    llvm::Value* compile() override;

  private:
    std::vector<Stmt*> stmt_list;
};

#endif
