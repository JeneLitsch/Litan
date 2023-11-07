#include "compile.hxx"
#include "build_in.hxx"

namespace ltn::c {
	InstructionBuffer compile_expr(const sst::BuildIn & expr) {
		return { resolve_build_in(expr.key) };
	}


	// compiles any expr
	InstructionBuffer compile_expression(const sst::Expression & expr) {
		auto fx = [&](const auto & e) { return compile_expr(e); };
		using Callable = std::decay_t<decltype(fx)>;
		using Ret = std::invoke_result_t<Callable, sst::Binary>;
		using Base = FunctionVisitor<sst::ExprVisitor, Callable, Ret>;

		struct Visitor : public Base {
			Visitor(Callable fx) : Base {fx} {} 

			virtual void visit(const sst::Binary & x) const override { this->run(x); };
			virtual void visit(const sst::Unary & x) const override { this->run(x); };
			virtual void visit(const sst::Integer & x) const override { this->run(x); };
			virtual void visit(const sst::Float & x) const override { this->run(x); };
			virtual void visit(const sst::Bool & x) const override { this->run(x); };
			virtual void visit(const sst::Char & x) const override { this->run(x); };
			virtual void visit(const sst::Null & x) const override { this->run(x); };
			virtual void visit(const sst::String & x) const override { this->run(x); };
			virtual void visit(const sst::Array & x) const override { this->run(x); };
			virtual void visit(const sst::Tuple & x) const override { this->run(x); };
			virtual void visit(const sst::Call & x) const override { this->run(x); };
			virtual void visit(const sst::Invoke & x) const override { this->run(x); };
			virtual void visit(const sst::InvokeMember & x) const override { this->run(x); };
			virtual void visit(const sst::Var & x) const override { this->run(x); };
			virtual void visit(const sst::Index & x) const override { this->run(x); };
			virtual void visit(const sst::FxPointer & x) const override { this->run(x); };
			virtual void visit(const sst::Member & x) const override { this->run(x); };
			virtual void visit(const sst::GlobalVar & x) const override { this->run(x); };
			virtual void visit(const sst::Iife & x) const override { this->run(x); };
			virtual void visit(const sst::Ternary & x) const override { this->run(x); };
			virtual void visit(const sst::Choose & x) const override { this->run(x); };
			virtual void visit(const sst::Reflect & x) const override { this->run(x); };
			virtual void visit(const sst::Struct & x) const override { this->run(x); };
			virtual void visit(const sst::Map & x) const override { this->run(x); };
			virtual void visit(const sst::Type & x) const override { this->run(x); };
			virtual void visit(const sst::BuildIn & x) const override { this->run(x); };
		};

		return Visitor{fx}(expr);
	}
}