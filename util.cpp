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
    if(t->size > 0) return llvm::ArrayType::get(getLLVMType(t->refType), t->size);
    else return getLLVMType(t->refType);
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

   /* Register functions as top-level functions */
   funcDepth[func_name] = currentScope->nestingLevel;
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
                         std::vector<PassMode>{PASS_BY_REFERENCE},
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
llvmType *i8;
llvmType *i32;
llvmType *i64;
llvmType *voidTy;

llvm::ConstantInt* c8(char c) {
  // returns a signed int because of the APInt call
  return llvm::ConstantInt::get(TheContext, llvm::APInt(8, c, true));
}

llvm::ConstantInt* c32(int n) {
  // returns a signed int because of the APInt call
  return llvm::ConstantInt::get(TheContext, llvm::APInt(32, n, true));
}

llvm::ConstantInt* c64(int n) {
  // returns a signed int because of the APInt call
  return llvm::ConstantInt::get(TheContext, llvm::APInt(64, n, true));
}

void codegenAddLibraryFunction(const char * func_name, llvmType* ret_type, const std::vector<llvmType*> param_type)
{
  llvm::FunctionType *t = llvm::FunctionType::get(ret_type, param_type, false);
  llvm::Function::Create(t, llvm::Function::ExternalLinkage, func_name, TheModule.get());
}

void codegenInitLibraryFunctions() {
  TheModule = std::make_unique<llvm::Module>("grace program", TheContext);
 
  /* Initialize types */
  i8 = llvm::IntegerType::get(TheContext, 8);
  i32 = llvm::IntegerType::get(TheContext, 32);
  i64 = llvm::IntegerType::get(TheContext, 64);
  voidTy = llvmType::getVoidTy(TheContext);

  /* Initialize library functions */
  codegenAddLibraryFunction("writeInteger", voidTy, std::vector<llvmType*>{i64});
  codegenAddLibraryFunction("writeChar", voidTy, std::vector<llvmType*>{i8});
  codegenAddLibraryFunction("writeString", voidTy, std::vector<llvmType*>{llvm::PointerType::get(i8, 0)});

  codegenAddLibraryFunction("readInteger", i64, std::vector<llvmType*>{});
  codegenAddLibraryFunction("readChar", i8, std::vector<llvmType*>{});
  codegenAddLibraryFunction("readString", voidTy, std::vector<llvmType*>{i64, llvm::PointerType::get(i8, 0)});

  codegenAddLibraryFunction("ascii", i64, std::vector<llvmType*>{i8});
  codegenAddLibraryFunction("chr", i8, std::vector<llvmType*>{i64});

  codegenAddLibraryFunction("strlen", i64, std::vector<llvmType*>{llvm::PointerType::get(i8, 0)});
  codegenAddLibraryFunction("strcmp", i64, std::vector<llvmType*>{llvm::PointerType::get(i8, 0), llvm::PointerType::get(i8, 0)});
  codegenAddLibraryFunction("strcpy", voidTy, std::vector<llvmType*>{llvm::PointerType::get(i8, 0), llvm::PointerType::get(i8, 0)});
  codegenAddLibraryFunction("strcat", voidTy, std::vector<llvmType*>{llvm::PointerType::get(i8, 0), llvm::PointerType::get(i8, 0)});

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

std::string mangle(const char * name, unsigned int scope_id)
{
  /* Scope with scope_id = 0 contains only the library functions, which are functions that are not mangled */
  if(scope_id > 0)
    return std::string(name) + "_" + std::to_string(scope_id);
  else
    return std::string(name);
}

std::string getStackFrameName(std::string mangled_function_name)
{
  return "stack_frame_" + mangled_function_name;
}

std::string getStackFrameStructName(std::string mangled_function_name)
{
  return "sf_" + mangled_function_name;
}

bool isTopLevelFunc(std::string mangled_function_name)
{
  return funcDepth[mangled_function_name] <= TOP_LEVEL_FUNCTION_MAXIMUM_SCOPE;
}