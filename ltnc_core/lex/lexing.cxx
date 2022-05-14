#include "lexing.hxx"
#include <unordered_map>
#include "ltnc_core/CompilerError.hxx"
#include "WS.hxx"
#include <sstream>

namespace ltn::c::lex {
	namespace {
		using TT = Token::Type; 

		// Returns true if stream is empty 
		bool is_at_end(std::istream & in) {
			return in.eof();
		}

		// return next char from "in"
		char consume(std::istream & in) {
			return static_cast<char>(in.get());
		}

		// peeks at "in" and returns true if chars matches
		bool check(std::istream & in, char chr, std::size_t & line) {
			in >> WS{line};
			if(is_at_end(in)) return false;
			return in.peek() == chr;
		}

		// returns true if next char is a digit
		bool check_digit(std::istream & in) {
			return std::isdigit(in.peek());
		}

		// returns true if next char is a hex digit
		bool check_hex_digit(std::istream & in) {
			return std::isxdigit(in.peek());
		}

		// returns true if next char is a hex digit
		bool check_bin_digit(std::istream & in) {
			return in.peek() == '0' || in.peek() == '1';
		}

		// returns true if next char is a letter
		bool check_alpha(std::istream & in) {
			return std::isalpha(in.peek());
		}

		// returns true if next char is a letter or digit
		bool check_alpha_numeric(std::istream & in) {
			return std::isalnum(in.peek());
		}

		bool check_id_char(std::istream & in) {
			return check_alpha_numeric(in) || in.peek() == '_';
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
			while(!is_at_end(in) && in.peek() != '\n') {
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
			{"if",          TT::IF},
			{"else",        TT::ELSE},
			{"return",      TT::RETURN},
			{"true",        TT::TRUE},
			{"false",       TT::FALSE},
			{"namespace",   TT::NAMESPACE},
			{"except",      TT::EXCEPT},
			{"throw",       TT::THROW},
			{"null",        TT::NVLL},
			{"iife",        TT::IIFE},
			{"build_in",    TT::BUILD_IN},
			{"enum",        TT::ENUM},
			{"define",      TT::DEFINE},
			{"preset",      TT::PRESET},
			{"switch",      TT::SWITCH},
			{"choose",      TT::CHOOSE},
			{"case",        TT::CASE},
			{"default",     TT::DEFAULT},
		};
		

		template<char END> 
		char de_escape(auto chr, const SourceLocation & location) {
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
					ss << de_escape<END>(in.get(), location);
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
		
		if(is_at_end(in)) return make(TT::___EOF___, "___EOF__");
		
		if(match(',')) return make(TT::COMMA, ",");
		if(match(';')) return make(TT::SEMICOLON, ";");
		if(match('~')) {
			if(match('~')) {
				return make(TT::TILDEx2, "~~");
			}
			return make(TT::TILDE, "~");
		}
		
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
			if(match('>')) {
				return make(TT::RARROW, "->");
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
			if(match('*')) {
				if(match('=')) {
					return make(TT::ASSIGN_POW, "**=");
				}
				return make(TT::STARx2, "**");
			}
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
			if(match('=')) {
				return make(TT::ASSIGN_BIT_AND, "&=");
			}
			return make(TT::AMPERSAND, "&");
		}
		if(match('|')) {
			if(match('|')) {
				return make(TT::OR, "||");
			}
			if(match('=')) {
				return make(TT::ASSIGN_BIT_OR, "|=");
			}
			return make(TT::BIT_OR, "|");
		}
		if(match('^')) {
			if(match('=')) {
				return make(TT::ASSIGN_BIT_XOR, "^=");
			}
			return make(TT::BIT_XOR, "^");
		}
		if(match('_')) return make(TT::UNDERSCORE, "_");
		if(match('@')) return make(TT::AT, "@");
		
		if(match('=')) {
			if(match('=')) return make(TT::EQUAL, "==");
			if(match('>')) return make(TT::DRARROW, "=>");
			return make(TT::ASSIGN, "=");
		}

		if(match('<')) {
			if(match('<')) {
				if(match('=')) return make(TT::ASSIGN_SHIFT_L, "<<=");
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
				if(match('=')) return make(TT::ASSIGN_SHIFT_R, ">>=");
				return make(TT::SHIFT_R, ">>");
			}
			if(match('=')) return make(TT::BIGGER_EQUAL, ">=");
			return make(TT::BIGGER, ">");
		}

		if(match('!')) {
			if(match('=')) return make(TT::UNEQUAL, "!=");
			if(match('~')) return make(TT::XMARK_TILDE, "!~");
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
			return make(TT::COLON, ":");
		}

		if(check_alpha(in)) {
			const auto str = read(in, check_id_char);
			if(keywords.contains(str)) {
				return make(keywords.at(str), str);
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
}

