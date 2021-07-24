#pragma once
#include <vector>
#include <string>
#include <ostream>
namespace ltnc {
	class Namespace {
		friend bool operator==(const Namespace & nsL, const Namespace & nsR);
	public:
		Namespace();
		Namespace(const std::vector<std::string> & path);
	
		void push(const std::string & ns);
		void pop();

		std::string str() const;
	private:
		std::vector<std::string> path; 
	};
	std::ostream & operator<<(std::ostream & stream, const Namespace & ns);
	bool operator==(const Namespace & nsL, const Namespace & nsR);
}