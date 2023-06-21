#include "transpile_c.hxx"

namespace ltn::c::trans::cxx {
	namespace {
		void transpile_c_bind(const sst::NewVarBinding & binding, std::ostream & out, Indent) {
			out << "var_" << binding.address << " = "; 
		}
		


		void transpile_c_bind(const sst::GroupBinding & binding, std::ostream &, Indent) {
		}



		void transpile_c_bind(const sst::NoBinding &, std::ostream &, Indent) {
		}



		void transpile_c_bind(const sst::GlobalBinding & binding, std::ostream &, Indent) {
		}



		void transpile_c_bind(const sst::MemberBinding & binding, std::ostream &, Indent) {
		}
		
		
		
		void transpile_c_bind(const sst::LocalBinding & binding, std::ostream & out, Indent) {
			out << "var_" << binding.address << " = "; 
		}
		
		
		
		void transpile_c_bind(const sst::IndexBinding & binding, std::ostream &, Indent) {
		}
	}



	void transpile_c_binding(const sst::Binding & binding, std::ostream & out, Indent indent) {
		sst::visit_binding(binding, [&] (const auto & b) {
			transpile_c_bind(b, out, indent);
			return 0;
		});
	}
}