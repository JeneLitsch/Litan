#pragma once
#include <memory>

namespace ltn::c::ast {
	struct ExprBase;

	class Expression {
		struct Concept {
			virtual ~Concept() = default;
		};

		template<typename T> 
		struct Model : Concept {
			Model(T && t) : t {std::move(t)} {}
			T t;
		};
	public:
		template<typename T>
		Expression(std::unique_ptr<T> node)
			: ptr {new Model<T> {std::move(*node)}} {}

		template<typename T>
		Expression(T node)
			: ptr {new Model<T> {std::move(node)}} {}

		Expression() : ptr {nullptr} {}

		Expression(Expression &&) = default;
		Expression & operator=(Expression &&) = default;
		
		operator bool() const {
			return static_cast<bool>(ptr);
		}
		
		template<class To>
		const To * as() const {
			auto model = dynamic_cast<const Model<To> *>(ptr.get());
			return model ? &model->t : nullptr;
		}

	private:
		std::unique_ptr<Concept> ptr;
	};
}