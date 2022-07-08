#pragma once
#include <vector>
#include <string>
#include <set>
#include <map>
#include "stdxx/reference.hxx"

namespace stx::args {
	class scanner {
	public:
		scanner(int argc, char const *argv[]) : argc{argc}, argv{argv} {}
		std::optional<std::string_view> peek() const {
			if(current < argc) {
				return argv[current];
			}
			else {
				return std::nullopt;
			}
		}

		void next() {
			this->current++;
		}

		std::optional<std::string_view> fetch() {
			const auto tmp = peek();
			next();
			return tmp; 
		}
	private:
		int current = 1;
		int argc;
		char const ** argv;
	};



	class arg {
	public:
		virtual void operator()(scanner & scanner) = 0;
	};



	class mandatory : public arg {
	public:
		virtual void operator()(scanner & scanner) {
			this->str = scanner.fetch();
		}
		auto get() const {
			if(!str) throw std::runtime_error {
				"Missing mandatory argument"
			};
			return *str;
		}
	private:
		std::optional<std::string_view> str;
	};



	class optional_list : public arg {
	public:
		optional_list(const std::string & start) : start {start} {}
		virtual void operator()(scanner & scanner) override {
			if(scanner.peek() != start) return;
			scanner.next();

			for(auto elem = scanner.peek(); elem && (*elem)[0] != '-'; elem = scanner.peek()) {
				scanner.next();
				list.push_back(std::string{*elem});
			}
		}

		const std::vector<std::string> get() const {
			return list;
		}
	private:
		std::string start;
		std::vector<std::string> list;
	};



	class options : public arg {
	public:
		options(const auto & flags) {
			for(const auto & flag : flags) {
				this->flags.insert({flag, false});
			}
		}

		virtual void operator()(scanner & scanner) override {
			while(auto x = scanner.peek()) {
				if(this->flags.contains(std::string{*x})) {
					scanner.next();
					this->flags[std::string{*x}] = true;
				}
				else break;
			}
		}

		bool is_set(const std::string & flag) {
			return this->flags.contains(flag) && this->flags.at(flag);
		}
	private:
		std::map<std::string, bool> flags;
	};



	class args {
	public:
		args(auto & ... x) : arg_refs { x... } {}
		void operator()(int argc, char const *argv[]) {
			scanner scanner(argc, argv);
			for(auto & arg : arg_refs) {
				(*arg)(scanner);
			}
		}
	private:
		std::vector<stx::reference<arg>> arg_refs;
	};
}