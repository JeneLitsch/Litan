#include "Type.hxx"
#include "to_string.hxx"
#include <tuple>

namespace ltn::c::type {
    namespace {
        std::strong_ordering compare_contained(const auto & l, const auto & r) {
            if(!l && !r) return std::strong_ordering::equal;
            if(l && r) return **l <=> **r;
			if(l) return std::strong_ordering::greater;
			if(r) return std::strong_ordering::less;
			throw std::runtime_error {"Type compare error"};
        }



		std::strong_ordering compare_parameters(const auto & l, const auto & r) {
			if(l.size() < r.size()) return std::strong_ordering::less;
			if(l.size() > r.size()) return std::strong_ordering::greater;
			for(std::size_t i = 0; i < l.size(); ++i) {
				if(*l[i] < *r[i]) return std::strong_ordering::less;
				if(*l[i] > *r[i]) return std::strong_ordering::greater;
			}
			return std::strong_ordering::equal;
		}
    }



	std::strong_ordering operator<=>(const Any &, const Any &) {
		return std::strong_ordering::equal;
	}



	std::strong_ordering operator<=>(const Other & l, const Other & r) {
		return l.type_name <=> r.type_name;
	}



	std::strong_ordering operator<=>(const Optional & l, const Optional & r) {
		return *l.contains <=> *r.contains;
	}



	std::strong_ordering operator<=>(const Error &, const Error &) {
		return std::strong_ordering::equal;
	}



	std::strong_ordering operator<=>(const Null &, const Null &) {
		return std::strong_ordering::equal;
	}



	std::strong_ordering operator<=>(const Bool &, const Bool &) {
		return std::strong_ordering::equal;
	}



	std::strong_ordering operator<=>(const Char &, const Char &) {
		return std::strong_ordering::equal;
	}



	std::strong_ordering operator<=>(const Int &, const Int &) {
		return std::strong_ordering::equal;
	}



	std::strong_ordering operator<=>(const Float &, const Float &) {
		return std::strong_ordering::equal;
	}
	


	std::strong_ordering operator<=>(const String &, const String &) {
		return std::strong_ordering::equal;
	}



	std::strong_ordering operator<=>(const Array & l, const Array & r) {
		return compare_contained(l.contains, r.contains);
	}



	std::strong_ordering operator<=>(const Tuple & l, const Tuple & r) {
		return compare_parameters(l.contained, r.contained);
	}



	std::strong_ordering operator<=>(const FxPtr & l, const FxPtr & r) {
		const auto order = compare_contained(l.return_type, r.return_type);
		if(order == 0) return compare_parameters(l.parameter_types, r.parameter_types);
		return order;
	}



	std::strong_ordering operator<=>(const Type & l, const Type & r) {
		return (*l) <=> (*r);
	}



	std::ostream & operator<<(std::ostream & out, const Type & type) {
		out << to_string(type);
		return out;
	}



	std::strong_ordering operator<=>(const Queue & l, const Queue & r) {
		return compare_contained(l.contains, r.contains);
	}



	std::strong_ordering operator<=>(const Stack & l, const Stack & r) {
		return compare_contained(l.contains, r.contains);
	}



	std::strong_ordering operator<=>(const Map & l, const Map & r) {
		const auto order = compare_contained(l.key, r.key);
		if(order == 0) return compare_contained(l.val, r.val);
		return order;
	}



	std::strong_ordering operator<=>(const Istream &, const Istream &) {
		return std::strong_ordering::equal;
	}



	std::strong_ordering operator<=>(const Ostream &, const Ostream &) {
		return std::strong_ordering::equal;
	}
}