#include "returnstack.hpp"

void ReturnStack::push(Type ret_type)
{
  types.push_back(ret_type);
  found.push_back(false);
}

void ReturnStack::pop()
{
  types.pop_back();
  found.pop_back();
}

Type ReturnStack::getType()
{
  return types.back();
}

bool ReturnStack::returnFound()
{
  /* We do not return .back() immediatly because we store the return
   * of this function and we want to avoid storing a reference to an element
   * that will be popped out of the stack. (maybe this is not necessary).
   */
  if (found.back()) return true;
  else return false;
}

void ReturnStack::setFound()
{
  found.back() = true;
}
