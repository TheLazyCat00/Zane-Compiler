#pragma once

#include <variant>
#include <vector>

// Helper function to load a variant at a specific index
template<std::size_t I = 0, typename... Types, typename Archive>
void loadVariantAt(std::size_t idx, std::variant<Types...>& var, Archive& ar) {
	if constexpr (I < sizeof...(Types)) {
		if (I == idx) {
			std::variant_alternative_t<I, std::variant<Types...>> val;
			ar(val);
			var = std::move(val);
		} else {
			loadVariantAt<I + 1>(idx, var, ar);
		}
	}
}

template<typename... Types>
struct Variant {
	std::variant<Types...> value;

	Variant() = default;

	Variant(std::variant<Types...> value)
	: value(std::move(value)) {}

	template<typename Callback>
	decltype(auto) visit(Callback&& callback) {
		return std::visit(std::forward<Callback>(callback), value);
	}

	template<typename Callback>
	decltype(auto) visit(Callback&& callback) const {
		return std::visit(std::forward<Callback>(callback), value);
	}

	template<typename Archive>
    void save(Archive& ar) const {
        ar(value.index());
        std::visit([&ar](const auto& v) { ar(v); }, value);
    }

    template<typename Archive>
    void load(Archive& ar) {
        std::size_t idx;
        ar(idx);
        loadVariantAt<0>(idx, value, ar);
    }
};

template<template<typename> class Wrapper, typename... Types>
struct WrappingVariant {
	std::variant<Wrapper<Types>...> value;

	WrappingVariant() = default;

	WrappingVariant(std::variant<Wrapper<Types>...> value)
	: value(std::move(value)) {}

	template<typename Callback>
	decltype(auto) visit(Callback&& callback) {
		return std::visit(std::forward<Callback>(callback), value);
	}

	template<typename Callback>
	decltype(auto) visit(Callback&& callback) const {
		return std::visit(std::forward<Callback>(callback), value);
	}

	template<typename Archive>
    void save(Archive& ar) const {
        ar(value.index());
        std::visit([&ar](const auto& v) { ar(v); }, value);
    }

    template<typename Archive>
    void load(Archive& ar) {
        std::size_t idx;
        ar(idx);
        loadVariantAt<0>(idx, value, ar);
    }
};

template<typename T>
class Stack {
	std::vector<T> stack;
public:
	Stack() = default;

	void push(T element) {
		stack.push_back(element);
	}

	bool empty() const {
		return stack.empty();
	}

	T top() const {
		return stack.back();
	}

	T pop() {
		if (stack.empty()) return {};
		auto value = stack.back();
		stack.pop_back();
		return value;
	}
};
