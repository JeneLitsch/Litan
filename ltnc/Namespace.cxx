#include "ltnc/Namespace.hxx"
#include <iostream>
#include <sstream>
namespace ltn::c {
	bool Namespace::is_absolute() const {
		return this->absolute;
	}



	void Namespace::push_back(const std::string & str) {
		this->path.push_back(str);
	}



	void Namespace::pop_back() {
		this->path.pop_back();
	}



	std::size_t Namespace::size() const {
		return this->path.size();
	}



	bool Namespace::empty() const {
		return this->size() == 0 && !this->is_absolute();
	}



	const std::string & Namespace::operator[](std::size_t i) const {
		return this->path[i];
	}



	std::string & Namespace::operator[](std::size_t i) {
		return this->path[i];
	}



	void Namespace::set_absolute()  {
		this->absolute = true;
	}




	std::string Namespace::to_string() const {
		std::ostringstream oss;
		for(const auto & step : this->path) {
			oss << step << "::";
		}
		return oss.str();
	}



	bool operator==(
		const Namespace & l,
		const Namespace & r) {
		return l.path == r.path;
	} 


	Namespace operator+(
		const Namespace & l,
		const Namespace & r) {
		Namespace n;
		n.path.reserve(l.path.size() + r.path.size());
		n.path.insert(std::end(n.path), l.path.begin(), l.path.end());
		n.path.insert(std::end(n.path), r.path.begin(), r.path.end());
		return n;
	}
}