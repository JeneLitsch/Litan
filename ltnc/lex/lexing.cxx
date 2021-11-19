#include "lexing.hxx"
#include <unordered_map>
#include "ltnc/CompilerError.hxx"
#include "WS.hxx"

namespace ltn::c::lex {
	namespace {
		using TT = Token::Type; 
		bool isAtEnd(std::istream & in) {
			return in.eof();
		}

		char consume(std::istream & in) {
			return static_cast<char>(in.get());
		}

		
		bool check(std::istream & in, char chr, std::size_t & line) {
			in >> WS(line);
			if(isAtEnd(in)) return false;
			return in.peek() == chr;
		}

		bool checkDigit(std::istream & in) {
			return std::isdigit(in.peek());
		}

		bool checkAlpha(std::istream & in) {
			return std::isalpha(in.peek());
		}

		bool checkAlNum(std::istream & in) {
			return std::isalnum(in.peek());
		}

		bool match(std::istream & in, char chr, std::size_t & line) {
			const bool b = check(in, chr, line);
			if(b) consume(in);
			return b;
		}

		std::string read(std::istream & in, const auto & checkFx) {
			std::string str;
			while(checkFx(in)) {
				const char chr = consume(in);
				str.push_back(chr);
			}
			return str;
		}

		void comment(std::istream & in, std::size_t & line) {
			while(in.peek() != '\n' && !isAtEnd(in)) {
				in.ignore();
			}
		}

		const static std::unordered_map<std::string_view, Token::Type> keywords{
			{"function", 	Token::Type::FUNCTION},
			{"while", 		Token::Type::WHILE},
			{"return", 		Token::Type::RETURN},
			{"var", 		Token::Type::VAR},
			{"if", 			Token::Type::IF},
			{"else", 		Token::Type::ELSE},
			{"new", 		Token::Type::NEW},
			{"return", 		Token::Type::RETURN},
			{"true", 		Token::Type::TRUE},
			{"false", 		Token::Type::FALSE},
		};
	}
	
	Token token(std::istream & in, std::size_t & line) {
		const auto match = [&] (auto & in, auto chr) {
			return ltn::c::lex::match(in, chr, line);
		};
		if(isAtEnd(in >> WS(line))) return {Token::Type::___EOF___, "___EOF___"};
		
		if(match(in, ',')) return {Token::Type::COMMA, ","};
		if(match(in, ';')) return {Token::Type::SEMICOLON, ";"};
		
		if(match(in, '(')) return {Token::Type::PAREN_L, "("};
		if(match(in, ')')) return {Token::Type::PAREN_R, ")"};
		if(match(in, '{')) return {Token::Type::BRACE_L, "{"};
		if(match(in, '}')) return {Token::Type::BRACE_R, "}"};
		if(match(in, '[')) return {Token::Type::BRACKET_L, "["};
		if(match(in, ']')) return {Token::Type::BRACKET_R, "]"};
		
		if(match(in, '-')) {
			if(match(in, '>')) return {Token::Type::ARROW, "->"};
			return {Token::Type::MINUS, "-"};
		}
		if(match(in, '+')) return {Token::Type::PLUS, "+"};
		if(match(in, '*')) return {Token::Type::STAR, "*"};
		if(match(in, '/')) {
			if(match(in, '/')) {
				comment(in, line);
				return token(in, line);
			}
			return {Token::Type::SLASH, "*"};
		}
		if(match(in, '%')) return {Token::Type::PERCENT, "%"};
		
		if(match(in, '=')) {
			if(match(in, '=')) return {Token::Type::EQUAL, "=="};
			return {Token::Type::ASSIGN, "="};
		}
		if(match(in, '<')) {
			if(match(in, '=')) return {Token::Type::SMALLER_EQUAL, "<="};
			return {Token::Type::SMALLER, "<"};
		}
		if(match(in, '>')) {
			if(match(in, '=')) return {Token::Type::BIGGER_EQUAL, ">="};
			return {Token::Type::BIGGER, ">"};
		}
		if(match(in, '!')) {
			if(match(in, '=')) return {Token::Type::UNEQUAL, "!="};
			return {Token::Type::NOT, "!"};
		}

		if(checkAlpha(in)) {
			const auto str = read(in, checkAlNum);
			if(keywords.contains(str)) {
				return {keywords.at(str), str};
			}
			return {Token::Type::INDENTIFIER, str};
		}

		if(checkDigit(in)) {
			const auto literalInt = read(in, checkDigit);
			if(match(in, '.')) {
				const auto literalFraction = read(in, checkDigit);
				return {Token::Type::FLOAT, literalInt + "." + literalFraction};
			}
			return {Token::Type::INTEGER, literalInt};
		}

		throw CompilerError{"invalid token", line};
	}
}

