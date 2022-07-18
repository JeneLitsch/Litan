#include "Tokens.hxx"
#include "lexing.hxx"
#include <set>
#include <sstream>
#include "ltnc/CompilerError.hxx"

#include "ltnc/stdlib/algorithm.hxx"
#include "ltnc/stdlib/bits.hxx"
#include "ltnc/stdlib/cast.hxx"
#include "ltnc/stdlib/chrono.hxx"
#include "ltnc/stdlib/container.hxx"
#include "ltnc/stdlib/debug.hxx"
#include "ltnc/stdlib/functional.hxx"
#include "ltnc/stdlib/io.hxx"
#include "ltnc/stdlib/math.hxx"
#include "ltnc/stdlib/random.hxx"
#include "ltnc/stdlib/range.hxx"
#include "ltnc/stdlib/type.hxx"

namespace ltn::c {
	using namespace lex;
	using TT = Token::Type;

	namespace {
		std::vector<Token> lex_source(std::istream & in, std::string sourcename, Reporter & reporter) {
			SourceLocation loc{1, sourcename};
			std::vector<Token> tokens;
			while (true) {
				try {
					Token t = lex::token(in, loc);
					if(t.type == TT::___EOF___)  break;
					tokens += t;
				}
				catch(const CompilerError & error) {
					reporter.push(error);
					in.ignore();
				}
			}
			tokens += Token{TT::___EOSRC___, "___EOSRC___", loc};
			return tokens;
		}
	}
	

	Tokens lex_sources(std::vector<Source> sources, Reporter & reporter) {
		std::vector<Token> tokens;

		std::istringstream stdlib { std::string()
			+ std_algorithm
			+ std_bits
			+ std_cast
			+ std_chrono
			+ std_container
			+ std_debug
			+ std_functional
			+ std_io
			+ std_math
			+ std_random
			+ std_range
			+ std_type
		};

		tokens += lex_source(stdlib, "stdlib", reporter);

		for(auto & source : sources) {
			tokens += lex_source(source.stream(), source.name(), reporter);
		}
		
		tokens += Token::end;
		return Tokens{ std::move(tokens) };
	}

	std::optional<lex::Token> match(lex::Token::Type type, Tokens & tokens) {
		if(tokens.empty()) return std::nullopt;
		const Token t = tokens.front(); 
		if(t.type != type) return std::nullopt;
		tokens.pop();
		return t;
	}

	void sync(Tokens & tokens) {
		const static std::set<TT> stops {
			TT::___EOF___,
			TT::SEMICOLON,
			TT::NAMESPACE,
			TT::FUNCTION,
			TT::BUILD_IN,
			TT::VAR,
			TT::FOR,
			TT::WHILE,
			TT::IF,
			TT::ELSE,
			TT::BRACE_R,
		};
		
		// if(tokens.empty()) {
		// 	tokens.unpop();
		// 	return;
		// }
		// std::cout << this->current->str << std::endl;
		if(tokens.front().type == TT::___EOF___) return;
		tokens.pop();
		while(!stops.contains(tokens.front().type)) {
			// std::cout << this->current->str << "\n";
			tokens.pop();
		}
		match(TT::SEMICOLON, tokens);
	}

	const SourceLocation & location(const Tokens & tokens) {
		const static SourceLocation fallback {0, ""};
		return (tokens.empty()) ? fallback : tokens.front().location;
	}
}

