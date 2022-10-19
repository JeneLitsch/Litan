#include "parse.hxx"


namespace ltn::c {

	namespace {

		using TT = Token::Type;

		class BraceTracker {
		public:
			void open() {
				++this->opened_braces;
			}



			void found_closed(std::int64_t count) {
				this->found_closed_braces += count;
			}
			
			
			
			void close() {
				if(this->found_closed_braces <= 0) throw CompilerError{"Missing >"};
				if(this->opened_braces <= 0) throw CompilerError{"Unexpected >"};
				--this->opened_braces;
				--this->found_closed_braces;
			}



			void finalize() {
				if(this->opened_braces < 0) throw CompilerError{"Unexpected >"};
				if(this->opened_braces > 0) throw CompilerError{"Missing >"};
				if(this->found_closed_braces < 0) throw CompilerError{"Missing >"};
				if(this->found_closed_braces > 0) throw CompilerError{"Unexpected >"};
			} 

		private:
			std::int64_t opened_braces = 0;
			std::int64_t found_closed_braces = 0;
		};


		void open_brace(Tokens & tokens, BraceTracker & brace_tracker) {
			if(!match(TT::SMALLER, tokens)) throw CompilerError{"Expected <"};
			brace_tracker.open();
		}




		void close_brace(Tokens & tokens, BraceTracker & brace_tracker) {
			if(match(TT::BIGGER, tokens)) {
				brace_tracker.found_closed(1);
			}
			if(match(TT::SHIFT_R, tokens)) {
				brace_tracker.found_closed(2);
			}
			brace_tracker.close();
		}



		type::Type parse_type(Tokens & tokens, BraceTracker & brace_tracker);



		type::Array parse_type_array(Tokens & tokens, BraceTracker & brace_tracker) {
			open_brace(tokens, brace_tracker);
			auto contains = parse_type(tokens, brace_tracker);
			close_brace(tokens, brace_tracker);
			return type::Array{contains};
		}



		type::Map parse_type_map(Tokens & tokens, BraceTracker & brace_tracker) {
			open_brace(tokens, brace_tracker);
			auto key = parse_type(tokens, brace_tracker);
			if(!match(TT::COMMA, tokens)) throw CompilerError{"Expected , between key type"};
			auto val = parse_type(tokens, brace_tracker);
			close_brace(tokens, brace_tracker);
			return type::Map{
				.key = key,
				.val = val,
			};
		}



		type::Type parse_fxptr(Tokens & tokens, BraceTracker & brace_tracker) {
			open_brace(tokens, brace_tracker);
			auto return_type = parse_type(tokens, brace_tracker);
			if(!match(TT::PAREN_L, tokens)) throw CompilerError{"Expected ("};
			std::vector<type::Type> parameter_types;
			do {
				parameter_types.push_back(parse_type(tokens, brace_tracker));
			} while(match(TT::COMMA, tokens));
			if(!match(TT::PAREN_R, tokens)) throw CompilerError{"Expected )"};
			close_brace(tokens, brace_tracker);
			return type::FxPtr {
				.return_type = return_type,
				.parameter_types = parameter_types
			};
		}



		type::Type parse_type(Tokens & tokens, BraceTracker & brace_tracker) {
			if(auto type_name = match(TT::INDENTIFIER, tokens)) {
				if(type_name->str == "null") return type::Null{}; 
				if(type_name->str == "any") return type::Any{};
				if(type_name->str == "bool") return type::Bool{}; 
				if(type_name->str == "char") return type::Char{}; 
				if(type_name->str == "int") return type::Int{}; 
				if(type_name->str == "float") return type::Float{}; 
				if(type_name->str == "string") return type::String{}; 
				if(type_name->str == "array") return parse_type_array(tokens, brace_tracker); 
				if(type_name->str == "map") return parse_type_map(tokens, brace_tracker);
				if(type_name->str == "fx_ptr") return parse_fxptr(tokens, brace_tracker);
				throw CompilerError{"Unknown type name " + type_name->str};
			}
			else {
				throw CompilerError{"Expected type name"};
			}
		}
	}



	type::Type parse_type(Tokens & tokens) {
		BraceTracker brace_tracker;
		auto type = parse_type(tokens, brace_tracker);
		brace_tracker.finalize();
		return type;
	}



	type::Type parse_var_type(Tokens & tokens) {
		return match(TT::COLON, tokens) ? parse_type(tokens) : type::Any{};
	}



	type::Type parse_return_type(Tokens & tokens) {
		return match(TT::RARROW, tokens) ? parse_type(tokens) : type::Any{};
	}
}