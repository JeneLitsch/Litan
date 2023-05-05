// #include "parse.hxx"


// namespace ltn::c {

// 	namespace {
// 		using TT = Token::Type;

// 		ast::type_ptr parse_type_array(Tokens & tokens, BraceTracker & brace_tracker) {
// 			const auto & loc = location(tokens);
// 			open_chevron(tokens, brace_tracker);
// 			auto contains = parse_type(tokens, brace_tracker);
// 			close_chevron(tokens, brace_tracker);
// 			auto type = std::make_unique<ast::Type>(loc, "array");
// 			type->sub_types.push_back(std::move(contains));
// 			return type;
// 		}


// 		ast::type_ptr parse_type_queue(Tokens & tokens, BraceTracker & brace_tracker) {
// 			const auto & loc = location(tokens);
// 			open_chevron(tokens, brace_tracker);
// 			auto contains = parse_type(tokens, brace_tracker);
// 			close_chevron(tokens, brace_tracker);
// 			auto type = std::make_unique<ast::Type>(loc, "queue");
// 			type->sub_types.push_back(std::move(contains));
// 			return type;
// 		}


// 		ast::type_ptr parse_type_stack(Tokens & tokens, BraceTracker & brace_tracker) {
// 			const auto & loc = location(tokens);
// 			open_chevron(tokens, brace_tracker);
// 			auto contains = parse_type(tokens, brace_tracker);
// 			close_chevron(tokens, brace_tracker);
// 			auto type = std::make_unique<ast::Type>(loc, "stack");
// 			type->sub_types.push_back(std::move(contains));
// 			return type;
// 		}



// 		ast::type_ptr parse_type_optional(Tokens & tokens, BraceTracker & brace_tracker) {
// 			const auto & loc = location(tokens);
// 			open_chevron(tokens, brace_tracker);
// 			auto contains = parse_type(tokens, brace_tracker);
// 			close_chevron(tokens, brace_tracker);
// 			auto type = std::make_unique<ast::Type>(loc, "optional");
// 			type->sub_types.push_back(std::move(contains));
// 			return type;
// 		}



// 		ast::type_ptr parse_type_map(Tokens & tokens, BraceTracker & brace_tracker) {
// 			const auto & loc = location(tokens);
// 			open_chevron(tokens, brace_tracker);
// 			auto key = parse_type(tokens, brace_tracker);
// 			if(!match(TT::COMMA, tokens)) throw CompilerError{"Expected , between key type"};
// 			auto val = parse_type(tokens, brace_tracker);
// 			close_chevron(tokens, brace_tracker);
// 			auto type = std::make_unique<ast::Type>(loc, "map");
// 			type->sub_types.push_back(std::move(key));
// 			type->sub_types.push_back(std::move(val));
// 			return type;
// 		}



// 		auto parse_fx_ptr_parameters(Tokens & tokens, BraceTracker & brace_tracker) {
// 			std::vector<ast::type_ptr> parameter_types;
// 			if(match(TT::PAREN_R, tokens)) return parameter_types;
// 			do {
// 				parameter_types.push_back(parse_type(tokens, brace_tracker));
// 			} while(match(TT::COMMA, tokens));
// 			if(!match(TT::PAREN_R, tokens)) throw CompilerError{"Expected )"};
// 			return parameter_types;
// 		}



// 		ast::type_ptr parse_fx_ptr_fancy(Tokens & tokens, const Token & start, BraceTracker & brace_tracker ) {
// 			const auto & loc = location(tokens);
// 			auto parameter_types = parse_fx_ptr_parameters(tokens, brace_tracker);
// 			if(!match(TT::RARROW, tokens)) throw CompilerError {
// 				"Expected ->", start.location 
// 			};
// 			auto return_type = parse_type(tokens);
// 			auto type = std::make_unique<ast::Type>(loc, "fx_ptr", std::move(parameter_types));
// 			type->sub_types.push_back(std::move(return_type));
// 			return type;
// 		}



// 		bool is_auto(const Token & token) {
// 			return token.type == TT::INDENTIFIER
// 				&& token.str == "auto";
// 		}
// 	}



// 	ast::type_ptr parse_type(Tokens & tokens, BraceTracker & brace_tracker) {
// 		if(auto type_name = match(TT::INDENTIFIER, tokens)) {
// 			const auto & loc = location(tokens);
// 			std::vector<ast::type_ptr> elements;
// 			if(match(TT::SMALLER, tokens)) {
// 				brace_tracker.open();
// 				elements.push_back(parse_type(tokens, brace_tracker));
// 				while(match(TT::COMMA, tokens)) {
// 					elements.push_back(parse_type(tokens, brace_tracker));
// 				}
// 				close_chevron(tokens, brace_tracker);
// 			}
// 			auto type = std::make_unique<ast::Type>(loc, type_name->str, std::move(elements));
// 			return type;
// 		}
// 		if(auto type_name = match(TT::NVLL, tokens)) {
// 			return std::make_unique<ast::Type>(type_name->location, "null");
// 		}
// 		if(auto start = match(TT::PAREN_L, tokens)) {
// 			return parse_fx_ptr_fancy(tokens, *start, brace_tracker);
// 		}
// 		if(auto t = match(TT::QMARK, tokens)) {
// 			auto type = std::make_unique<ast::Type>(t->location, "optional");
// 			type->sub_types.push_back(parse_type(tokens, brace_tracker));
// 			return type;
// 		}
// 		throw CompilerError{"Expected typename", tokens.front().location};
// 	}
	


// 	ast::type_ptr parse_type(Tokens & tokens) {
// 		BraceTracker brace_tracker;
// 		auto type = parse_type(tokens, brace_tracker);
// 		brace_tracker.finalize();
// 		return type;
// 	}




// 	ast::type_ptr parse_var_type(Tokens & tokens) {
// 		auto t = match(TT::COLON, tokens);
// 		return t
// 			? parse_type(tokens)
// 			: std::make_unique<ast::Type>(location(tokens), "any");
// 	}



// 	std::optional<ast::type_ptr> parse_var_type_auto(Tokens & tokens) {
// 		if(match(TT::COLON, tokens)) {
// 			if(is_auto(tokens.front())) {
// 				tokens.pop();
// 				return std::nullopt;
// 			}
// 			else {
// 				return parse_type(tokens);
// 			}
// 		}
// 		return std::nullopt;
// 	}



// 	ast::type_ptr parse_return_type(Tokens & tokens) {
// 		auto t = match(TT::RARROW, tokens);
// 		return t
// 			? parse_type(tokens)
// 			: std::make_unique<ast::Type>(location(tokens), "any");
// 	}
// }