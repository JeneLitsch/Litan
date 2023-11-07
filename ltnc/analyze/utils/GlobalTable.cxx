#include "GlobalTable.hxx"


namespace ltn::c {
	CompilerError GlobalErrors::redef(const sst::Global & def) {
		std::stringstream msg;
		msg << "Global variable ";
		msg << def.namespaze.to_string();
		msg << def.name;
		msg	<< " already exists";
		return CompilerError{ msg.str(), {} };
	}


	
	CompilerError GlobalErrors::decl(const std::string & inside) {
		return CompilerError {
			"Cannot declare globals inside " + inside
		};
	}
	


	CompilerError GlobalErrors::use(const std::string & inside) {
		return CompilerError {
			"Cannot use globals inside " + inside
		};
	}
}