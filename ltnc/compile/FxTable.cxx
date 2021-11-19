#include "FxTable.hxx"
#include "ltnc/CompilerError.hxx"
#include <sstream>
#include "ltn/printing.hxx"
namespace ltn::c::compile {
	
	CompilerError multipleDefinitions(const FxSignature & fx) {
		std::stringstream msg;
		msg << "Function ";
		msg << fx.name << "(";
		msg << fx.parameters;
		msg << ") already exists";
		return CompilerError{ msg.str(), 0 };
	}

	const FxSignature * FxTable::find(
		const std::string_view name,
		const std::size_t parameters) {
		for(const auto & fx : this->functions) {
			if((fx.name == name) && fx.parameters == parameters) {
				return &fx;
			}
		}
		return nullptr;
	}

	void FxTable::insert(const FxSignature & fx) {
		if(this->find(fx.name, fx.parameters)) {
			throw multipleDefinitions(fx);
		}
		this->functions.push_back(fx);
	}
}