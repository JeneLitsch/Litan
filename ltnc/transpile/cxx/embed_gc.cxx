#include "embed_gc.hxx"
#include "print.hxx"

namespace ltn::c::trans::cxx {
	void embed_sweep(std::ostream & out, Indent indent) {
		out << indent << "template<typename Obj>\n";
		out << indent << "void sweep(std::unique_ptr<Obj> * obj) {\n";
		out << indent.in() << "while(*obj) {\n";
		out << indent.in().in() << "if(!(*obj)->marked) {\n";
		// out << indent.in().in().in() << "std::cout << \"FREE\";\n";
		out << indent.in().in().in() << "*obj = std::move((*obj)->next);\n";
		out << indent.in().in() << "}\n";
		out << indent.in().in() << "else{\n";
		out << indent.in().in().in() << "(*obj)->marked = false;\n";
		out << indent.in().in().in() << "obj = &(*obj)->next;\n";
		out << indent.in().in() << "}\n";
		out << indent.in() << "};\n";
		out << indent << "};\n";
		out << indent << "\n";
	}



	void embed_mark(std::ostream & out, Indent indent) {
		out << indent << "void mark(const Value & value) {\n";
		print_switch(out, indent.in(), "value.type", {
			{"Value::Type::STRING", [] (std::ostream & out, Indent indent) {
				out << indent << "auto & str = *value.val.str;\n";
				out << indent << "str.marked = true;\n";
			}},
			{"Value::Type::ARRAY", [] (std::ostream & out, Indent indent) {
				out << indent << "auto & arr = *value.val.arr;\n";
				out << indent << "arr.marked = true;\n";
				out << indent << "for(auto & elem : arr.value) {\n";
				out << indent.in() << "mark(elem);\n";
				out << indent << "}\n";
			}},
			{"Value::Type::TUPLE", [] (std::ostream & out, Indent indent) {
				out << indent << "auto & tup = *value.val.tup;\n";
				out << indent << "tup.marked = true;\n";
				out << indent << "for(auto & elem : tup.value) {\n";
				out << indent.in() << "mark(elem);\n";
				out << indent << "}\n";
			}},
		});
		out << indent << "}\n";
		out << indent << "\n";
	}



	void embed_run_gc(std::ostream & out, Indent indent) {
		out << indent << "void gc(const Context & cnxt) {\n";
		out << indent.in() << "for(auto * root : cnxt.roots) {\n";
		out << indent.in().in() << "mark(*root);\n";
		out << indent.in() << "}\n";
		out << indent.in() << "sweep(&context.strings);\n";
		out << indent.in() << "sweep(&context.arrays);\n";
		out << indent << "}\n\n";
	}
}