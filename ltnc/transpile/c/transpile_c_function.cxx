#include "transpile_c.hxx"
#include <sstream>

namespace ltn::c::trans::c {
	namespace {
		Node transpile_c_function(const sst::Function & fx) {
			return Function {
				.name = fx.name,
				.arity = fx.parameters.size(),
				.body = Block {
					.elements {
						Line{
							.code = "// Test"
						}
					}
				}
			};
		}



		Node transpile_c_build_in_function(const sst::BuildIn & fx) {
			return Function {
				.name = fx.name,
				.arity = fx.parameters.size(),
				.body = Line {
					.code = "// Test"
				}
			};
		}
	}



	Node transpile_c_functional(const sst::Functional & functional) {
		if(auto fx = as<const sst::Function>(functional)) {
			return transpile_c_function(*fx);
		}
		if(auto fx = as<const sst::BuildIn>(functional)) {
			return transpile_c_build_in_function(*fx);
		}
		throw std::runtime_error{"Unknown functional declaration"};
	}
}