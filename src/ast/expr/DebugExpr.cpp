/* This is the source code of Brain Programming Language.
 * It is licensed under GNU GPL v. 3 or later.
 * You should have received a copy of the license in this archive (see LICENSE).
 *
 * Copyright Luiz Peres, 2016.
 */

#include "DebugExpr.h"

using namespace llvm;

void DebugExpr::CodeGen(llvm::Module *M, llvm::IRBuilder<> &B, llvm::GlobalVariable *index, llvm::GlobalVariable *cells)
{
  llvm::LLVMContext &C = M->getContext();
  
  // Get "printf" function
  // i32 @printf(i8*, ...)
  llvm::Type* PrintfArgs[] = { llvm::Type::getInt8PtrTy(C) };
  llvm::FunctionType *PrintfTy = llvm::FunctionType::get(llvm::Type::getInt32Ty(C), PrintfArgs, true /* vaarg */);
  llvm::Function *PrintfF = llvm::cast<llvm::Function>(M->getOrInsertFunction("printf", PrintfTy));
  
  // Prepare args
  static llvm::Value *GDBPrintfFormat = NULL;
  if (!GDBPrintfFormat) {
    GDBPrintfFormat = B.CreateGlobalString("Index Pointer: %d Value at Index Pointer: %d\n", "brainf.debug.printf.format");
  }
  llvm::Value *IdxV = B.CreateLoad(index);
  llvm::Value *CellPtr = B.CreateGEP(B.CreatePointerCast(cells,
                                                   llvm::Type::getInt32Ty(C)->getPointerTo()), // Cast to int32*
                               IdxV);
  
  // Call "printf"
  llvm::Value* Args[] = { CAST_TO_C_STRING(GDBPrintfFormat, B), IdxV, B.CreateLoad(CellPtr) };
  llvm::ArrayRef<llvm::Value *> ArgsArr(Args);
  B.CreateCall(PrintfF, ArgsArr);
}

void DebugExpr::DebugDescription(int level)
{
  std::cout.width(level);
  if (ArgsOptions::instance()->hasOption(BO_IS_VERBOSE))
  {
    std::cout << "Debug Expression - data pointer at cell " 
              << ASTInfo::instance()->debugIndex
              << std::endl;
  }
  else
  {
    std::cout << "DebugExpr" << std::endl;
  }
}
