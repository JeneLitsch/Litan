#include "Namespace.hxx"
#include <iostream>
namespace ltn::c::ast {

	namespace {
		template<class T>
		std::vector<T> operator+(
			const std::vector<T> & l,
			const std::vector<T> & r) {
			std::vector<T> vec;
			vec.reserve(l.size() + r.size());
			vec.insert(std::end(vec), l.begin(), l.end());
			vec.insert(std::end(vec), r.begin(), r.end());
			return vec;
		}
	}


	bool is_absolute(const Namespace & ns) {
		return (!ns.empty()) && (ns[0] == "::");
	}
}