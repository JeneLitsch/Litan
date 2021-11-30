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
		const static std::unordered_map<std::string_view, Token::Type> keywords{
			{"function",    Token::Type::FUNCTION},
			{"while",       Token::Type::WHILE},
			{"for",         Token::Type::FOR},
			{"return",      Token::Type::RETURN},
			{"var",         Token::Type::VAR},
			{"if",          Token::Type::IF},
			{"else",        Token::Type::ELSE},
			{"new",         Token::Type::NEW},
			{"return",      Token::Type::RETURN},
			{"true",        Token::Type::TRUE},
			{"false",       Token::Type::FALSE},
			{"asm",         Token::Type::ASM},
			{"namespace",   Token::Type::NAMESPACE},
		};
		
		 
		char deEscape(auto chr, std::size_t & line) {
			switch (chr) {
			case 'n': return '\n';
			case 't': return '\t';
			case '\\': return '\\';
			case '"': return '"';
			default: break;
			}
			throw CompilerError{"Invalid escape sequence", line};
		}

		// Reads and deescape string from in
		std::string string(std::istream & in, std::size_t & line) {
			std::stringstream ss;
			while(!in.eof()) {
				const auto chr = static_cast<char>(in.get());
				if(chr == '"') {
					return ss.str();
				}
				if(chr == '\n') {
					throw CompilerError{"Newline needs to be escaped \\n", line};
				}
				if(chr == '\t') {
					throw CompilerError{"Tab needs to be escaped \\t", line};
				}
				if(chr == '\\') {
					ss << deEscape(in.get(), line);
				}
				else {
					ss << chr;
				}
			}
			throw CompilerError{"Unterminated string", line};
		}
	}
	
	Token token(std::istream & in, std::size_t & line) {
		const auto match = [&] (auto chr) {
			return ltn::c::lex::match(in, chr, line);
		};
		if(isAtEnd(in >> WS{line})) return {Token::Type::___EOF___, "___EOF___"};
		
		if(match(',')) return {Token::Type::COMMA, ","};
		if(match(';')) return {Token::Type::SEMICOLON, ";"};
		
		if(match('(')) return {Token::Type::PAREN_L, "("};
		if(match(')')) return {Token::Type::PAREN_R, ")"};
		if(match('{')) return {Token::Type::BRACE_L, "{"};
		if(match('}')) return {Token::Type::BRACE_R, "}"};
		if(match('[')) return {Token::Type::BRACKET_L, "["};
		if(match(']')) return {Token::Type::BRACKET_R, "]"};
		
		if(match('-')) {
			if(match('=')) {
				return {Token::Type::ASSIGN_SUB, "-="};
			}
			return {Token::Type::MINUS, "-"};
		}
		if(match('+')) {
			if(match('=')) {
				return {Token::Type::ASSIGN_ADD, "+="};
			}
			return {Token::Type::PLUS, "+"};
		}
		if(match('*')) {
			if(match('=')) {
				return {Token::Type::ASSIGN_MLT, "*="};
			}
			return {Token::Type::STAR, "*"};
		}
		if(match('/')) {
			if(match('=')) {
				return {Token::Type::ASSIGN_DIV, "/="};
			}
			if(match('/')) {
				comment(in);
				return token(in, line);
			}
			return {Token::Type::SLASH, "/"};
		}
		if(match('%')) {
			if(match('=')) {
				return {Token::Type::ASSIGN_MOD, "%="};
			}
			return {Token::Type::PERCENT, "%"};
		}
		if(match('&')) {
			if(match('&')) {
				return {Token::Type::AND, "&&"};
			}
			return {Token::Type::AMPERSAND, "&"};
		}
		if(match('|')) {
			if(match('|')) {
				return {Token::Type::OR, "||"};
			}
			throw CompilerError{"\"|\" is not a valid token.", line};
		}
		if(match('_')) return {Token::Type::UNDERSCORE, "_"};
		
		if(match('=')) {
			if(match('=')) return {Token::Type::EQUAL, "=="};
			return {Token::Type::ASSIGN, "="};
		}

		if(match('<')) {
			if(match('<')) return {Token::Type::SHIFT_L, "<<"};
			if(match('=')) return {Token::Type::SMALLER_EQUAL, "<="};
			return {Token::Type::SMALLER, "<"};
		}
		if(match('>')) {
			if(match('>')) return {Token::Type::SHIFT_R, ">>"};
			if(match('=')) return {Token::Type::BIGGER_EQUAL, ">="};
			return {Token::Type::BIGGER, ">"};
		}
		if(match('!')) {
			if(match('=')) return {Token::Type::UNEQUAL, "!="};
			return {Token::Type::NOT, "!"};
		}

		if(match('"')) {
			const auto str = string(in, line);
			return {Token::Type::STRING, str};
		}

		if(match(':')) {
			if(match(':')) {
				return {Token::Type::COLONx2, "::"};
			}
			throw CompilerError{"\":\" is not a valid token.", line};
		}

		if(checkAlpha(in)) {
			const auto str = read(in, checkAlNum);
			if(keywords.contains(str)) {
				return {keywords.at(str), str};
			}
			return {Token::Type::INDENTIFIER, str};
		}

		if(checkDigit(in)) {
			if(match('0')) {
				if(match('x')) {
					const auto literalInt = read(in, checkHexDigit);
					return {Token::Type::INTEGER_HEX, literalInt};
				}
				if(match('b')) {
					const auto literalInt = read(in, checkBinDigit);
					return {Token::Type::INTEGER_BIN, literalInt};
				}
				throw CompilerError{"Leading 0s not allowed", line};
			}
			else {
				const auto literalInt = read(in, checkDigit);
				if(match('.')) {
					const auto literalFraction = read(in, checkDigit);
					const auto literal = literalInt + "." + literalFraction;
					return {Token::Type::FLOAT, literal};
				}
				return {Token::Type::INTEGER, literalInt};
			}
		}

		throw CompilerError{"invalid token", line};
	}
}

