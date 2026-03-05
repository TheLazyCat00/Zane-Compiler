#pragma once

#include "ir/node.hpp"
#include "ir/nodes.hpp"
#include "parser/ZaneBaseVisitor.h"
#include "parser/ZaneParser.h"

#include <antlr4-runtime.h>
#include <memory>
#include <stdexcept>
#include <string>
#include <tree/ParseTree.h>
#include <utils/embedded_types.hpp>
#include <vector>

using namespace parser;

class CustomZaneVisitor : public ZaneBaseVisitor {
private:
	std::string packageName; 

protected:
	template<typename T>
	std::shared_ptr<T> toIRNode(const std::any& result) {
		if (!result.has_value()) return nullptr;
		
		if (result.type() == typeid(std::shared_ptr<T>)) {
			return std::any_cast<std::shared_ptr<T>>(result);
		}

		if (result.type() == typeid(std::shared_ptr<ir::IRNode>)) {
			auto base = std::any_cast<std::shared_ptr<ir::IRNode>>(result);
			return std::dynamic_pointer_cast<T>(base);
		}

		std::string expectedType = typeid(std::shared_ptr<T>).name();
		std::string actualType = result.type().name();
		
		throw std::runtime_error(
			"IR Type Mismatch!\n"
			"  Expected: " + expectedType + "\n"
			"  Actual:   " + actualType + "\n"
		);
	}

	template<typename T>
	std::shared_ptr<T> get(antlr4::tree::ParseTree* tree) {
		return toIRNode<T>(visit(tree));
	}

public:
	std::any visitTypeSymbol(ZaneParser::TypeSymbolContext *ctx) override {
		auto typeSymbol = std::make_shared<ir::TypeSymbol>();
		auto name = ctx->name->getText();
		typeSymbol->name = name;

		if (ctx->package) {
			typeSymbol->packageName = packageName;
		}

		return std::static_pointer_cast<ir::IRNode>(typeSymbol);
	}

	std::any visitFuncType(ZaneParser::FuncTypeContext *ctx) override {
		auto funcType = std::make_shared<ir::FuncType>();
		funcType->returnType = get<ir::Type>(ctx->returnType);

		std::string funcMod = "open";
		if (ctx->funcMod()) {
			funcMod = ctx->funcMod()->getText();
		}
		funcType->mod = ir::FuncMod(funcMod);

		if (ctx->funcTypeParams()) {
			for (auto paramCtx : ctx->funcTypeParams()->type()) {
				auto paramType = get<ir::Type>(paramCtx);
				funcType->paramTypes.push_back(paramType);
			}
		}

		return std::static_pointer_cast<ir::IRNode>(funcType);
	}

	std::any visitType(ZaneParser::TypeContext *ctx) override {
		auto type = std::make_shared<ir::Type>();
	
		if (ctx->typeSymbol()) {
			type->value = { get<ir::TypeSymbol>(ctx->typeSymbol()) };
		} else if (ctx->funcType()) {
			type->value = { get<ir::FuncType>(ctx->funcType()) };
		}
	
		for (auto generic : ctx->type()) {
			type->generics.push_back(get<ir::Type>(generic));
		}

		return std::static_pointer_cast<ir::IRNode>(type);
	}
};
