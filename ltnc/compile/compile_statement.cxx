#include "compile.hxx"
namespace ltn::c {
	InstructionBuffer compile_stmt(const sst::NoOp &) {
		return {};
	}



	InstructionBuffer compile_statement(const sst::Statement & stmt) {
		auto fx = [] (const auto & s) { return compile_stmt(s); };
		using Callable = std::decay_t<decltype(fx)>;
		using Ret = std::invoke_result_t<Callable, sst::Block>;
		using Base = FunctionVisitor<sst::StmtVisitor, Callable, Ret>;

		struct Visitor : public Base {
			Visitor(Callable fx) : Base {fx} {} 
			
			virtual void visit(const sst::Block & x) const override { this->run(x); }
			virtual void visit(const sst::IfElse & x) const override { this->run(x); }
			virtual void visit(const sst::While & x) const override { this->run(x); }
			virtual void visit(const sst::InfiniteLoop & x) const override { this->run(x); }
			virtual void visit(const sst::ForEach & x) const override { this->run(x); }
			virtual void visit(const sst::Assign & x) const override { this->run(x); }
			virtual void visit(const sst::Return & x) const override { this->run(x); }
			virtual void visit(const sst::Throw & x) const override { this->run(x); }
			virtual void visit(const sst::Switch & x) const override { this->run(x); }
			virtual void visit(const sst::NoOp & x) const override { this->run(x); }
		};

		return Visitor{fx}(stmt);
	}
}