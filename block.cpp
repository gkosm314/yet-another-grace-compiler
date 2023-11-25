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