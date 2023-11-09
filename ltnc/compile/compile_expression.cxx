#include "compile.hxx"
#include "build_in.hxx"
#include "ltnc/sst/expr/BuildIn.hxx"

namespace ltn::c {
	InstructionBuffer compile_expr(const sst::expr::BuildIn & expr) {
		return { resolve_build_in(expr.key) };
	}


	// compiles any expr
	InstructionBuffer compile_expression(const sst::expr::Expression & expr) {
		auto fx = [&](const auto & e) { return compile_expr(e); };
		using Callable = std::decay_t<decltype(fx)>;
		using Ret = std::invoke_result_t<Callable, sst::expr::Binary>;
		using Base = FunctionVisitor<sst::expr::ExprVisitor, Callable, Ret>;

		struct Visitor : public Base {
			Visitor(Callable fx) : Base {fx} {} 

			virtual void visit(const sst::expr::Binary & x) const override { this->run(x); };
			virtual void visit(const sst::expr::Unary & x) const override { this->run(x); };
			virtual void visit(const sst::expr::Integer & x) const override { this->run(x); };
			virtual void visit(const sst::expr::Float & x) const override { this->run(x); };
			virtual void visit(const sst::expr::Bool & x) const override { this->run(x); };
			virtual void visit(const sst::expr::Char & x) const override { this->run(x); };
			virtual void visit(const sst::expr::Null & x) const override { this->run(x); };
			virtual void visit(const sst::expr::String & x) const override { this->run(x); };
			virtual void visit(const sst::expr::Array & x) const override { this->run(x); };
			virtual void visit(const sst::expr::Tuple & x) const override { this->run(x); };
			virtual void visit(const sst::expr::Call & x) const override { this->run(x); };
			virtual void visit(const sst::expr::Invoke & x) const override { this->run(x); };
			virtual void visit(const sst::expr::InvokeMember & x) const override { this->run(x); };
			virtual void visit(const sst::expr::Var & x) const override { this->run(x); };
			virtual void visit(const sst::expr::Index & x) const override { this->run(x); };
			virtual void visit(const sst::expr::FxPointer & x) const override { this->run(x); };
			virtual void visit(const sst::expr::Member & x) const override { this->run(x); };
			virtual void visit(const sst::expr::GlobalVar & x) const override { this->run(x); };
			virtual void visit(const sst::expr::Iife & x) const override { this->run(x); };
			virtual void visit(const sst::expr::Ternary & x) const override { this->run(x); };
			virtual void visit(const sst::expr::Choose & x) const override { this->run(x); };
			virtual void visit(const sst::expr::Reflect & x) const override { this->run(x); };
			virtual void visit(const sst::expr::Struct & x) const override { this->run(x); };
			virtual void visit(const sst::expr::Map & x) const override { this->run(x); };
			virtual void visit(const sst::expr::Type & x) const override { this->run(x); };
			virtual void visit(const sst::expr::BuildIn & x) const override { this->run(x); };
		};

		return Visitor{fx}(expr);
	}
}