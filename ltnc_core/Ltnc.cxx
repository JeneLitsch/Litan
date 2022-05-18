#include "Ltnc.hxx"
#include <vector>
#include "lex/Lexer.hxx"
#include "parse/parse.hxx"
#include "unfold/unfold.hxx"
#include "optimize/optimize.hxx"
#include <string_view>
#include "stdlib/algorithm.hxx"
#include "stdlib/bits.hxx"
#include "stdlib/cast.hxx"
#include "stdlib/chrono.hxx"
#include "stdlib/container.hxx"
#include "stdlib/debug.hxx"
#include "stdlib/functional.hxx"
#include "stdlib/io.hxx"
#include "stdlib/math.hxx"
#include "stdlib/random.hxx"
#include "stdlib/range.hxx"
#include "stdlib/type.hxx"

using namespace std::string_view_literals;

namespace ltn::c {
	Ltnc::Ltnc(std::unique_ptr<Backend> backend) : backend(std::move(backend)) {
		auto compile_std = [this](auto code) {
			std::istringstream iss{code};
			this->compile(iss, "");
		};

		compile_std(std_algorithm);
		compile_std(std_bits);
		compile_std(std_cast);
		compile_std(std_chrono);
		compile_std(std_container);
		compile_std(std_debug);
		compile_std(std_functional);
		compile_std(std_io);
		compile_std(std_math);
		compile_std(std_random);
		compile_std(std_range);
		compile_std(std_type);
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


