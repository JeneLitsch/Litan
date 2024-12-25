#include "DefinitionTable.hxx"


namespace ltn::c {
	CompilerError DefinitionErrors::redef(const sst::decl::Definition & def) {
		std::stringstream msg;
		msg << "Definition ";
		msg << def.namespaze.to_string();
		msg << def.name;
		msg	<< " already exists";
		return CompilerError{ msg.str(), {} };
	}

	

	CompilerError DefinitionErrors::decl(const std::string & inside) {
		return CompilerError {
			"Cannot declare definition inside a " + inside
		};
	}
	


	CompilerError DefinitionErrors::use(const std::string & inside) {
		return CompilerError {
			"Cannot use definition inside a " + inside
		};
	}
}