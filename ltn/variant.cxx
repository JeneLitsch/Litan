#include "variant.hxx"
#include "stdxx/io.hxx"

namespace ltn {

	Variant::Variant()              
		: data{NullT{}} {}

	Variant::Variant(bool v)                  
		: data{v} {}

	Variant::Variant(char v)                  
		: data{v} {}
	
	Variant::Variant(std::int64_t v)          
		: data{v} {}
	
	Variant::Variant(stx::float64_t v)        
		: data{v} {}

	Variant::Variant(const std::string v)
		: data{v} {}
	
	Variant::Variant(const std::vector<Variant> & v)
		: data{v} {}



	bool Variant::is_null() const {
		return this->is<NullT>();
	}

	bool Variant::is_bool() const {
		return this->is<bool>();
	}

	bool Variant::is_char() const {
		return this->is<char>();
	}

	bool Variant::is_int() const {
		return this->is<std::int64_t>();
	}

	bool Variant::is_float() const {
		return this->is<stx::float64_t>();
	}

	bool Variant::is_string() const {
		return this->is<std::string>();
	}

	bool Variant::is_array() const {
		return this->is<std::vector<Variant>>();
	}



	const bool & Variant::as_bool() const {
		return this->get<bool>();
	}

	const char & Variant::as_char() const {
		return this->get<char>();
	}

	const std::int64_t & Variant::as_int() const {
		return this->get<std::int64_t>();
	}

	const stx::float64_t & Variant::as_float() const {
		return this->get<stx::float64_t>();
	}

	const std::string & Variant::as_string() const {
		return this->get<std::string>();
	}

	const std::vector<Variant> & Variant::as_array() const {
		return this->get<std::vector<Variant>>();
	}


	namespace {
		void print(std::ostream & stream, const Variant::NullT &) {
			stream << "null";
		}



		void print(std::ostream & stream, const bool & value) {
			stream << std::boolalpha << value << std::noboolalpha;
		}



		void print(std::ostream & stream, const char & value) {
			stream << value;

		}



		void print(std::ostream & stream, const std::int64_t & value) {
			stream << value;

		}



		void print(std::ostream & stream, const stx::float64_t & value) {
			stream << value;
		}



		void print(std::ostream & stream, const std::string & value) {
			stream << value;
		}



		void print(std::ostream & stream, const std::vector<Variant> & value) {
			stream << stx::whole(value);
		}
	}



	std::ostream & operator<<(std::ostream & stream, const Variant & variant) {
		std::visit([&] (auto & value) { print(stream, value); }, variant.data);
		return stream;
	}
}
