#include <sstream>
#include <cctype>
#include <istream>
#include <iostream>
#include <unordered_map>

#include "litan_compiler/parse/tokenize.hxx"
#include "litan_compiler/CompilerError.hxx"
#include "litan_compiler/source/StringSource.hxx"



namespace ltn::c {
	struct WS {	std::size_t & line; };

	std::istream & operator>>(std::istream & in, const WS & ws) {
		while(std::isspace(in.peek())) {
			if(in.peek() == '\n') {
				ws.line++;
			}
			in.ignore();
		}
		return in;
	}


	namespace {
		using TT = Token::Type; 



		bool is_at_end(std::istream & in) {
			return in.eof();
		}



		char consume(std::istream & in) {
			return static_cast<char>(in.get());
		}



		bool check(std::istream & in, char chr) {
			if(is_at_end(in)) return false;
			return in.peek() == chr;
		}



		bool check_digit(std::istream & in) {
			return std::isdigit(in.peek());
		}



		bool check_hex_digit(std::istream & in) {
			return std::isxdigit(in.peek());
		}



		bool check_bin_digit(std::istream & in) {
			return in.peek() == '0' || in.peek() == '1';
		}



		bool check_alpha(std::istream & in) {
			return std::isalpha(in.peek());
		}



		bool check_alpha_numeric(std::istream & in) {
			return std::isalnum(in.peek());
		}


		bool check_id_start_char(std::istream & in) {
			return check_alpha(in) || check(in, '_');
		}



		bool check_id_char(std::istream & in) {
			return check_alpha_numeric(in) || check(in, '_');
		}



		bool match_char(std::istream & in, char chr) {
			const bool b = check(in, chr);
			if(b) consume(in);
			return b;
		}



		std::string read(std::istream & in, const auto & check_fx) {
			std::string str;
			while(check_fx(in)) {
				const char chr = consume(in);
				str.push_back(chr);
			}
			return str;
		}



		void comment(std::istream & in) {
			while(!is_at_end(in) && in.peek() != '\n') {
				in.ignore();
			}
		}



		const std::unordered_map<std::string_view, Token::Type> keywords{
			{"function",     TT::FUNCTION},
			{"lambda",       TT::LAMBDA},
			{"while",        TT::WHILE},
			{"for",          TT::FOR},
			{"return",       TT::RETURN},
			{"var",          TT::VAR},
			{"if",           TT::IF},
			{"else",         TT::ELSE},
			{"return",       TT::RETURN},
			{"true",         TT::TRUE},
			{"false",        TT::FALSE},
			{"namespace",    TT::NAMESPACE},
			{"except",       TT::EXCEPT},
			{"throw",        TT::THROW},
			{"null",         TT::NVLL},
			{"iife",         TT::IIFE},
			{"build_in",     TT::BUILD_IN},
			{"dynamic",      TT::DYNAMIC},
			{"enum",         TT::ENUM},
			{"def",          TT::DEFINE},
			{"switch",       TT::SWITCH},
			{"case",         TT::CASE},
			{"reflect",      TT::REFLECT},
			{"yield",        TT::YIELD},
			{"conditional",  TT::CONDITIONAL},
		};
		


		char de_escape(auto chr, const SourceLocation & location) {
			switch (chr) {
			case 'n': return '\n';
			case 't': return '\t';
			case '\\': return '\\';
			case '\"': return '\"';
			case '\'': return '\'';
			default: break;
			}
			throw CompilerError{"Invalid escape sequence", location};
		}



		template<char END> 
		std::string string(std::istream & in, const SourceLocation & location) {
			std::stringstream ss;
			while(!in.eof()) {
				const auto chr = static_cast<char>(in.get());
				if(chr == END) {
					return ss.str();
				}
				if(chr == '\"') {
					throw CompilerError{"Newline needs to be escaped \\\"", location};
				}
				if(chr == '\'') {
					throw CompilerError{"Newline needs to be escaped \\'", location};
				}
				if(chr == '\n') {
					throw CompilerError{"Newline needs to be escaped \\n", location};
				}
				if(chr == '\t') {
					throw CompilerError{"Tab needs to be escaped \\t", location};
				}
				if(chr == '\\') {
					ss << de_escape(in.get(), location);
				}
				else {
					ss << chr;
				}
			}
			throw CompilerError{"Unterminated string", location};
		}
	


		Token token(std::istream & in, SourceLocation & location) {
			const auto match = [&] (char chr) {
				return ltn::c::match_char(in, chr);
			};

			const auto make = [&location] (auto type, const auto &str) {
				return Token{type, str, location};
			};

			in >> WS{location.line};
			
			if(is_at_end(in)) return make(TT::___EOF___, "___EOF__");
			
			if(match(',')) return make(TT::COMMA, ",");
			if(match(';')) return make(TT::SEMICOLON, ";");
			if(match('~')) {
				return make(TT::TILDE, "~");
			}
			
			if(match('(')) return make(TT::PAREN_L, "(");
			if(match(')')) return make(TT::PAREN_R, ")");
			if(match('{')) return make(TT::BRACE_L, "{");
			if(match('}')) return make(TT::BRACE_R, "}");
			if(match('[')) return make(TT::BRACKET_L, "[");
			if(match(']')) return make(TT::BRACKET_R, "]");
			
			if(match('-')) {
				if(match('>')) {
					return make(TT::RARROW, "->");
				}
				return make(TT::MINUS, "-");
			}
			if(match('+')) {
				return make(TT::PLUS, "+");
			}
			if(match('*')) {
				if(match('*')) {
					return make(TT::STARx2, "**");
				}
				return make(TT::STAR, "*");
			}
			if(match('/')) {
				if(match('/')) {
					comment(in);
					return token(in, location);
				}
				return make(TT::SLASH, "/");
			}
			if(match('%')) {
				return make(TT::PERCENT, "%");
			}
			if(match('&')) {
				if(match('&')) {
					return make(TT::AND, "&&");
				}
				return make(TT::AMPERSAND, "&");
			}
			if(match('|')) {
				if(match('|')) {
					return make(TT::OR, "||");
				}
				return make(TT::BIT_OR, "|");
			}
			if(match('^')) {
				return make(TT::BIT_XOR, "^");
			}
			if(match('@')) return make(TT::AT, "@");
			
			if(match('=')) {
				if(match('=')) return make(TT::EQUAL, "==");
				if(match('>')) return make(TT::DRARROW, "=>");
				return make(TT::ASSIGN, "=");
			}

			if(match('<')) {
				if(match('<')) {
					return make(TT::SHIFT_L, "<<");
				}
				
				if(match('=')) {
					if(match('>')) return make(TT::SPACE_SHIP, "<=>");
					return make(TT::SMALLER_EQUAL, "<=");
				}
				return make(TT::SMALLER, "<");
			}

			if(match('>')) {
				if(match('>')) {
					return make(TT::SHIFT_R, ">>");
				}
				if(match('=')) return make(TT::BIGGER_EQUAL, ">=");
				return make(TT::BIGGER, ">");
			}

			if(match('!')) {
				if(match('=')) return make(TT::UNEQUAL, "!=");
				return make(TT::XMARK, "!");
			}
			
			if(match('?')) {
				return make(TT::QMARK, "?");
			}

		

			if(match('"')) {
				const auto str = string<'"'>(in, location);
				return make(TT::STRING, str);
			}

			if(match('\'')) {
				const auto str = string<'\''>(in, location);
				return make(TT::CHAR, str);
			}

			if(match('.')) {
				if(match('.')) {
					if(match('.')) {
						return make(TT::ELLIPSIS, "...");
					}
					throw CompilerError{"invalid token", location};
				}
				return make(TT::DOT, ".");
			}

			if(match(':')) {
				if(match(':')) {
					return make(TT::COLONx2, "::");
				}
				return make(TT::COLON, ":");
			}

			if(match('#')) {
				const auto str = read(in, check_id_char);
				if(str == "include") return make(TT::HASH_INCLUDE, str);
				if(str == "import") return make(TT::HASH_IMPORT, str);
				else {
					throw CompilerError{"invalid token", location};
				}
			}

			if(check_id_start_char(in)) {
				const auto str = read(in, check_id_char);
				if(keywords.contains(str)) {
					return make(keywords.at(str), str);
				}
				if(str == "_") {
					return make(TT::UNDERSCORE, str);
				}
				return make(TT::INDENTIFIER, str);
			}

			if(check_digit(in)) {
				bool zero = false;
				if(match('0')) {
					if(match('x')) {
						const auto int_literal = read(in, check_hex_digit);
						return make(TT::INTEGER_HEX, int_literal);
					}
					if(match('b')) {
						const auto int_literal = read(in, check_bin_digit);
						return make(TT::INTEGER_BIN, int_literal);
					}
					zero = true;
				}
				const auto int_literal = (zero?"0":"") + read(in, check_digit);
				if(match('.')) {
					const auto literalFraction = read(in, check_digit);
					const auto literal = int_literal + "." + literalFraction;
					return make(TT::FLOAT, literal);
				}
				return make(TT::INTEGER, int_literal);
			}

			throw CompilerError{"invalid token", location};
		}



		std::vector<Token> lex_source(std::istream & in, std::string sourcename) {
			SourceLocation loc{1, sourcename};
			std::vector<Token> tokens;
			while (true) {
				Token t = token(in, loc);
				if(t.type == TT::___EOF___) break;
				tokens += t;
			}
			tokens += Token{TT::___EOF___, "___EOF___", loc};
			return tokens;
		}
	}


	Tokens tokenize(const Source & source) {
		auto stream = source.make_istream();
		return lex_source(*stream, source.get_name());
	}
}

