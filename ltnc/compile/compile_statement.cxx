#include "compile.hxx"
namespace ltn::c {
	InstructionBuffer compile_stmt(const sst::stmt::NoOp &) {
		return {};
	}



	InstructionBuffer compile_statement(const sst::stmt::Statement & stmt) {
		auto fx = [] (const auto & s) { return compile_stmt(s); };
		using Callable = std::decay_t<decltype(fx)>;
		using Ret = std::invoke_result_t<Callable, sst::stmt::Block>;
		using Base = FunctionVisitor<sst::stmt::StmtVisitor, Callable, Ret>;

		struct Visitor : public Base {
			Visitor(Callable fx) : Base {fx} {} 
			
			virtual void visit(const sst::stmt::Block & x) const override { this->run(x); }
			virtual void visit(const sst::stmt::IfElse & x) const override { this->run(x); }
			virtual void visit(const sst::stmt::While & x) const override { this->run(x); }
			virtual void visit(const sst::stmt::InfiniteLoop & x) const override { this->run(x); }
			virtual void visit(const sst::stmt::ForEach & x) const override { this->run(x); }
			virtual void visit(const sst::stmt::Assign & x) const override { this->run(x); }
			virtual void visit(const sst::stmt::Return & x) const override { this->run(x); }
			virtual void visit(const sst::stmt::Throw & x) const override { this->run(x); }
			virtual void visit(const sst::stmt::Switch & x) const override { this->run(x); }
			virtual void visit(const sst::stmt::NoOp & x) const override { this->run(x); }
		};

		return Visitor{fx}(stmt);
	}
}