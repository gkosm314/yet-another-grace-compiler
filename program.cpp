#include "program.hpp"

Program::Program(FuncDef *f) : fd(f) {}

Program::~Program() { delete fd; }

void Program::printAST(std::ostream &out) const {
  out << "Program(" << *fd << ")";
}

void Program::sem()
{
  fd->hasProgramSignature();
  fd->sem();
}

llvm::Value* Program::compile()
{
  TheModule = std::make_unique<llvm::Module>("grace program", TheContext);
  codegenInitFPM();
  codegenInitLibraryFunctions();
  
  /* Compile program */
  llvm::Function* program = fd->compile();
  codegenMain(program);

  /* Verify the IR */
  bool bad = verifyModule(*TheModule, &llvm::errs());
  if (bad) {
    std::cerr << "The IR is bad!" << std::endl;
    TheModule->print(llvm::errs(), nullptr);
    std::exit(1);
  }

  /* Dump IR and final code to correct files/stdout */
  if (emit_imm_code_to_stdout)
    /* Dump intermidiate code to stdout */
    dumpIntermediateCode("-");
  else if (emit_final_code_to_stdout)
    /* Dump final code to stdout */
    dumpFinalCode("-");
  else
  {
    /* Dump intermidiate code to *.imm file */
    std::string imm_filename =filename.substr(0,filename.find_last_of('.'))+".imm";
    dumpIntermediateCode(imm_filename);
    /* Dump final code to *.asm file */
    std::string asm_filename =filename.substr(0,filename.find_last_of('.'))+".asm";
    dumpFinalCode(asm_filename);
  }
  return nullptr;
}

void Program::dumpFinalCode(std::string Filename)
{
  std::error_code EC;
  llvm::raw_fd_ostream dest(Filename, EC, llvm::sys::fs::OF_None);

  // Initialize the target registry etc.
  llvm::InitializeAllTargetInfos();
  llvm::InitializeAllTargets();
  llvm::InitializeAllTargetMCs();
  llvm::InitializeAllAsmParsers();
  llvm::InitializeAllAsmPrinters();

  auto TargetTriple = llvm::sys::getDefaultTargetTriple();
  TheModule->setTargetTriple(TargetTriple);

  std::string Error;
  auto Target = llvm::TargetRegistry::lookupTarget(TargetTriple, Error);

  // Print an error and exit if we couldn't find the requested target.
  // This generally occurs if we've forgotten to initialise the
  // TargetRegistry or we have a bogus target triple.
  if (!Target) {
    llvm::errs() << Error;
    exit(1);
  }

  auto CPU = "generic";
  auto Features = "";

  llvm::TargetOptions opt;
  auto TheTargetMachine = Target->createTargetMachine(
      TargetTriple, CPU, Features, opt, llvm::Reloc::PIC_);

  TheModule->setDataLayout(TheTargetMachine->createDataLayout());

  if (EC) {
    llvm::errs() << "Could not open file: " << EC.message();
    exit(1);
  }

  llvm::legacy::PassManager pass;
  auto FileType = llvm::CodeGenFileType::CGFT_AssemblyFile;

  if (TheTargetMachine->addPassesToEmitFile(pass, dest, nullptr, FileType)) {
    llvm::errs() << "TheTargetMachine can't emit a file of this type";
    exit(1);
  }

  pass.run(*TheModule);
  dest.flush();

}

void Program::dumpIntermediateCode(std::string Filename)
{
    std::error_code EC;
    llvm::raw_fd_ostream oss(Filename, EC);
    TheModule->print(oss, nullptr);
}