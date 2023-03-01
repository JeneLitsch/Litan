#pragma once

namespace ltn {
	template<typename T>
	struct Visit {
		virtual void visit(const T &) const = 0;
	};

	template<typename ...Ts>
	struct Visitor : Visit<Ts>...{
		using Visit<Ts>::visit...;
	};



	template<typename Interface, typename Callable, typename Ret>
	struct FunctionVisitor : Interface {
	public:
		FunctionVisitor(Callable fx) : fx {fx} {}

		Ret operator()(const auto & expr) const {
			expr.accept(*this);
			return std::move(ret);
		}

	protected:
		void run(const auto & x) const {
			ret = fx(x);
		}

	private:
		Callable fx;
		mutable Ret ret;
	};
}