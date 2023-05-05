// #include "analyze.hxx"


// namespace ltn::c {
// 	namespace {
// 		template<typename Type>
// 		Type type_with_0_sub_types(const ast::Type & type) {
// 			if(!std::empty(type.sub_types)) throw CompilerError {
// 				"Type " + type.name + " does not allow subtype"
// 			};
// 			return Type{};
// 		}


// 		template<typename Type>
// 		Type type_with_1_sub_types(const ast::Type & type, Scope & scope) {
// 			if(std::size(type.sub_types) != 1) throw CompilerError {
// 				"Type " + type.name + " needs exactly 1 subtype"
// 			};
// 			return Type { 
// 				.contains = analyze_type(*type.sub_types.front(), scope)
// 			};
// 		}

// 		type::Type analyze_type_any(const ast::Type & type) {
// 			return type_with_0_sub_types<type::Any>(type);
// 		}

// 		type::Type analyze_type_null(const ast::Type & type) {
// 			return type_with_0_sub_types<type::Null>(type);
// 		}

// 		type::Type analyze_type_bool(const ast::Type & type) {
// 			return type_with_0_sub_types<type::Bool>(type);
// 		}

// 		type::Type analyze_type_char(const ast::Type & type) {
// 			return type_with_0_sub_types<type::Char>(type);
// 		}

// 		type::Type analyze_type_int(const ast::Type & type) {
// 			return type_with_0_sub_types<type::Int>(type);
// 		}

// 		type::Type analyze_type_float(const ast::Type & type) {
// 			return type_with_0_sub_types<type::Float>(type);
// 		}
		
// 		type::Type analyze_type_string(const ast::Type & type) {
// 			return type_with_0_sub_types<type::String>(type);
// 		}

// 		type::Type analyze_type_istream(const ast::Type & type) {
// 			return type_with_0_sub_types<type::Istream>(type);
// 		}

// 		type::Type analyze_type_ostream(const ast::Type & type) {
// 			return type_with_0_sub_types<type::Ostream>(type);
// 		}

// 		type::Type analyze_type_array(const ast::Type & type, Scope & scope) {
// 			return type_with_1_sub_types<type::Array>(type, scope);
// 		}

// 		type::Type analyze_type_queue(const ast::Type & type, Scope & scope) {
// 			return type_with_1_sub_types<type::Queue>(type, scope);
// 		}

// 		type::Type analyze_type_stack(const ast::Type & type, Scope & scope) {
// 			return type_with_1_sub_types<type::Stack>(type, scope);
// 		}

// 		type::Type analyze_type_optional(const ast::Type & type, Scope & scope) {
// 			if(std::size(type.sub_types) != 1) throw CompilerError {
// 				"Type " + type.name + " needs exactly 1 subtype"
// 			};
// 			if(type.sub_types.front()->name == "optional") {
// 				return type::Optional { 
// 					.contains = analyze_type(*type.sub_types.front()->sub_types.front(), scope)
// 				};
// 			}
// 			else {
// 				return type::Optional { 
// 					.contains = analyze_type(*type.sub_types.front(), scope)
// 				};
// 			}
// 		}

// 		type::Type analyze_type_tuple(const ast::Type & type, Scope & scope) {
// 			std::vector<type::Type> sub_types;
// 			for(const auto & c : type.sub_types) {
// 				sub_types.push_back(analyze_type(*c, scope));
// 			}
// 			return type::Tuple{ 
// 				.contained = std::move(sub_types)
// 			};
// 		}

// 		type::Type analyze_type_map(const ast::Type & type, Scope & scope) {
// 			if(std::size(type.sub_types) == 2) throw CompilerError {
// 				"Type " + type.name + " needs exactly 2 subtypes"
// 			};
// 			auto key = analyze_type(*type.sub_types.front(), scope); 
// 			auto val = analyze_type(*type.sub_types.front(), scope);
// 			return type::Map { .key = key, .val = val };
// 		}

// 		type::Type analyze_type_fx_ptr(const ast::Type & type, Scope & scope) {
// 			if(std::empty(type.sub_types)) throw CompilerError {
// 				"Type " + type.name + " needs at least 1 subtype"
// 			};
// 			std::vector<type::Type> parameters;
// 			for(const auto & t : type.sub_types) {
// 				parameters.push_back(analyze_type(*t, scope));
// 			}
// 			auto return_type = parameters.back();
// 			parameters.pop_back();
// 			return type::FxPtr { 
// 				.return_type = std::move(return_type),
// 				.parameter_types = std::move(parameters),
// 			};
// 		}
// 	}


// 	type::Type analyze_type(const ast::Type & type, Scope & scope) {
// 		if(type.name == "any") return analyze_type_any(type);
// 		if(type.name == "null") return analyze_type_null(type);
// 		if(type.name == "bool") return analyze_type_bool(type);
// 		if(type.name == "char") return analyze_type_char(type);
// 		if(type.name == "int") return analyze_type_int(type);
// 		if(type.name == "float") return analyze_type_float(type);
// 		if(type.name == "string") return analyze_type_string(type);
// 		if(type.name == "array") return analyze_type_array(type, scope); 
// 		if(type.name == "tuple") return analyze_type_tuple(type, scope); 
// 		if(type.name == "queue") return analyze_type_queue(type, scope);  
// 		if(type.name == "stack") return analyze_type_stack(type, scope);  
// 		if(type.name == "map") return analyze_type_map(type, scope);
// 		if(type.name == "optional") return analyze_type_optional(type, scope); 
// 		if(type.name == "istream") return analyze_type_istream(type);
// 		if(type.name == "ostream") return analyze_type_ostream(type);
// 		if(type.name == "fx_ptr") return analyze_type_fx_ptr(type, scope);
// 		if(auto * resolved = scope.resolve_type(type.name)) {
// 			return *resolved;
// 		}
// 		else throw CompilerError { "Unknown type" + type.name };
// 	}
// }