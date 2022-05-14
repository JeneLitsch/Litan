#include "Ltnc.hxx"
#include <vector>
#include "lex/Lexer.hxx"
#include "parse/parse.hxx"
#include "unfold/unfold.hxx"
#include "optimize/optimize.hxx"
#include <string_view>

using namespace std::string_view_literals;

namespace ltn::c {
	const std::span<const std::string_view> Ltnc::stdlib() const {
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
		};
		return std_files;
	}



	void Ltnc::compile(std::istream & in, const std::string & sourcename) {
		lex::Lexer lexer{in, sourcename, reporter};
		try {
			auto source = parse::source(lexer);
			auto t_unit = unfold::source(std::move(source));
			for(auto && fx : t_unit->functions) {
				this->program.functions.push_back(std::move(fx));
			}

			for(auto && e : t_unit->globals) {
				this->program.globals.push_back(std::move(e));
			}
		}
		catch(const CompilerError & error) {
			this->reporter.push(error);
		}
	}



	void Ltnc::optimize() {
		optimize::optimize(this->program);
	}



	void Ltnc::yield(std::ostream & out) {
		std::ostringstream ss;
		try {
			this->backend->compile(ss, this->config, this->program, reporter);
		}
		catch(const CompilerError & error) {
			this->reporter.push(error);
		}
		this->reporter.may_throw();
		out << ss.str();
	}
}


