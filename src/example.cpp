#include <llvm/ExecutionEngine/Orc/LLJIT.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/Support/InitLLVM.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/Support/raw_ostream.h>
#include <memory>

using namespace llvm;
using namespace llvm::orc;

int main(int argc, char *argv[]) {
	// 1. Initialize LLVM
	InitLLVM X(argc, argv);
	InitializeNativeTarget();
	InitializeNativeTargetAsmPrinter();

	ExitOnError ExitOnErr;

	auto Context = std::make_unique<LLVMContext>();
	auto M = std::make_unique<Module>("zane_jit", *Context);
	IRBuilder<> Builder(*Context);

	// 2. Setup printf (Opaque Pointers for LLVM 18)
	Type *Int8Ptr = PointerType::get(*Context, 0); 
	FunctionType *PrintfType = FunctionType::get(Builder.getInt32Ty(), {Int8Ptr}, true);
	FunctionCallee PrintfFunc = M->getOrInsertFunction("printf", PrintfType);

	// 3. Create main function
	FunctionType *MainType = FunctionType::get(Builder.getInt32Ty(), false);
	Function *MainFunc = Function::Create(MainType, Function::ExternalLinkage, "main", M.get());
	BasicBlock *Entry = BasicBlock::Create(*Context, "entry", MainFunc);
	Builder.SetInsertPoint(Entry);

	// 4. Logic
	Value *HelloStr = Builder.CreateGlobalStringPtr("Hello from the Zane Compiler JIT!\n");
	Builder.CreateCall(PrintfFunc, {HelloStr});
	Builder.CreateRet(Builder.getInt32(0));

	// 5. Build JIT
	auto JIT = ExitOnErr(LLJITBuilder().create());

	// Ensure the module matches the JIT target data layout
	M->setDataLayout(JIT->getDataLayout());
	ExitOnErr(JIT->addIRModule(ThreadSafeModule(std::move(M), std::move(Context))));

	// 6. Lookup and Execute
	// LLVM 18 lookup returns an ExecutorAddr
	auto MainAddr = ExitOnErr(JIT->lookup("main"));

	// Convert the address to a callable function pointer
	auto MainPtr = MainAddr.toPtr<int (*)()>();

	outs() << "--- JIT Execution Start ---\n";
	MainPtr();
	outs() << "--- JIT Execution End ---\n";

	return 0;
}
