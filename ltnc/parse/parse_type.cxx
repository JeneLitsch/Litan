#include "parse.hxx"


namespace ltn::c {

	namespace {

		using TT = Token::Type;


		type::Array parse_type_array(Tokens & tokens, BraceTracker & brace_tracker) {
			open_chevron(tokens, brace_tracker);
			auto contains = parse_type(tokens, brace_tracker);
			close_chevron(tokens, brace_tracker);
			return type::Array{contains};
		}



		type::Optional parse_type_optional(Tokens & tokens, BraceTracker & brace_tracker) {
			open_chevron(tokens, brace_tracker);
			auto contains = parse_type(tokens, brace_tracker);
			close_chevron(tokens, brace_tracker);
			return type::Optional{
				.contains = contains
			};
		}



		type::Map parse_type_map(Tokens & tokens, BraceTracker & brace_tracker) {
			open_chevron(tokens, brace_tracker);
			auto key = parse_type(tokens, brace_tracker);
			if(!match(TT::COMMA, tokens)) throw CompilerError{"Expected , between key type"};
			auto val = parse_type(tokens, brace_tracker);
			close_chevron(tokens, brace_tracker);
			return type::Map{
				.key = key,
				.val = val,
			};
		}



		type::Type parse_fxptr(Tokens & tokens, BraceTracker & brace_tracker) {
			open_chevron(tokens, brace_tracker);
			auto return_type = parse_type(tokens, brace_tracker);
			if(!match(TT::PAREN_L, tokens)) throw CompilerError{"Expected ("};
			std::vector<type::Type> parameter_types;
			do {
				parameter_types.push_back(parse_type(tokens, brace_tracker));
			} while(match(TT::COMMA, tokens));
			if(!match(TT::PAREN_R, tokens)) throw CompilerError{"Expected )"};
			close_chevron(tokens, brace_tracker);
			return type::FxPtr {
				.return_type = return_type,
				.parameter_types = parameter_types
			};
		}
	}



	type::Type parse_type(Tokens & tokens, BraceTracker & brace_tracker) {
		if(auto type_name = match(TT::NVLL, tokens)) {
			return type::Null{};
		}
		if(auto type_name = match(TT::INDENTIFIER, tokens)) {
			if(type_name->str == "any") return type::Any{};
			if(type_name->str == "bool") return type::Bool{}; 
			if(type_name->str == "char") return type::Char{}; 
			if(type_name->str == "int") return type::Int{}; 
			if(type_name->str == "float") return type::Float{}; 
			if(type_name->str == "string") return type::String{}; 
			if(type_name->str == "array") return parse_type_array(tokens, brace_tracker); 
			if(type_name->str == "map") return parse_type_map(tokens, brace_tracker);
			if(type_name->str == "fx_ptr") return parse_fxptr(tokens, brace_tracker);
			if(type_name->str == "optional") return parse_type_optional(tokens, brace_tracker);
			throw CompilerError{"Unknown type name " + type_name->str};
		}
		else if(match(TT::QMARK, tokens)) {
			return type::Optional{parse_type(tokens, brace_tracker)};
		}
		else {
			throw CompilerError{"Expected type name"};
		}
	}
	


	type::Type parse_type(Tokens & tokens) {
		BraceTracker brace_tracker;
		auto type = parse_type(tokens, brace_tracker);
		brace_tracker.finalize();
		return type;
	}


	type::Type parse_parameter_type(Tokens & tokens) {
		return match(TT::COLON, tokens) ? parse_type(tokens) : type::Any{};
	}


	type::Type parse_var_type(Tokens & tokens) {
		return match(TT::COLON, tokens) ? parse_type(tokens) : type::Any{};
	}


	std::variant<type::Type, type::Auto> parse_var_type_auto(Tokens & tokens) {
		if(match(TT::COLON, tokens)) {
			if(tokens.front().type == TT::INDENTIFIER && tokens.front().str == "auto") {
				tokens.pop();
				return type::Auto{};
			}
			else {
				return parse_type(tokens);
			}
		}
		return type::Any{};
	}



	type::Type parse_return_type(Tokens & tokens) {
		return match(TT::RARROW, tokens) ? parse_type(tokens) : type::Any{};
	}
}