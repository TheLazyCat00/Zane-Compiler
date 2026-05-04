#include "package/package.hpp"

#include "codegen/llvm.hpp"

std::unique_ptr<llvm::Module> Package::getLlvmModule(
		Ptr<llvm::LLVMContext> context,
		Ptr<Package> package,
		Ptr<Packages> allPackages,
		const std::vector<std::shared_ptr<ir::PackageInfo>>& externalPackages,
		const std::string& triple) {
	LLVMCodeGen codegen(*context, triple);
	codegen.setupBuiltins();
	codegen.generate(package, allPackages, externalPackages);
	return codegen.extractModule();
}
