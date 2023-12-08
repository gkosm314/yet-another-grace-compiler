#ifndef __RETURN_STACK_HPP__ 
#define __RETURN_STACK_HPP__ 

#include <vector>

extern "C" {
  #include "symbol.h"
}

/* We keep the return types of the function definitions we semantically analyze in this stack,
 * in order to know the expected return type of a return statement when we call semantically analyze it.
 * Using a stack works correctly because function definitions are nested.
 * We push the return type every type we semantically analyze a header,
 * This includes ret_types inside the headers of forward-declared functions (func-decl). 
 * We pop the ret_type from the stack when the definition (or declaration) finishes.
 *
 * We also keep track of whether a return statement was already found in the function.
 * We do this in order to:
 *     - ensure that non-void functions include a return statement
 *     - not generate code for statements that should be skipped
 */
class ReturnStack
{
 public:
    ReturnStack() {};
    void push(Type ret_type);
    void pop();
    Type getType();
    bool returnFound();
    void setFound();

 private:
    std::vector<Type> types;
    std::vector<bool> found;
};

#endif