#pragma once
#include "Expression.hxx"

namespace ltn::c::ast::expr {
	struct Type final : public Expression {
		struct Null{};
		struct Any{};
		struct Bool{};
		struct Char{};
		struct Int{};
		struct Float{};
		struct String{};
		struct Array {
			std::unique_ptr<Type> contains;
		};
		struct TupleN {
			std::vector<std::unique_ptr<Type>> contains;
		};
		struct Tuple {};
		struct Fx {};
		struct FxN {
			std::uint64_t arity;
		};
		struct IStream {};
		struct OStream {};
		struct Iterator {};
		struct IteratorStop {};
		struct TypeT {};
		struct Rng {};
		struct Clock {};
		struct Struct {
			struct Member {
				std::variant<std::string, MemberCode> name;
				std::unique_ptr<Type> type;
			};

			std::vector<Member> members;
		};
		struct Queue {
			std::unique_ptr<Type> contains;
		};
		struct Stack {
			std::unique_ptr<Type> contains;
		};
		struct Map {
			std::unique_ptr<Type> key;
			std::unique_ptr<Type> value;
		};
		struct Coroutine {};

		using Variant = std::variant<
			Null,
			Any,
			Bool,
			Char,
			Int,
			Float,
			String,
			Array,
			Tuple, TupleN,
			Fx, FxN, Coroutine,
			IStream, OStream,
			Iterator, IteratorStop,
			TypeT, Rng, Clock,
			Struct, 
			Map,
			Queue, Stack
		>;

		Type(Variant variant, const SourceLocation & location);
		virtual void accept(const ExprVisitor & visitor) const override;

		Variant variant;
	};

	std::unique_ptr<Type> type(const SourceLocation & location, Type::Variant variant);
}