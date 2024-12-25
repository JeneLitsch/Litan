#pragma once
#include "litan_vm/VMCore.hxx"

namespace ltn::vm {
	std::string stringify(const Value & value, VMCore & core);
	void stringify(const Value & value, VMCore & core, std::ostream & oss, bool nested);


	void print_element(const Value value, VMCore & core, std::ostream & oss);
	void print_element(const std::pair<Value, Value> pair, VMCore & core, std::ostream & oss);

	template<typename Iterator>
		void print_all(
			Iterator begin,
			Iterator end,
			std::ostream & out,
			VMCore & core,
			char open = '[',
			char close = ']') {
			
			out << open;
			for(auto it = begin; it != end; ++it) {
				if (it != begin) out << ", ";
				 print_element(*it, core, out);
			}
			out << close;
		}
}