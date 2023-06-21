#include "transpile_c.hxx"

namespace ltn::c::trans::cxx {
	void transpile_c_stmt(const sst::Block & sst_block, std::ostream & out, Indent indent) {
		out << indent << "{\n";
		for(const auto & elem : sst_block.statements) {
			transpile_c_statement(*elem, out, indent.in());
		}
		out << indent << "}\n";
	}



	void transpile_c_stmt(const sst::Return & ret, std::ostream & out, Indent indent) {
		out << indent << "return ";
		transpile_c_expression(*ret.expr, out, indent);
		out << ";\n";
	}



	void transpile_c_stmt(const sst::Throw &, std::ostream & out, Indent indent) {
		out << indent << "// Throw\n";
	}



	void transpile_c_stmt(const sst::IfElse &, std::ostream & out, Indent indent) {
		out << indent <<  "// IfElse\n";
	}



	void transpile_c_stmt(const sst::InfiniteLoop &, std::ostream & out, Indent indent) {
		out << indent <<  "// InfiniteLoop\n";
	}



	void transpile_c_stmt(const sst::While &, std::ostream & out, Indent indent) {
		out << indent <<  "// While\n";
	}



	void transpile_c_stmt(const sst::ForEach &, std::ostream & out, Indent indent) {
		out << indent <<  "// ForEach\n";
	}



	void transpile_c_stmt(const sst::Assign & assign, std::ostream & out, Indent indent) {
		out << indent;
		transpile_c_binding(*assign.binding, out, indent);
		out << " = ";
		transpile_c_expression(*assign.expr, out, indent);
		out << ";\n";
	}



	void transpile_c_stmt(const sst::Switch &, std::ostream & out, Indent indent) {
		out << indent <<  "// Switch\n";
	}



	void transpile_c_stmt(const sst::DoNothing &, std::ostream & out, Indent indent) {
		out << indent <<  "// DoNothing\n";
	}



	void transpile_c_statement(const sst::Statement & stmt, std::ostream & out, Indent indent) {
		sst::visit_statement(stmt, [&] (const auto & s) {
			transpile_c_stmt(s, out, indent);
			return 0;
		});
	}
}