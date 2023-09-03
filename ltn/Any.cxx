#include "Any.hxx"
#include "stdxx/io.hxx"

namespace ltn {

	Any::Any()              
		: data{NullT{}} {}

	Any::Any(bool v)                  
		: data{v} {}

	Any::Any(char v)                  
		: data{v} {}
	
	Any::Any(std::int64_t v)          
		: data{v} {}
	
	Any::Any(stx::float64_t v)        
		: data{v} {}

	Any::Any(const std::string v)
		: data{v} {}
	
	Any::Any(const std::vector<Any> & v)
		: data{v} {}



	bool Any::is_null() const {
		return this->is<NullT>();
	}

	bool Any::is_bool() const {
		return this->is<bool>();
	}

	bool Any::is_char() const {
		return this->is<char>();
	}

	bool Any::is_int() const {
		return this->is<std::int64_t>();
	}

	bool Any::is_float() const {
		return this->is<stx::float64_t>();
	}

	bool Any::is_string() const {
		return this->is<std::string>();
	}

	bool Any::is_array() const {
		return this->is<std::vector<Any>>();
	}



	const bool & Any::as_bool() const {
		return this->get<bool>();
	}

	const char & Any::as_char() const {
		return this->get<char>();
	}

	const std::int64_t & Any::as_int() const {
		return this->get<std::int64_t>();
	}

	const stx::float64_t & Any::as_float() const {
		return this->get<stx::float64_t>();
	}

	const std::string & Any::as_string() const {
		return this->get<std::string>();
	}

	const std::vector<Any> & Any::as_array() const {
		return this->get<std::vector<Any>>();
	}


	namespace {
		void print(std::ostream & stream, const Any::NullT &) {
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



		void print(std::ostream & stream, const std::vector<Any> & value) {
			stream << stx::whole(value);
		}
	}



	std::ostream & operator<<(std::ostream & stream, const Any & any) {
		std::visit([&] (auto & value) { print(stream, value); }, any.data);
		return stream;
	}
}
