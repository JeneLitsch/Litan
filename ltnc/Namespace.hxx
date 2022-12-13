#pragma once
#include <vector>
#include <string>
namespace ltn::c {
	class Namespace {
	public:
		Namespace(const std::vector<std::string> & path) : path(path) {}  
		Namespace() = default;  

		void push_back(const std::string & str);
		void pop_back();
		std::size_t size() const;
		bool empty() const;
		const std::string & operator[](std::size_t i) const;
		std::string & operator[](std::size_t i);
		bool is_absolute() const;
		void set_absolute();
		std::string to_string() const;


		friend bool operator==(
			const Namespace & l,
			const Namespace & r);



		friend Namespace operator+(
			const Namespace & l,
			const Namespace & r);


		auto begin()        { return this->path.begin(); }
		auto begin()  const { return this->path.begin(); }
		auto cbegin() const { return this->path.cbegin(); }
		auto end()          { return this->path.end(); }
		auto end()    const { return this->path.end(); }
		auto cend()   const { return this->path.cend(); }

	private:
		std::vector<std::string> path;
		bool absolute = false;
	};



	bool operator==(
		const Namespace & l,
		const Namespace & r);



	Namespace operator+(
		const Namespace & l,
		const Namespace & r);
}