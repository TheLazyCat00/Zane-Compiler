#include <unordered_map>
#include <string>
#include <llvm/IR/Type.h>
#include <llvm/IR/DerivedTypes.h>
#include <llvm/IR/LLVMContext.h>
#include <utils/embedded_types.hpp>

class TypeMapper {
private:
	std::unordered_map<std::string, llvm::Type*> typeCache;
	llvm::LLVMContext& context;

public:
	TypeMapper(llvm::LLVMContext& ctx) : context(ctx) {
		loadTypes();
	}

	llvm::Type* toLLVMType(const std::string& irTypeName) {
		if (irTypeName == "String") {
			return llvm::PointerType::get(context, 0);
		}
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

	void loadTypes() {
		for (const auto& typeInfo : utils::parseEmbeddedTypes()) {
			typeCache[typeInfo.name] = resolveString(typeInfo.llvmType);
		}
	}
};
