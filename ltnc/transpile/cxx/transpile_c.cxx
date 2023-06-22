#include "transpile_c.hxx"
#include "embed_gc.hxx"
#include "object_types.hxx"
#include "primitive_types.hxx"
#include "utils.hxx"
#include "operators.hxx"

namespace ltn::c::trans::cxx {
	namespace {
		void print_includes(std::ostream & stream) {
			stream << "#include <cstdint>\n";
			stream << "#include <concepts>\n";
			stream << "#include <iostream>\n";
			stream << "#include <sstream>\n";
			stream << "#include <vector>\n";
			stream << "#include <memory>\n";
			stream << "\n";
		}



		void print_value_type_enum(std::ostream & stream, Indent indent) {
			stream << indent << "enum class Type : std::uint8_t {\n";
			stream << indent.in() << "NVLL = 0x00,\n";
			stream << indent.in() << "BOOL = 0x10, INT, FLOAT, CHAR,\n";
			stream << indent.in() << "ARRAY = 0x20, STRING, TUPLE,\n";
			stream << indent.in() << "ISTREAM = 0x30, OSTREAM,\n";
			stream << indent.in() << "FX_PTR = 0x40, ITERATOR, ITERATOR_STOP,\n";
			stream << indent.in() << "CLOCK = 0x50,\n";
			stream << indent.in() << "STRUCT = 0x60,\n";
			stream << indent.in() << "QUEUE = 0x70, STACK, MAP,\n";
			stream << indent.in() << "RNG = 0x80, TYPE,\n";
			stream << indent << "};\n";
			stream << indent << "\n";
		}



		void print_value_class(std::ostream & out, Indent indent) {
			out << indent << "struct Value {\n";
			print_value_type_enum(out, indent.in());
			out << indent.in() << "union Val {\n";
			
			for(const auto & p : primitive_types) {
				out << indent.in().in() << p.data_type << " " << p.value_member << ";\n";
			}

			for(const auto & o : object_types) {
				out << indent.in().in() << o.name << " * " << o.value_member << ";\n";
			}

			out << indent.in() << "};\n";
			out << indent.in() << "Value(Type type, Val val) : type{type}, val{val} {}\n";
			out << indent.in() << "Type type;\n";
			out << indent.in() << "Val val;\n";
			out << indent << "};\n\n";
			out << indent << "using VT = Value::Type;\n\n";
		}



		void print_context_class(std::ostream & stream, Indent indent) {
			stream << indent << "struct Context {\n";
			stream << indent.in() << "void push_root(Value * value) {\n";
			stream << indent.in().in() << "roots.push_back(value);\n"; 
			// stream << indent.in().in() << "std::cout << \"Push\" << roots.size() << \"\\n\";\n"; 
			stream << indent.in() << "}\n";
			stream << indent.in() << "void pop_root() {\n";
			// stream << indent.in().in() << "std::cout << \"Pop\" << roots.size() << \"\\n\";\n"; 
			stream << indent.in().in() << "roots.pop_back();\n"; 
			stream << indent.in() << "}\n"; 
			stream << indent.in() << "std::vector<const Value *> roots;\n"; 

			for(const auto & obj : object_types) {
				stream << indent.in() 
					<< "std::unique_ptr<" << obj.name << "> "
					<< to_lowercase(obj.name) << "s;\n"; 
			}
			stream << indent << "};\n\n";
		}



		void print_value_wrapper_class(std::ostream & stream, Indent indent, std::string_view name) {
			stream << indent << "class " << name << " final {\n";
			stream << indent << "public:\n";
			
			stream << indent.in() << name << "(const Value & value) : value {value} {\n";
			stream << indent.in().in() << "context.push_root(&this->value);\n";
			stream << indent.in() << "}\n";

			stream << indent.in() << "~" << name << "() {\n";
			stream << indent.in().in() << "context.pop_root();\n";
			stream << indent.in() << "}\n";

			stream << indent.in() << name << " & operator=(const Value & value) {\n";
			stream << indent.in().in() << "this->value = value;\n";
			stream << indent.in().in() << "return *this;\n";
			stream << indent.in() << "}\n";

			stream << indent.in() << "const Value & get() const {\n";
			stream << indent.in().in() << "return this->value;\n";
			stream << indent.in() << "}\n";

			stream << indent.in() << " operator const Value &() const {\n";
			stream << indent.in().in() << "return this->value;\n";
			stream << indent.in() << "}\n";

			print_delete_special_members(stream, name, indent.in());
			stream << indent << "private:\n";
			stream << indent.in() << "Value value;\n";
			stream << indent << "};\n\n";
		}


		void print_tmp_class(std::ostream & stream, Indent indent) {
			print_value_wrapper_class(stream, indent, "Tmp");
		}


		void print_var_class(std::ostream & stream, Indent indent) {
			print_value_wrapper_class(stream, indent, "Var");
		}



		void print_main(std::ostream & stream) {
			stream << "int main() {\n";
			stream << "\tstd::cout << ltn::stringify(fx::main_1(ltn::value_null()));\n";
			stream << "}\n";
			stream << "\n";
		}



		void print_stringify(std::ostream & out, Indent indent) {
			out << indent << "std::string stringify(const Value & value) {\n";
			out << indent.in() << "std::ostringstream oss;\n";
			print_switch(out, indent.in(), "value.type", {
				{"Value::Type::BOOL", [] (std::ostream & out, Indent indent) {
					out << indent << "oss << std::boolalpha << value.val.b;\n";
				}},
				{"Value::Type::CHAR", [] (std::ostream & out, Indent indent) {
					out << indent << "oss << value.val.c;\n";
				}},
				{"Value::Type::INT", [] (std::ostream & out, Indent indent) {
					out << indent << "oss << value.val.i;\n";
				}},
				{"Value::Type::FLOAT", [] (std::ostream & out, Indent indent) {
					out << indent << "oss << value.val.f;\n";
				}},
				{"Value::Type::STRING", [] (std::ostream & out, Indent indent) {
					out << indent << "oss << value.val.str->value;\n";
				}},
				{"Value::Type::ARRAY", [] (std::ostream & out, Indent indent) {
					out << indent << "auto & arr = *value.val.arr;\n";
					out << indent << "oss << \"[\";\n";
					out << indent << "for(std::size_t i = 0; i < std::size(arr.value); ++i) {\n";
					out << indent.in() << "if(i) oss << \", \";\n";
					out << indent.in() << "oss << stringify(arr.value[i]);\n";
					out << indent << "}\n";
					out << indent << "oss << \"]\";\n";
				}},
				{"Value::Type::TUPLE", [] (std::ostream & out, Indent indent) {
					out << indent << "auto & tup = *value.val.tup;\n";
					out << indent << "oss << \"(\";\n";
					out << indent << "for(std::size_t i = 0; i < std::size(tup.value); ++i) {\n";
					out << indent.in() << "if(i) oss << \", \";\n";
					out << indent.in() << "oss << stringify(tup.value[i]);\n";
					out << indent << "}\n";
					out << indent << "oss << \")\";\n";
				}},
			});
			out << indent.in() << "return oss.str();\n";
			out << indent << "}\n";
			out << indent << "\n";
		}
	}

	std::string transpile_c(const sst::Program & program) {
		std::ostringstream oss;
		
		print_includes(oss);
		Indent indent_ns {1};

		oss << "namespace ltn {\n";

		print_forward_decls(oss, indent_ns, object_types);

		print_value_class(oss, indent_ns);
		print_context_class(oss, indent_ns);
		oss << indent_ns << "Context context;\n\n";
		print_var_class(oss, indent_ns);
		print_tmp_class(oss, indent_ns);
		
		print_objects(oss, indent_ns, object_types);

		embed_sweep(oss, indent_ns);
		embed_mark(oss, indent_ns);
		embed_run_gc(oss, indent_ns);

		oss << indent_ns << "template<typename Obj>\n";
		oss << indent_ns << "static Obj * track(std::unique_ptr<Obj> & base, std::unique_ptr<Obj> obj) {\n";
		oss << indent_ns.in() << "obj->next = std::move(base);\n";
		oss << indent_ns.in() << "base = std::move(obj);\n";
		oss << indent_ns.in() << "return base.get();\n";
		oss << indent_ns << "}\n";

		for(const auto & p : primitive_types) {
			p.print_maker(p, oss, indent_ns);
		}

		oss << indent_ns << "Value value_string(const std::string_view str) {\n";
		oss << indent_ns.in() << "gc(context);\n";
		oss << indent_ns.in() << "auto obj = std::make_unique<String>(std::string(str));\n";
		oss << indent_ns.in() << "auto * ptr = track(context.strings, std::move(obj));\n";
		oss << indent_ns.in() << "return Value {Value::Type::STRING, Value::Val { .str=ptr }};\n";
		oss << indent_ns << "}\n\n";

		oss << indent_ns << "Value value_array(std::vector<Value> arr = {}) {\n";
		oss << indent_ns.in() << "gc(context);\n";
		oss << indent_ns.in() << "auto obj = std::make_unique<Array>();\n";
		oss << indent_ns.in() << "obj->value = std::move(arr);\n";
		oss << indent_ns.in() << "auto * ptr = track(context.arrays, std::move(obj));\n";
		oss << indent_ns.in() << "return Value {Value::Type::ARRAY, Value::Val { .arr=ptr }};\n";
		oss << indent_ns << "}\n\n";

		oss << indent_ns << "Value value_tuple(std::vector<Value> tup = {}) {\n";
		oss << indent_ns.in() << "gc(context);\n";
		oss << indent_ns.in() << "auto obj = std::make_unique<Tuple>();\n";
		oss << indent_ns.in() << "obj->value = std::move(tup);\n";
		oss << indent_ns.in() << "auto * ptr = track(context.tuples, std::move(obj));\n";
		oss << indent_ns.in() << "return Value {Value::Type::TUPLE, Value::Val { .tup=ptr }};\n";
		oss << indent_ns << "}\n\n";

		oss << indent_ns << "Value value_cout() {\n";
		oss << indent_ns.in() << "gc(context);\n";
		oss << indent_ns.in() << "auto obj = std::make_unique<OStream>(&std::cout);\n";
		oss << indent_ns.in() << "auto * ptr = track(context.ostreams, std::move(obj));\n";
		oss << indent_ns.in() << "return Value {Value::Type::OSTREAM, Value::Val { .out=ptr }};\n";
		oss << indent_ns << "}\n\n";

		oss << indent_ns << "constexpr std::uint16_t combine(VT l, VT r) {\n";
		oss << indent_ns.in() << "return static_cast<std::uint16_t>(l) + (static_cast<std::uint16_t>(r) << 8);\n";
		oss << indent_ns << "}\n\n";

		wrap_binary_operator(oss, indent_ns, "add", "+");
		print_concat(oss, indent_ns);
		add_dispatch(oss, indent_ns);

		wrap_binary_operator(oss, indent_ns, "sub", "-");
		arith_dispatch(oss, indent_ns, "sub");

		wrap_binary_operator(oss, indent_ns, "mlt", "*");
		arith_dispatch(oss, indent_ns, "mlt");

		wrap_binary_operator(oss, indent_ns, "div", "/");
		arith_dispatch(oss, indent_ns, "div");
		
		wrap_unary_operator(oss, indent_ns, "neg", "-");
		unary_dispatch(oss, "neg", indent_ns);

		print_stringify(oss, indent_ns);

		oss << "}\n";

		oss << "namespace fx {\n";
		for(const auto & fx : program.functions) {
			oss << indent_ns;
			print_function_header(*fx, oss);
			oss << ";}\n";
		}
		oss << "\n";
		for(const auto & fx : program.functions) {
			oss << transpile_c_functional(*fx, indent_ns);
		}
		oss << "}\n";
		
		print_main(oss);

		return oss.str();
	}
}