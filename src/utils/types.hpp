#pragma once

#include <variant>

template<typename... Types>
struct Variant {
	std::variant<Types...> value;

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
};

template<template<typename> class Wrapper, typename... Types>
struct WrappingVariant {
	std::variant<Wrapper<Types>...> value;

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
};
