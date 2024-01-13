#ifndef __LOCALDEF_HPP__ 
#define __LOCALDEF_HPP__ 

#include "ast.hpp"
#include "util.hpp"

/* abstract class */
class LocalDef : public AST
{
  public:
    virtual void setOuterFunc(std::string outer_func_mangled_name) = 0;
};

#endif
