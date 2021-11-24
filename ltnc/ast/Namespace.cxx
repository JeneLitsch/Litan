#include "Namespace.hxx"
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

	bool match(
		const Namespace & full,
		const Namespace & from,
		const Namespace & to) {
			
		if((from + to) == full) {
			return true;
		}
		else if(from.empty()) {
			return false;
		}
		else {
			return match(
				full,
				{from.begin(), from.end()-1},
				to);
		}
	}
}