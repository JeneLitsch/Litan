#include "optimize.hxx"
#include "ltn/casts.hxx"
namespace ltn::c::optimize {
	namespace {
		using Op = ast::Unary::Type;



		template<typename T>
		concept Literal = std::is_base_of<ast::Literal, T>::value;



		template<Literal T>
		struct promoted_t {
			using Type = T;
		};
		template<>
		struct promoted_t<ast::Bool> {
			using Type = ast::Integer;
		};
		template<>
		struct promoted_t<ast::Char> {
			using Type = ast::Integer;
		};
		template<Literal T>
		using promoted = typename promoted_t<T>::Type;
		



		template<Op op>
		bool is_type(const ast::Unary & unary) {
			return unary.type == op;
		}
		constexpr auto is_neg = is_type<Op::NEG>;
		constexpr auto is_not = is_type<Op::NOT>;
		constexpr auto is_nul = is_type<Op::NUL>;

		

		template<typename Operator, Literal Litr>
		ast::expr_ptr fold(ast::Expression & inner) {
			static constexpr Operator op;
			if(auto * litr = as<Litr>(inner)) {
				return op(*litr);
			}
			return nullptr;
		}




		struct Negation {
			template<Literal Litr>
			auto operator()(Litr & litr) const {
				using T = promoted<Litr>;
				return std::make_unique<T>(eval(litr), litr.location);
			}

			auto eval(Literal auto & litr) const {
				return -litr.value;
			}
		};



		struct Notigation {
			auto eval(Literal auto & litr) const {
				return !litr.value;
			}
			

			auto operator()(Literal auto & litr) const {
				return std::make_unique<ast::Bool>(eval(litr), litr.location);
			}
		};


		
		struct NullTest {
			auto eval(Literal auto &) const {
				return true;
			}
		
			auto eval(ast::Null &) const {
				return false;
			}

			auto operator()(Literal auto & litr) const {
				return std::make_unique<ast::Bool>(eval(litr), litr.location);
			}
		};
	}


	
	
	ast::expr_ptr unary(ast::Unary & unary) {
		auto & inner = unary.expression;
		inner = expression(std::move(inner));
		if(is_neg(unary)) {
			if(auto expr = fold<Negation, ast::Bool>(*inner)) return expr;
			if(auto expr = fold<Negation, ast::Char>(*inner)) return expr;
			if(auto expr = fold<Negation, ast::Integer>(*inner)) return expr;
			if(auto expr = fold<Negation, ast::Float>(*inner))   return expr;
		}
		if(is_not(unary)) {
			if(auto expr = fold<Notigation, ast::Bool>(*inner))    return expr;
			if(auto expr = fold<Notigation, ast::Integer>(*inner)) return expr;
			if(auto expr = fold<Notigation, ast::Float>(*inner))   return expr;
		}
		if(is_nul(unary)) {
			if(auto expr = fold<NullTest, ast::Null>(*inner))    return expr;
			if(auto expr = fold<NullTest, ast::Bool>(*inner))   return expr;
			if(auto expr = fold<NullTest, ast::Char>(*inner))    return expr;
			if(auto expr = fold<NullTest, ast::Integer>(*inner)) return expr;
			if(auto expr = fold<NullTest, ast::Float>(*inner))   return expr;
			if(auto expr = fold<NullTest, ast::String>(*inner))  return expr;
			if(auto expr = fold<NullTest, ast::Array>(*inner))   return expr;
		}
		return nullptr;
	}
}