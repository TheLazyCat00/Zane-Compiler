#include "package/package.hpp"

#include "ast/symbol_collector.hpp"
#include "ast/visitor.hpp"
#include "package/parser_context.hpp"

Package::Package(Ptr<SymbolCollector> symbolCollector)
	: symbolCollector(symbolCollector),
	  visitor(Visitor(symbolCollector)) {}

Package::~Package() = default;

std::shared_ptr<ir::PackageInfo> Package::getPackageInfo() const {
	return packageInfo;
}

std::shared_ptr<ir::GlobalScope> Package::getIRProgram() const {
	return irProgram;
}
