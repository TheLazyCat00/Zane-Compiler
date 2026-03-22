#include "package/package.hpp"
#include "globals/constants.hpp"
#include "codegen/llvm.hpp"

Package::Package(Ptr<Packages> packages) 
	: packages(packages) {
	this->symbolCollector = SymbolCollector();
	this->visitor = Visitor(packages, symbolCollector);
}

std::expected<std::unique_ptr<ParserContext>, std::string> Package::parseFile(const fs::path& path) {
	std::ifstream stream(path);
	if (!stream) {
		std::ostringstream oss;
		oss << "Failed to open file: " << path << "\n";
		return std::unexpected(oss.str());
	}
	std::stringstream ss;
	ss << stream.rdbuf();
	auto ctx = std::make_unique<ParserContext>(ss.str());
	if (!ctx->getTree()) {
		return std::unexpected("Failed to parse file: " + path.string());
	}
	return ctx;
}

void Package::parse(const std::vector<fs::path>& files) {
	this->files = files;
	contexts.reserve(files.size());
	for (const auto& path : files) {
		auto result = parseFile(path);
		if (!result) { LOG("Parse error: " << result.error()); continue; }
		contexts.push_back(std::move(*result));
	}
}

void Package::collectSymbols() {
	for (const auto& ctx : contexts) {
		symbolCollector->collectSymbols(ctx->getTree());
	}
	packageInfo = symbolCollector->getPackageInfo();
}

void Package::buildTree(const std::string& packageDir) {
	for (const auto& ctx : contexts) {
		visitor->buildTree(ctx->getTree());
	}
	irProgram = visitor->getGlobalScope();
	writeSymbolsCache(packageInfo, packageDir, files);
}

void Package::compile(const std::string& pkgName, const std::vector<fs::path>& files, const std::string& packageDir) {
	std::vector<std::unique_ptr<ParserContext>> contexts;
	contexts.reserve(files.size());

	for (const auto& path : files) {
		auto parseResult = parseFile(path);
		if (!parseResult) {
			LOG("Parse error: " << parseResult.error());
			continue;
		}
		contexts.push_back(std::move(*parseResult));
	}

	for (const auto& ctx : contexts) {
		symbolCollector->collectSymbols(ctx->getTree());
	}

	packageInfo = symbolCollector->getPackageInfo();

	for (const auto& ctx : contexts) {
		visitor->buildTree(ctx->getTree());
	}

	irProgram = visitor->getGlobalScope();

	writeSymbolsCache(packageInfo, packageDir, files);
}

void Package::writeSymbolsCache(
		std::shared_ptr<ir::PackageInfo> packageInfo,
		const std::string& packageDir,
		const std::vector<fs::path>& files) {
	fs::path symbolsPath = constants::getSymbolsPath(packageDir);
	fs::create_directories(symbolsPath.parent_path());

	std::ofstream os(symbolsPath, std::ios::binary);
	cereal::BinaryOutputArchive archive(os);

	archive(
		packageInfo->packageName,
		packageInfo->importedPackages
	);
}

std::unique_ptr<llvm::Module> Package::getLlvmModule(Ptr<llvm::LLVMContext> context, Ptr<Package> package, const std::string& triple) {
	LLVMCodeGen codegen(*context, triple);
	codegen.setupBuiltins();
	codegen.generate(package, packages);
	return std::move(codegen.extractModule());
}

std::shared_ptr<ir::PackageInfo> Package::getPackageInfo() const {
	return packageInfo;
}

std::shared_ptr<ir::GlobalScope> Package::getIRProgram() const {
	return irProgram;
}
