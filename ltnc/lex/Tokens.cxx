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
			tokens += Token{TT::___EOSRC___, "___EOSRC___", SourceLocation{}};
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

	Tokens::Tokens(std::vector<Token> tokens) : tokens(std::move(tokens)) {
		this->current = this->tokens.begin();
	}

	std::optional<Token> Tokens::match(Token::Type type) {
		if(this->current->type == type) {
			Token t = *this->current; 
			std::advance(this->current, 1);
			return t;
		}
		else {
			return {};
		}
	}

	
	bool Tokens::check(Token::Type type) {
		return this->current->type == type;
	}


	void Tokens::sync() {
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
		
		if(this->current == this->tokens.end()) {
			std::advance(this->current, -1);
			return;
		}
		// std::cout << this->current->str << std::endl;
		if(this->current->type == TT::___EOF___) return;
		std::advance(this->current, 1);
		while(!stops.contains(this->current->type)) {
			// std::cout << this->current->str << "\n";
			std::advance(this->current, 1);
		}
		this->match(TT::SEMICOLON);
	}

	std::optional<lex::Token> match(lex::Token::Type type, Tokens & tokens) {
		return tokens.match(type);
	}
}

