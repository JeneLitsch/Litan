#pragma once
#include <string>
#include <vector>
#include <ostream>
#include <memory>

namespace ltn::c::trans::c {
	class Node {
		struct Concept{
			virtual void print(std::ostream & stream, std::uint64_t indent) const = 0;
			virtual std::unique_ptr<Concept> clone() const = 0;
			virtual ~Concept() = default;
		};
		
		template <typename T>
		struct Model : Concept {
			Model(T t) : t {std::move(t)} {}
			virtual void print(std::ostream & stream, std::uint64_t indent) const override {
				return print_c(stream, t, indent);
			}
			virtual std::unique_ptr<Concept> clone() const override {
				return std::make_unique<Model<T>>(t);
			}
			T t;
		};
	public:
		template <typename T>
		Node(T t) : object{std::make_unique<Model<T>>(std::move(t))}{}
		
		Node(const Node & other) {
			this->object = other.object->clone();
		}

		Node(Node && other) {
			this->object = std::move(other.object);
		}

		void print(std::ostream & stream, std::uint64_t indent) const {
			return object->print(stream, indent);
		}
	private:
		std::unique_ptr<Concept> object;
	};
}