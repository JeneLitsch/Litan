#include "transpile_c.hxx"
#include "syntax.hxx"

namespace ltn::c::trans::c {
	namespace {
		Node generate_main() {
			return Line {
				.code = "int main() { return 0; }"
			};
		}



		Node generate_impl(const sst::Program & program) {
			Bundle file;
			for(const auto & fx : program.functions) {
				file.elements.push_back(transpile_c_functional(*fx));
			}
			return file;
		}



		Node generate_utils() {
			std::ostringstream oss;
			Bundle file;
			std::vector<Node> nodes;
			file.elements.push_back(Include{
				.header = "<stdint.h>"
			});
			file.elements.push_back(Struct {
				.name = "Value",
				.members {
					Member {
						.type = "uint8_t",
						.name = "type",
					}
				}
			});

			return file;
		}
	}



	std::vector<OutputFile> transpile_c(const sst::Program & program) {
		std::vector<OutputFile> files;
		std::ostringstream oss;
		generate_utils().print(oss, 0);
		generate_main().print(oss, 0);
		generate_impl(program).print(oss, 0);
		files.push_back(OutputFile{
			.name = "main.c",
			.content = oss.str(),
		});
		return files;
	}
}