#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>

class TypeMapper {
private:
	std::unordered_map<std::string, llvm::Type*> typeCache;
	llvm::LLVMContext& context;

public:
	TypeMapper(llvm::LLVMContext& ctx) : context(ctx) {
		loadTypes("data/types.csv");
	}

	llvm::Type* toLLVMType(const std::string& irTypeName) {
		auto it = typeCache.find(irTypeName);
		if (it != typeCache.end()) {
			return it->second;
		}
		return nullptr;
	}

private:
	llvm::Type* resolveString(const std::string& llvmTypeName) {
		if (llvmTypeName == "void") return llvm::Type::getVoidTy(context);
		if (llvmTypeName == "i32")  return llvm::Type::getInt32Ty(context);
		if (llvmTypeName == "i64")  return llvm::Type::getInt64Ty(context);
		return nullptr;
	}

	void loadTypes(const std::string& filename) {
		std::ifstream file(filename);
		std::string line;
		bool firstLine = true;

		while (std::getline(file, line)) {
			if (firstLine) { firstLine = false; continue; }

			std::istringstream iss(line);
			std::string name, llvmTypeName;
			if (std::getline(iss, name, ',') && std::getline(iss, llvmTypeName)) {
				trim(name);
				trim(llvmTypeName);

				// Pre-resolve and store the pointer
				typeCache[name] = resolveString(llvmTypeName);
			}
		}
	}

	void trim(std::string& s) {
		s.erase(0, s.find_first_not_of(" \t"));
		s.erase(s.find_last_not_of(" \t") + 1);
	}
};
