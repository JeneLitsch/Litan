#include "Ltnc.hxx"
#include <vector>
#include "lex/Lexer.hxx"
#include "parse/parse.hxx"
#include <string_view>
using namespace std::string_view_literals;

const std::span<const std::string_view> ltn::c::Ltnc::stdlib() const {
	constexpr static std::array std_files {
		"algorithm.ltn"sv,
		"cast.ltn"sv,
		"chrono.ltn"sv,
		"container.ltn"sv,
		"debug.ltn"sv,
		"functional.ltn"sv,
		"io.ltn"sv,
		"math.ltn"sv,
		"random.ltn"sv,
		"range.ltn"sv,
		"type.ltn"sv,
		"utils.ltn"sv,
	};
	return std_files;
}

void ltn::c::Ltnc::compile(std::istream & in, const std::string & sourcename) {
	lex::Lexer lexer{in, sourcename, reporter};
	try {
		auto source = parse::source(lexer);
		for(auto && fx : source) {
			this->program.functions.push_back(std::move(fx));
		}
	}
	catch(const CompilerError & error) {
		this->reporter.push(error);
	}
}

void ltn::c::Ltnc::yield(std::ostream & out) {
	std::ostringstream ss;
	try {
		this->backend->compile(ss, this->config, this->program.functions, reporter);
	}
	catch(const CompilerError & error) {
		this->reporter.push(error);
	}
	this->reporter.may_throw();
	out << ss.str();
}
