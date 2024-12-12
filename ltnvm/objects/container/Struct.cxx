#include "Struct.hxx"
#include "ltnvm/Exception.hxx"
#include "ltnvm/utils/special_member.hxx"

namespace ltn::vm {
	void Struct::stringify(VMCore & core, std::ostream & oss, bool nested) {
		auto fx = find_special_member<MemberCode::OPERATOR_STR>(*this);
		if(fx) {
			Value value = value::strukt(this);
			auto result = run_special_member(core, *fx, value);
			if(is_string(result)) {
				oss << value::as<String>(result)->get_underlying();
			} 
			else {
				throw except::invalid_argument("Special member {str} must return string");
			}
		}
		else {
			oss << "<struct>";
		}
	}

}