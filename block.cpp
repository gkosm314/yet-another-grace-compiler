#include "block.hpp"

Block::Block() {}

Block::~Block() {
  for (Stmt *s : stmt_list) delete s;
}

void Block::append(Stmt *s) { stmt_list.push_back(s); }

void Block::printAST(std::ostream &out) const {
  out << "Block(";
  bool first = true;
  for (const auto &s : stmt_list) {
    if (!first) out << ", ";
    first = false;
    out << *s;
  }
  out << ")";
}

void Block::sem()
{
  for (Stmt *s : stmt_list) s->sem();
}

llvm::Value* Block::compile()
{
  for (Stmt *s : stmt_list)
  {
    s->compile();
    
    /* If the statement you just compiled is a return statement: 
     *    - do not compile anything else in this block 
     *    - block will return (useful to avoid inserting a reduntant branch when exiting an if/else/while)
     */
    if(dynamic_cast<Return*>(s))
    {
      will_return = true;
      break;
    }
  }

  return nullptr;
}