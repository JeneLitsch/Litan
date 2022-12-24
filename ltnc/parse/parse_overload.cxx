#include "parse.hxx"

namespace ltn::c {
	namespace {
		using TT = Token::Type;



		ast::Overload::Element parse_overload_elements(
			const SourceLocation & location,
			Tokens & tokens) {
			const auto [name, namespaze] = parse_symbol(tokens);
			if(!match(TT::SEMICOLON, tokens)) throw CompilerError{
				"Expected ;",
				location
			};
			return ast::Overload::Element {
				.name = name,
				.namespaze = namespaze
			};
		}
	}

	std::unique_ptr<ast::Overload> parse_overload(
		Tokens & tokens,
		const Namespace & namespaze) {
		
		if(auto begin = match(TT::OVERLOAD, tokens)) {
			const auto [name, namespaze] = parse_symbol(tokens);
			if(!match(TT::PAREN_L, tokens)) throw CompilerError{
				"Expected (",
				begin->location
			};
			std::uint64_t arity = parse_placeholder(tokens);
			if(!match(TT::BRACE_L, tokens)) throw CompilerError{
				"Expected {",
				begin->location
			};

			std::vector<ast::Overload::Element> elements;

			while(!match(TT::BRACE_R, tokens)) {
				auto element = parse_overload_elements(begin->location, tokens);
				elements.push_back(std::move(element));
			};


			return std::make_unique<ast::Overload>(
				begin->location,
				std::move(name),
				std::move(namespaze),
				arity,
				std::move(elements)
			);
		}
		else return nullptr;
	}
}