#include "lexing.hxx"
#include <unordered_map>
#include "ltnc/CompilerError.hxx"
#include "WS.hxx"
#include <sstream>

namespace ltn::c::lex {
	namespace {
		using TT = Token::Type; 

		// Returns true if stream is empty 
		bool isAtEnd(std::istream & in) {
			return in.eof();
		}

		// return next char from "in"
		char consume(std::istream & in) {
			return static_cast<char>(in.get());
		}

		// peeks at "in" and returns true if chars matches
		bool check(std::istream & in, char chr, std::size_t & line) {
			in >> WS{line};
			if(isAtEnd(in)) return false;
			return in.peek() == chr;
		}

		// returns true if next char is a digit
		bool checkDigit(std::istream & in) {
			return std::isdigit(in.peek());
		}

		// returns true if next char is a hex digit
		bool checkHexDigit(std::istream & in) {
			return std::isxdigit(in.peek());
		}

		// returns true if next char is a hex digit
		bool checkBinDigit(std::istream & in) {
			return in.peek() == '0' || in.peek() == '1';
		}

		// returns true if next char is a letter
		bool checkAlpha(std::istream & in) {
			return std::isalpha(in.peek());
		}

		// returns true if next char is a letter or digit
		bool checkAlNum(std::istream & in) {
			return std::isalnum(in.peek());
		}

		bool checkIdChar(std::istream & in) {
			return checkAlNum(in) || in.peek() == '_';
		}

		// returns true and consumes if the next char matches 
		bool match(std::istream & in, char chr, std::size_t & line) {
			const bool b = check(in, chr, line);
			if(b) consume(in);
			return b;
		}

		// fetches from "in" while checkFx returns true
		std::string read(std::istream & in, const auto & checkFx) {
			std::string str;
			while(checkFx(in)) {
				const char chr = consume(in);
				str.push_back(chr);
			}
			return str;
		}

		// ignores rest of line
		void comment(std::istream & in) {
			while(!isAtEnd(in) && in.peek() != '\n') {
				in.ignore();
			}
		}


		// Table of keywords
		const std::unordered_map<std::string_view, Token::Type> keywords{
			{"function",    TT::FUNCTION},
			{"lambda",      TT::LAMBDA},
			{"while",       TT::WHILE},
			{"for",         TT::FOR},
			{"return",      TT::RETURN},
			{"var",         TT::VAR},
			{"const",       TT::CONST},
			{"if",          TT::IF},
			{"else",        TT::ELSE},
			{"return",      TT::RETURN},
			{"true",        TT::TRUE},
			{"false",       TT::FALSE},
			{"asm",         TT::ASM},
			{"namespace",   TT::NAMESPACE},
			{"except",      TT::EXCEPT},
			{"throw",       TT::THROW},
		};
		

		template<char END> 
		char deEscape(auto chr, const SourceLocation & location) {
			switch (chr) {
			case 'n': return '\n';
			case 't': return '\t';
			case '\\': return '\\';
			case END: return END;
			default: break;
			}
			throw CompilerError{"Invalid escape sequence", location};
		}

		// Reads and deescape string from in
		template<char END> 
		std::string string(std::istream & in, const SourceLocation & location) {
			std::stringstream ss;
			while(!in.eof()) {
				const auto chr = static_cast<char>(in.get());
				if(chr == END) {
					return ss.str();
				}
				if(chr == '\n') {
					throw CompilerError{"Newline needs to be escaped \\n", location};
				}
				if(chr == '\t') {
					throw CompilerError{"Tab needs to be escaped \\t", location};
				}
				if(chr == '\\') {
					ss << deEscape<END>(in.get(), location);
				}
				else {
					ss << chr;
				}
			}
			throw CompilerError{"Unterminated string", location};
		}
	}
	
	Token token(std::istream & in, SourceLocation & location) {
		const auto match = [&] (auto chr) {
			return ltn::c::lex::match(in, chr, location.line);
		};

		const auto make = [&location] (auto type, const auto &str) {
			return Token{type, str, location};
		};

		in >> WS{location.line};
		
		if(isAtEnd(in)) return make(TT::___EOF___, "___EOF__");
		
		if(match(',')) return make(TT::COMMA, ",");
		if(match(';')) return make(TT::SEMICOLON, ";");
		
		if(match('(')) return make(TT::PAREN_L, "(");
		if(match(')')) return make(TT::PAREN_R, ")");
		if(match('{')) return make(TT::BRACE_L, "{");
		if(match('}')) return make(TT::BRACE_R, "}");
		if(match('[')) return make(TT::BRACKET_L, "[");
		if(match(']')) return make(TT::BRACKET_R, "]");
		
		if(match('-')) {
			if(match('=')) {
				return make(TT::ASSIGN_SUB, "-=");
			}
			return make(TT::MINUS, "-");
		}
		if(match('+')) {
			if(match('=')) {
				return make(TT::ASSIGN_ADD, "+=");
			}
			return make(TT::PLUS, "+");
		}
		if(match('*')) {
			if(match('=')) {
				return make(TT::ASSIGN_MLT, "*=");
			}
			return make(TT::STAR, "*");
		}
		if(match('/')) {
			if(match('=')) {
				return make(TT::ASSIGN_DIV, "/=");
			}
			if(match('/')) {
				comment(in);
				return token(in, location);
			}
			return make(TT::SLASH, "/");
		}
		if(match('%')) {
			if(match('=')) {
				return make(TT::ASSIGN_MOD, "%=");
			}
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
			throw CompilerError{"\"|\" is not a valid token.", location};
		}
		if(match('_')) return make(TT::UNDERSCORE, "_");
		
		if(match('=')) {
			if(match('=')) return make(TT::EQUAL, "==");
			return make(TT::ASSIGN, "=");
		}

		if(match('<')) {
			if(match('<')) return make(TT::SHIFT_L, "<<");
			if(match('=')) return make(TT::SMALLER_EQUAL, "<=");
			return make(TT::SMALLER, "<");
		}
		if(match('>')) {
			if(match('>')) return make(TT::SHIFT_R, ">>");
			if(match('=')) return make(TT::BIGGER_EQUAL, ">=");
			return make(TT::BIGGER, ">");
		}
		if(match('!')) {
			if(match('=')) return make(TT::UNEQUAL, "!=");
			return make(TT::NOT, "!");
		}

		if(match('"')) {
			const auto str = string<'"'>(in, location);
			return make(TT::STRING, str);
		}

		if(match('\'')) {
			const auto str = string<'\''>(in, location);
			if(str.size() != 1) {
				throw CompilerError{"Expected single char", location};
			}
			return make(TT::CHAR, str);
		}

		if(match('.')) {
			return make(TT::DOT, ".");
		}

		if(match(':')) {
			if(match(':')) {
				return make(TT::COLONx2, "::");
			}
			throw CompilerError{"\":\" is not a valid token.", location};
		}

		if(checkAlpha(in)) {
			const auto str = read(in, checkIdChar);
			if(keywords.contains(str)) {
				return make(keywords.at(str), str);
			}
			return make(TT::INDENTIFIER, str);
		}

		if(checkDigit(in)) {
			bool zero = false;
			if(match('0')) {
				if(match('x')) {
					const auto literalInt = read(in, checkHexDigit);
					return make(TT::INTEGER_HEX, literalInt);
				}
				if(match('b')) {
					const auto literalInt = read(in, checkBinDigit);
					return make(TT::INTEGER_BIN, literalInt);
				}
				zero = true;
			}
			const auto literalInt = (zero?"0":"") + read(in, checkDigit);
			if(match('.')) {
				const auto literalFraction = read(in, checkDigit);
				const auto literal = literalInt + "." + literalFraction;
				return make(TT::FLOAT, literal);
			}
			return make(TT::INTEGER, literalInt);
		}

		throw CompilerError{"invalid token", location};
	}
}

