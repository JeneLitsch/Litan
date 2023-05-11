#include "parse.hxx"


namespace ltn::c {
	using TT = Token::Type;

	namespace {
		ast::type_ptr parse_type_name(const Token & begin, Tokens & tokens);



		template<typename T>
		ast::type_ptr simple_type(const Token & begin) {
			const auto & loc = begin.location;
			return std::make_unique<ast::Type>(T{}, loc); 
		}




		template<typename T>
		ast::type_ptr unary_type(const Token & begin, Tokens & tokens) {
			const auto & loc = begin.location;
			if(match(TT::PAREN_L, tokens)) {
				auto sub_type = parse_type_name(begin, tokens);
				if(!match(TT::PAREN_R, tokens)) throw CompilerError {
					"Expected )", loc
				};
				return std::make_unique<ast::Type>(T{
					.contains = std::move(sub_type),
				}, loc);
			}
			else {
				return std::make_unique<ast::Type>(T{
					.contains = nullptr,
				}, loc); 
			}
		}



		ast::type_ptr tuple_type(const Token & begin, Tokens & tokens) {
			const auto & loc = begin.location;
			if(match(TT::PAREN_L, tokens)) {
				if(match(TT::PAREN_R, tokens)) {
					return std::make_unique<ast::Type>(ast::Type::TupleN{
						.contains = {},
					}, loc);
				}
				std::vector<ast::type_ptr> sub_types;
				do {
					sub_types.push_back(parse_type_name(begin, tokens));
				} while(match(TT::COMMA, tokens));
				if(!match(TT::PAREN_R, tokens)) throw CompilerError {
					"Expected )", loc
				};
				return std::make_unique<ast::Type>(ast::Type::TupleN{
					.contains = std::move(sub_types),
				}, loc);
			}
			else {
				return std::make_unique<ast::Type>(ast::Type::Tuple{}, loc); 
			}
		}



		ast::type_ptr map_type(const Token & begin, Tokens & tokens) {
			const auto & loc = begin.location;
			if(match(TT::PAREN_L, tokens)) {
				auto key = parse_type_name(begin, tokens);
				if(!match(TT::COMMA, tokens)) throw CompilerError {
					"Expected ,", loc
				};
				auto val = parse_type_name(begin, tokens);
				if(!match(TT::PAREN_R, tokens)) throw CompilerError {
					"Expected )", loc
				};
				return std::make_unique<ast::Type>(ast::Type::Map{
					.key = std::move(key),
					.value = std::move(val),
				}, loc);
			}
			else {
				return std::make_unique<ast::Type>(ast::Type::Map{
					.key = nullptr,
					.value = nullptr,
				}, loc); 
			}
		}


		ast::type_ptr fx_type(const Token & begin, Tokens & tokens) {
			const auto & loc = begin.location;
			if(match(TT::PAREN_L, tokens)) {
				auto token_arity = match(TT::INTEGER, tokens);
				if(!token_arity) throw CompilerError {
					"Expected arity", loc
				};
				if(!match(TT::PAREN_R, tokens)) throw CompilerError {
					"Expected )", loc
				};

				std::stringstream iss{token_arity->str};
				std::uint64_t arity;
				iss >> arity;
				return std::make_unique<ast::Type>(ast::Type::FxN{
					.arity = arity,
				}, loc);
			}
			else {
				return std::make_unique<ast::Type>(ast::Type::Fx {}, loc); 
			}
		}


		ast::type_ptr parse_type_name(const Token & begin, Tokens & tokens) {
			if(auto name = match(TT::NVLL, tokens)) {
				return simple_type<ast::Type::Null>(begin);
			}
			if(auto name = match(TT::INDENTIFIER, tokens)) {
				if(name->str == "bool") return simple_type<ast::Type::Bool>(begin);
				if(name->str == "char") return simple_type<ast::Type::Char>(begin);
				if(name->str == "int") return simple_type<ast::Type::Int>(begin);
				if(name->str == "float") return simple_type<ast::Type::Float>(begin);
				if(name->str == "string") return simple_type<ast::Type::String>(begin);
				if(name->str == "array") return unary_type<ast::Type::Array>(begin, tokens);
				if(name->str == "tuple") return tuple_type(begin, tokens);
				if(name->str == "fx") return fx_type(begin, tokens);
				if(name->str == "istream") return simple_type<ast::Type::IStream>(begin);
				if(name->str == "ostream") return simple_type<ast::Type::OStream>(begin);
				if(name->str == "iter") return simple_type<ast::Type::Iterator>(begin);
				if(name->str == "stop") return simple_type<ast::Type::IteratorStop>(begin);
				if(name->str == "rng") return simple_type<ast::Type::Rng>(begin);
				if(name->str == "clock") return simple_type<ast::Type::Clock>(begin);
				if(name->str == "type") return simple_type<ast::Type::TypeT>(begin);
				if(name->str == "queue") return unary_type<ast::Type::Queue>(begin, tokens);
				if(name->str == "stack") return unary_type<ast::Type::Stack>(begin, tokens);
				if(name->str == "map") return map_type(begin, tokens);
				throw CompilerError {"Unknown type name " + name->str, name->location};
			}
			throw CompilerError {"Expected type name", begin.location};
		}




		ast::type_ptr parse_type_name_start(const Token & begin, Tokens & tokens) {
			if(auto name = match("type", tokens)) {
				if(match(TT::COLON, tokens)) {
					return parse_type_name(begin, tokens);
				}
				else {
					return simple_type<ast::Type::TypeT>(begin);
				}
			}
			return parse_type_name(begin, tokens);
		}
	}



	ast::type_ptr parse_type(Tokens & tokens) {
		if(auto begin = match(TT::SMALLER, tokens)) {
			auto type = parse_type_name_start(*begin, tokens);
			if(!match(TT::BIGGER, tokens)) throw CompilerError {
				"Expected )", begin->location
			};
			return type;
		}
		else return nullptr;
	}
}