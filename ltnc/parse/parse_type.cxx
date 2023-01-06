#include "parse.hxx"


namespace ltn::c {

	namespace {
		using TT = Token::Type;

		type::Array parse_type_array(Tokens & tokens, BraceTracker & brace_tracker) {
			open_chevron(tokens, brace_tracker);
			auto contains = parse_type(tokens, brace_tracker).type;
			close_chevron(tokens, brace_tracker);
			return type::Array{contains};
		}


		type::Queue parse_type_queue(Tokens & tokens, BraceTracker & brace_tracker) {
			open_chevron(tokens, brace_tracker);
			auto contains = parse_type(tokens, brace_tracker).type;
			close_chevron(tokens, brace_tracker);
			return type::Queue{contains};
		}


		type::Stack parse_type_stack(Tokens & tokens, BraceTracker & brace_tracker) {
			open_chevron(tokens, brace_tracker);
			auto contains = parse_type(tokens, brace_tracker).type;
			close_chevron(tokens, brace_tracker);
			return type::Stack{contains};
		}



		type::Optional parse_type_optional(Tokens & tokens, BraceTracker & brace_tracker) {
			open_chevron(tokens, brace_tracker);
			auto contains = parse_type(tokens, brace_tracker).type;
			close_chevron(tokens, brace_tracker);
			return type::Optional{
				.contains = contains
			};
		}



		type::Map parse_type_map(Tokens & tokens, BraceTracker & brace_tracker) {
			open_chevron(tokens, brace_tracker);
			auto key = parse_type(tokens, brace_tracker).type;
			if(!match(TT::COMMA, tokens)) throw CompilerError{"Expected , between key type"};
			auto val = parse_type(tokens, brace_tracker).type;
			close_chevron(tokens, brace_tracker);
			return type::Map{
				.key = key,
				.val = val,
			};
		}



		auto parse_fx_ptr_parameters(Tokens & tokens, BraceTracker & brace_tracker) {
			std::vector<type::Type> parameter_types;
			if(match(TT::PAREN_R, tokens)) return parameter_types;
			do {
				parameter_types.push_back(parse_type(tokens, brace_tracker).type);
			} while(match(TT::COMMA, tokens));
			if(!match(TT::PAREN_R, tokens)) throw CompilerError{"Expected )"};
			return parameter_types;
		}



		type::Type parse_fx_ptr_fancy(Tokens & tokens, const Token & start, BraceTracker & brace_tracker ) {
			auto parameter_types = parse_fx_ptr_parameters(tokens, brace_tracker);
			if(!match(TT::RARROW, tokens)) throw CompilerError {
				"Expected ->", start.location 
			};
			const auto return_type = parse_type(tokens).type;
			return type::FxPtr{
				.return_type = return_type,
				.parameter_types = parameter_types,
			};
		}



		bool is_auto(const Token & token) {
			return token.type == TT::INDENTIFIER
				&& token.str == "auto";
		}
	}



	type::IncompleteType parse_type(Tokens & tokens, BraceTracker & brace_tracker) {
		if(auto type_name = match(TT::INDENTIFIER, tokens)) {
			if(type_name->str == "any") return type::IncompleteType{type::Any{}};
			if(type_name->str == "bool") return type::IncompleteType{type::Bool{}}; 
			if(type_name->str == "char") return type::IncompleteType{type::Char{}}; 
			if(type_name->str == "int") return type::IncompleteType{type::Int{}}; 
			if(type_name->str == "float") return type::IncompleteType{type::Float{}}; 
			if(type_name->str == "string") return type::IncompleteType{type::String{}}; 
			if(type_name->str == "array") return type::IncompleteType{parse_type_array(tokens, brace_tracker)}; 
			if(type_name->str == "queue") return type::IncompleteType{parse_type_queue(tokens, brace_tracker)}; 
			if(type_name->str == "stack") return type::IncompleteType{parse_type_stack(tokens, brace_tracker)}; 
			if(type_name->str == "map") return type::IncompleteType{parse_type_map(tokens, brace_tracker)};
			if(type_name->str == "optional") return type::IncompleteType{parse_type_optional(tokens, brace_tracker)};
			return type::IncompleteType{type::Other{.type_name = type_name->str}};
		}
		if(auto type_name = match(TT::NVLL, tokens)) {
			return type::IncompleteType{type::Null{}};
		}
		if(auto start = match(TT::PAREN_L, tokens)) {
			return type::IncompleteType{parse_fx_ptr_fancy(tokens, *start, brace_tracker)};
		}
		if(match(TT::QMARK, tokens)) {
			return type::IncompleteType{type::Optional{parse_type(tokens, brace_tracker).type}};
		}
		throw CompilerError{"Expected typename", tokens.front().location};
	}
	


	type::IncompleteType parse_type(Tokens & tokens) {
		BraceTracker brace_tracker;
		auto type = parse_type(tokens, brace_tracker);
		brace_tracker.finalize();
		return type;
	}



	type::IncompleteType parse_parameter_type(Tokens & tokens) {
		return match(TT::COLON, tokens)
			? parse_type(tokens)
			: type::IncompleteType{type::Any{}};
	}



	type::IncompleteType parse_var_type(Tokens & tokens) {
		return match(TT::COLON, tokens)
			? parse_type(tokens)
			: type::IncompleteType{type::Any{}};
	}



	std::optional<type::IncompleteType>	parse_var_type_auto(Tokens & tokens) {
		if(match(TT::COLON, tokens)) {
			if(is_auto(tokens.front())) {
				tokens.pop();
				return std::nullopt;
			}
			else {
				return parse_type(tokens);
			}
		}
		return std::nullopt;
	}



	type::IncompleteType parse_return_type(Tokens & tokens) {
		return match(TT::RARROW, tokens)
			? parse_type(tokens)
			: type::IncompleteType{type::Any{}};
	}
}