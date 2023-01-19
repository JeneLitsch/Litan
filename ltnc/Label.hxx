#pragma once
#include <string>
#include "Namespace.hxx"
#include "type/Type.hxx"

namespace ltn::c {
	class Label {
	public:
		enum class UseCase { INTERNAL, EXTERNAL };
		Label(UseCase use_case, const std::string & name)
			: use_case{use_case}, name{name} {}
		const std::string & get_name() const;
		std::string mangle() const;
		std::string to_string() const;
	private:
		UseCase use_case;
		std::string name;
	};
}