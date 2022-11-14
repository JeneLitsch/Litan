#include "Type.hxx"

namespace ltn::c::type {
    namespace {
        bool compare_contained(const auto & l, const auto & r) {
            if(!l && !r) return true;
            if(l && r) return **l == **r;
            return false;
        }


		bool compare_parameters(const auto & l, const auto & r) {
			if(l.size() != r.size()) return false;
			for(std::size_t i = 0; i < l.size(); ++i) {
				if(l[i] != r[i]) return false;
			}
			return true;
		}
    }

	bool operator==(const Any &, const Any &) {
		return true;
	}

	bool operator==(const Optional & l, const Optional & r) {
		return *l.contains == *r.contains;
	}

	bool operator==(const Error &, const Error &) {
		return true;
	}

	bool operator==(const Null &, const Null &) {
		return true;
	}

	bool operator==(const Bool &, const Bool &) {
		return true;
	}

	bool operator==(const Char &, const Char &) {
		return true;
	}

	bool operator==(const Int &, const Int &) {
		return true;
	}

	bool operator==(const Float &, const Float &) {
		return true;
	}
	
	bool operator==(const String &, const String &) {
		return true;
	}

	bool operator==(const Array & l, const Array & r) {
		return compare_contained(l.contains, r.contains);
	}


	bool operator==(const FxPtr & l, const FxPtr & r) {
		return compare_contained(l.return_type, r.return_type) 
			&& compare_parameters(l.parameter_types, r.parameter_types);
	}

	bool operator==(const Type & l, const Type & r) {
		return l.actual_type == r.actual_type;
	}

	std::ostream & operator<<(std::ostream & out, const Type & type) {
		out << to_string(type);
		return out;
	}

	bool operator==(const Queue & l, const Queue & r) {
		return compare_contained(l.contains, r.contains);
	}

	bool operator==(const Stack & l, const Stack & r) {
		return compare_contained(l.contains, r.contains);
	}

	bool operator==(const Map & l, const Map & r) {
		return compare_contained(l.key, r.key) && compare_contained(l.val, r.val);
	}
}