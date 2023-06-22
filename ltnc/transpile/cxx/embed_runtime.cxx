#include "embed_runtime.hxx"
#include "embed_gc.hxx"
#include "object_types.hxx"
#include "primitive_types.hxx"
#include "utils.hxx"
#include "operators.hxx"
#include "print.hxx"

namespace ltn::c::trans::cxx {
	namespace {
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



		void print_is_truthy(std::ostream & out, Indent indent) {
			out << indent << "bool is_truthy(const Value & value) {\n";
			out << indent.in() << "std::ostringstream oss;\n";
			print_switch(out, indent.in(), "value.type", {
				{"Value::Type::NVLL", [] (std::ostream & out, Indent indent) {
					out << indent << "return false;\n";
				}},
				{"Value::Type::BOOL", [] (std::ostream & out, Indent indent) {
					out << indent << "return value.val.b;\n";
				}},
				{"Value::Type::CHAR", [] (std::ostream & out, Indent indent) {
					out << indent << "return value.val.c != 0;\n";
				}},
				{"Value::Type::INT", [] (std::ostream & out, Indent indent) {
					out << indent << "return value.val.i != 0;\n";
				}},
				{"Value::Type::FLOAT", [] (std::ostream & out, Indent indent) {
					out << indent << "return value.val.f != 0;\n";
				}},
				{"Value::Type::STRING", [] (std::ostream & out, Indent indent) {
					out << indent << "return true;\n";
				}},
				{"Value::Type::ARRAY", [] (std::ostream & out, Indent indent) {
					out << indent << "return true;\n";
				}},
				{"Value::Type::TUPLE", [] (std::ostream & out, Indent indent) {
					out << indent << "return true;\n";
				}},
			});
			out << indent.in() << "return true;\n";
			out << indent << "}\n";
			out << indent << "\n";
		}
	}



	void embed_runtime(std::ostream & out, Indent indent) {
		out << "namespace ltn {\n";

		print_forward_decls(out, indent, object_types);

		print_value_class(out, indent);
		print_context_class(out, indent);
		out << indent << "Context context;\n\n";

		print_value_wrapper_class(out, indent, "Tmp");
		print_value_wrapper_class(out, indent, "Var");
		print_value_wrapper_class(out, indent, "Global");
		
		print_objects(out, indent, object_types);

		embed_sweep(out, indent);
		embed_mark(out, indent);
		embed_run_gc(out, indent);

		out << indent << "template<typename Obj>\n";
		out << indent << "static Obj * track(std::unique_ptr<Obj> & base, std::unique_ptr<Obj> obj) {\n";
		out << indent.in() << "obj->next = std::move(base);\n";
		out << indent.in() << "base = std::move(obj);\n";
		out << indent.in() << "return base.get();\n";
		out << indent << "}\n";

		for(const auto & p : primitive_types) {
			p.print_maker(p, out, indent);
		}

		out << indent << "Value value_string(const std::string_view str) {\n";
		out << indent.in() << "gc(context);\n";
		out << indent.in() << "auto obj = std::make_unique<String>(std::string(str));\n";
		out << indent.in() << "auto * ptr = track(context.strings, std::move(obj));\n";
		out << indent.in() << "return Value {Value::Type::STRING, Value::Val { .str=ptr }};\n";
		out << indent << "}\n\n";

		out << indent << "Value value_array(std::vector<Value> arr = {}) {\n";
		out << indent.in() << "gc(context);\n";
		out << indent.in() << "auto obj = std::make_unique<Array>();\n";
		out << indent.in() << "obj->value = std::move(arr);\n";
		out << indent.in() << "auto * ptr = track(context.arrays, std::move(obj));\n";
		out << indent.in() << "return Value {Value::Type::ARRAY, Value::Val { .arr=ptr }};\n";
		out << indent << "}\n\n";

		out << indent << "Value value_tuple(std::vector<Value> tup = {}) {\n";
		out << indent.in() << "gc(context);\n";
		out << indent.in() << "auto obj = std::make_unique<Tuple>();\n";
		out << indent.in() << "obj->value = std::move(tup);\n";
		out << indent.in() << "auto * ptr = track(context.tuples, std::move(obj));\n";
		out << indent.in() << "return Value {Value::Type::TUPLE, Value::Val { .tup=ptr }};\n";
		out << indent << "}\n\n";

		out << indent << "Value value_cout() {\n";
		out << indent.in() << "gc(context);\n";
		out << indent.in() << "auto obj = std::make_unique<OStream>(&std::cout);\n";
		out << indent.in() << "auto * ptr = track(context.ostreams, std::move(obj));\n";
		out << indent.in() << "return Value {Value::Type::OSTREAM, Value::Val { .out=ptr }};\n";
		out << indent << "}\n\n";

		out << indent << "constexpr std::uint16_t combine(VT l, VT r) {\n";
		out << indent.in() << "return static_cast<std::uint16_t>(l) + (static_cast<std::uint16_t>(r) << 8);\n";
		out << indent << "}\n\n";

		wrap_binary_operator(out, indent, "add", "+");
		print_concat(out, indent);
		add_dispatch(out, indent);

		wrap_binary_operator(out, indent, "sub", "-");
		arith_dispatch(out, indent, "sub");

		wrap_binary_operator(out, indent, "mlt", "*");
		arith_dispatch(out, indent, "mlt");

		wrap_binary_operator(out, indent, "div", "/");
		arith_dispatch(out, indent, "div");
		
		wrap_unary_operator(out, indent, "neg", "-");
		unary_dispatch(out, "neg", indent);

		print_stringify(out, indent);
		print_is_truthy(out, indent);

		out << "}\n";
	}
}
