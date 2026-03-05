#pragma once

#include <variant>

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
