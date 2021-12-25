#include "Ltnc.hxx"
#include <vector>
#include "lex/Lexer.hxx"
#include "parse/parsing.hxx"
#include <string_view>
using namespace std::string_view_literals;

const std::span<const std::string_view> ltn::c::Ltnc::stdLib() const {
	constexpr static std::array stdFiles {
		"io.ltn"sv,
		"chrono.ltn"sv,
		"error.ltn"sv,
		"debug.ltn"sv,
		"functional.ltn"sv,
		"math.ltn"sv,
		"type.ltn"sv,
		"utils.ltn"sv,
	};
	return stdFiles;
}

void ltn::c::Ltnc::compile(std::istream & in, const std::string &) {
	this->line = 0;
	lex::Lexer lexer{in, this->line};
	auto source = parse::source(lexer);
	for(auto && fx : source) {
		this->program.functions.push_back(std::move(fx));
	}
}

void ltn::c::Ltnc::yield(std::ostream & out) {
	this->backend->compile(out, this->config, this->program.functions);
}
