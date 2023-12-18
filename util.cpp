#include "util.hpp"
#include "lexer.hpp"

#include <vector>

/* Use yylineno from lexer file, since the main is in this file we need to use extern here */
extern int yylineno;

std::ostream &operator<<(std::ostream &out, const AST &ast)
{
  ast.printAST(out);
  return out;
}

std::ostream &operator<<(std::ostream &out, const Type &t)
{
  printType(t);
  return out;
}

void yyerror(const char *msg)
{
  fprintf(stderr, "Error: %s at line %d\n", msg, yylineno);
  exit(1);
}

Type toType(DATA_TYPE datatype_arg)
{
  Type t;

  switch (datatype_arg) {
    case DATA_TYPE_int:
      t = typeInteger;
      break;
    case DATA_TYPE_char:
      t = typeChar;
      break;
    case DATA_TYPE_void:
      t = typeVoid;
      break;
    default:
      /* Execution should never reach this point */
      std::cout << "Invalid datatype_arg passed in toType()" << std::endl;
      exit(1);
      break;
  }  

  return t;
}

void semAddLibraryFunctions(const char                     *func_name,
                            const int                       param_count,
                            const std::vector<const char*>  param_name,
                            const std::vector<Type>         param_type,
                            const std::vector<PassMode>     pass_mode,
                            const Type                      return_type)
{
   SymbolEntry *f = newFunction(func_name);
   openScope();

   for(int i = 0; i < param_count; i++)
     newParameter(param_name[i], param_type[i], pass_mode[i], f);

   endFunctionHeader(f, return_type);
   closeScope();
}

void semInitLibraryFunctions()
{
  /* Here autocomplete is true because this will be the parameter type for the library functions */
  Type typeStringParam = typeArray(INT_CONST_BRACKET_LIST_DIMENSION_AUTOCOMPLETE, typeChar, true);

  /* Output library functions */
  semAddLibraryFunctions("writeInteger", 1,
                         std::vector<const char*>{"n"},
                         std::vector<Type>{typeInteger},
                         std::vector<PassMode>{PASS_BY_VALUE},
                         typeVoid);
  semAddLibraryFunctions("writeChar", 1,
                         std::vector<const char*>{"c"},
                         std::vector<Type>{typeChar},
                         std::vector<PassMode>{PASS_BY_VALUE},
                         typeVoid);
  semAddLibraryFunctions("writeString", 1,
                         std::vector<const char*>{"s"},
                         std::vector<Type>{typeStringParam},
                         std::vector<PassMode>{PASS_BY_VALUE},
                         typeVoid);

  /* Input library functions */
  semAddLibraryFunctions("readInteger", 0,
                         std::vector<const char*>{},
                         std::vector<Type>{},
                         std::vector<PassMode>{},
                         typeInteger);
  semAddLibraryFunctions("readChar", 0,
                         std::vector<const char*>{},
                         std::vector<Type>{},
                         std::vector<PassMode>{},
                         typeChar);
  semAddLibraryFunctions("readString", 2,
                         std::vector<const char*>{"n","s"},
                         std::vector<Type>{typeInteger, typeStringParam},
                         std::vector<PassMode>{PASS_BY_VALUE, PASS_BY_REFERENCE},
                         typeVoid);

  /* Type conversion library functions */
  semAddLibraryFunctions("ascii", 1,
                         std::vector<const char*>{"c"},
                         std::vector<Type>{typeChar},
                         std::vector<PassMode>{PASS_BY_VALUE},
                         typeInteger);
  semAddLibraryFunctions("chr", 1,
                         std::vector<const char*>{"n"},
                         std::vector<Type>{typeInteger},
                         std::vector<PassMode>{PASS_BY_VALUE},
                         typeChar);                       

  /* String handling library functions */
  semAddLibraryFunctions("strlen", 1,
                         std::vector<const char*>{"s"},
                         std::vector<Type>{typeStringParam},
                         std::vector<PassMode>{PASS_BY_REFERENCE},
                         typeInteger);
  semAddLibraryFunctions("strcmp", 2,
                         std::vector<const char*>{"s1", "s2"},
                         std::vector<Type>{typeStringParam, typeStringParam},
                         std::vector<PassMode>{PASS_BY_REFERENCE, PASS_BY_REFERENCE},
                         typeInteger);
  semAddLibraryFunctions("strcpy", 2,
                         std::vector<const char*>{"trg", "src"},
                         std::vector<Type>{typeStringParam, typeStringParam},
                         std::vector<PassMode>{PASS_BY_REFERENCE, PASS_BY_REFERENCE},
                         typeVoid);
  semAddLibraryFunctions("strcat", 2,
                         std::vector<const char*>{"trg", "src"},
                         std::vector<Type>{typeStringParam, typeStringParam},
                         std::vector<PassMode>{PASS_BY_REFERENCE, PASS_BY_REFERENCE},
                         typeVoid);

  destroyType(typeStringParam);
}

llvm::LLVMContext TheContext;
llvm::IRBuilder<> Builder(TheContext);
std::unique_ptr<llvm::Module> TheModule;