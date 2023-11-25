#include <iostream>

#include "noop.hpp"

NoOp::NoOp() {}

void NoOp::printAST(std::ostream &out) const { out << "NoOp()"; }