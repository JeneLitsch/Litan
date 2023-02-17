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
}