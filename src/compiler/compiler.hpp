# pragma once

#include "cli/manifest.hpp"
#include "ir/nodes.hpp"
#include <map>
#include <string>

using Packages = std::map<std::string, ir::GlobalScope>;

class Compiler {
private:
	Packages packages;
	manifest::Manifest manifest;
public:
	Compiler(manifest::Manifest manifest) : manifest(manifest) {}

	Packages getPackages() {
		namespace fs = std::filesystem;
		fs::path entry;
		if (manifest.type == manifest::Type::Executable) {
			entry = constants::executable::ENTRY_DIR;
		}
		else {
			entry = constants::library::ENTRY_DIR;
		}

		if (!fs::exists(entry) || !fs::is_directory(entry)) {
			std::cerr << "Directory not found: " << entry << "\n";
			return {};
		}

		std::vector<fs::path> sources;
		for (const auto& entry : fs::directory_iterator(entry)) {
			if (entry.path().extension() == ".zn") {
				sources.push_back(entry.path());
			}
		}

		std::sort(sources.begin(), sources.end());

		Visitor visitor;
		std::shared_ptr<ir::GlobalScope> irProgram;
		for (const auto& path : sources) {
			std::ifstream stream(path);
			if (!stream) {
				std::cerr << "Failed to open file: " << path << "\n";
				return;
			}

			std::stringstream ss;
			ss << stream.rdbuf();

			antlr4::ANTLRInputStream input(ss.str());
			parser::ZaneLexer lexer(&input);
			antlr4::CommonTokenStream tokens(&lexer);
			parser::ZaneParser parser(&tokens);

			antlr4::tree::ParseTree *tree = parser.globalScope();
			visitor.visit(tree);

			irProgram = visitor.getGlobalScope();
			const std::string& pkgName = irProgram->pkgName;

			const std::string expectedName =
				(entry == fs::path("src")) ? manifest.name : entry.string();
			
			if (expectedName != pkgName) {
				std::cerr << "Expected package name " << expectedName << " but got " << pkgName;
				return;
			}
		}


		llvm::LLVMContext context;
		LLVMCodeGen codegen(context);
		codegen.generate(irProgram);
	}
};
