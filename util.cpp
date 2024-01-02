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

  switch (datatype_arg)
  {
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

llvmType *getLLVMType(Type t)
{
  if (equalType(t, typeVoid))
  {
    return llvmType::getVoidTy(TheContext);
  }
  else if (equalType(t, typeInteger))
  {
    return llvmType::getInt64Ty(TheContext);
  }
  else if (equalType(t, typeChar))
  {
    return llvmType::getInt8Ty(TheContext);
  }
  else
  {
    /* Execution should never reach this point */
    std::cout << "Invalid datatype_arg passed in toType()" << std::endl;
    exit(1);
    return 0; 
  }
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
llvm::Type *i8;
llvm::Type *i32;
llvm::Type *i64;
llvm::Function *TheWriteInteger;
llvm::Function *TheWriteString;

llvm::ConstantInt* c8(char c) {
  // returns a signed int because of the APInt call
  return llvm::ConstantInt::get(TheContext, llvm::APInt(8, c, true));
}

llvm::ConstantInt* c64(int n) {
  // returns a signed int because of the APInt call
  return llvm::ConstantInt::get(TheContext, llvm::APInt(64, n, true));
}

void codegenInitLibraryFunctions() {
  TheModule = std::make_unique<llvm::Module>("grace program", TheContext);
  // Initialize types
  i8 = llvm::IntegerType::get(TheContext, 8);
  i32 = llvm::IntegerType::get(TheContext, 32);
  i64 = llvm::IntegerType::get(TheContext, 64);

  // Initialize library functions
  llvm::FunctionType *writeInteger_type =
    llvm::FunctionType::get(llvmType::getVoidTy(TheContext), {i64}, false);
  TheWriteInteger =
    llvm::Function::Create(writeInteger_type, llvm::Function::ExternalLinkage,
                      "writeInteger", TheModule.get());
  llvm::FunctionType *writeString_type =
    llvm::FunctionType::get(llvmType::getVoidTy(TheContext),
                      {llvm::PointerType::get(i8, 0)}, false);
  TheWriteString =
    llvm::Function::Create(writeString_type, llvm::Function::ExternalLinkage,
                      "writeString", TheModule.get());
}

void codegenMain(llvm::Function* program_func)
{
  /* Create main function. This function is the entry point for the assembly code.
   * This function includes only a call to the program. */
  llvm::FunctionType *main_type = llvm::FunctionType::get(i64, {}, false);
  llvm::Function *main = llvm::Function::Create(main_type, llvm::Function::ExternalLinkage,
                                                "main", TheModule.get());
  
  /* Create the basic block for the main function */
  llvm::BasicBlock *BB = llvm::BasicBlock::Create(TheContext, "entry", main);
  Builder.SetInsertPoint(BB);
  /* Call the program */
  Builder.CreateCall(program_func);
  /* Return correct execution code */
  Builder.CreateRet(c64(0));
}