#ifndef __ABSTRACTLVALUE_HPP__ 
#define __ABSTRACTLVALUE_HPP__ 

#include "expr.hpp"

/* abstract class */
class AbstractLvalue : public Expr
{
  public:
    bool isLvalue() override;
};

#endif
