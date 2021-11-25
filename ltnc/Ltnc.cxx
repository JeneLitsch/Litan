#include "Ltnc.hxx"
#include <vector>
#include "lex/Lexer.hxx"
#include "parse/parsing.hxx"
#include <string_view>
using namespace std::string_view_literals;

const std::span<const std::string_view> ltn::c::Ltnc::stdLib() const {
	constexpr static std::array stdFiles {
		"io.ltn"sv,
		"math.ltn"sv,
	};
	return stdFiles;
}

void ltn::c::Ltnc::compile(std::istream & in, const std::string &) {
	this->line = 0;
	lex::Lexer lexer{in, this->line};
	auto source = parse::source(lexer);
	this->backend->compile(this->config, *source);
}

void ltn::c::Ltnc::yield(std::ostream & out) {
	this->backend->yield(out);
}
