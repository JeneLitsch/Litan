#include "io.hxx"
#include "litan_vm/utils/stringify.hxx"
#include <filesystem>

namespace ltn::vm::stdlib {
		namespace {
		using VT = ValueType;


		template<typename T>
		auto add_out (VMCore & core, T && out) {
			core.heap.collect_garbage(core.stack);
			const auto ptr = core.heap.alloc<OStream>(std::forward<T>(out));
			return value::ostream(ptr);
		}



		template<typename T>
		Value add_in (VMCore & core, T && in) {
			core.heap.collect_garbage(core.stack);
			const auto ptr = core.heap.alloc<IStream>(std::forward<T>(in));
			return value::istream(ptr);
		}
	}




	Value cout::func(Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		return add_out(core, OStream{std::cout});
	}



	Value fout::func(Context * context, const Value * args) {
		const auto ref = args[0];
		const auto openmode = req_int(args + 1);
		VMCore & core = *static_cast<VMCore*>(context->core);
		if(!is_string(ref)) throw except::invalid_argument();
		
		const String * path = value::as<String>(ref);
		auto path_str = path->copy_to_std_string(); 

		const auto flags = openmode ? std::ios::app : std::ios::trunc;

		auto fout = std::make_unique<std::ofstream>(path_str, flags);
		return add_out(core, OStream{std::move(fout)});
	}



	Value strout::func(Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		return add_out(core, OStream{std::make_unique<std::ostringstream>()});
	}



	Value cin::func(Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		return add_in(core, IStream{std::cin});
	}



	Value fin::func(Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		if(!is_string(args[0])) {
			throw except::invalid_argument();
		}
		const String * path = value::as<String>(args[0]);
		auto path_str = path->copy_to_std_string(); 
		if(!std::filesystem::exists(path_str)) {
			throw except::cannot_open_file(path_str);
		}
		return add_in(core, IStream{std::make_unique<std::ifstream>(path_str)});
	}



	Value strin::func(Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		if(!is_string(args[0])) throw except::invalid_argument();
		const String * str = value::as<String>(args[0]);
		return add_in(core, IStream{std::make_unique<std::istringstream>(str->copy_to_std_string())});
	}



	Value close_stream::func(Context * context, const Value * args) {
		if(is_ostream(args[0])) {
			std::ostream & ostream = value::as<OStream>(args[0])->get();
			if(auto * out = dynamic_cast<std::ofstream *>(&ostream)) {
				out->close();
			}
			else {
				throw Exception{
					Exception::Type::INVALID_ARGUMENT,
					"Not an ofstream"};
			}
		}

		else if(is_istream(args[0])) {
			std::istream & istream = value::as<IStream>(args[0])->get();
			if(auto * in = dynamic_cast<std::ifstream *>(&istream)) {
				in->close();
			}
			else {
				throw Exception{
					Exception::Type::INVALID_ARGUMENT,
					"Not an ifstream"};
			}
		}

		else {
			throw Exception{
				Exception::Type::INVALID_ARGUMENT,
				"Not a stream"};
		}
		return value::null;
	}



	Value is_eof::func(Context * context, const Value * args) {
		if (is_istream(args[0])) {
			IStream * istream = value::as<IStream>(args[0]);
			return value::boolean(istream->get().peek() == EOF);
		}
		else { 
			throw except::not_input();
		}
	}




	Value print::func(Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		if (is_ostream(args[0])) {
			OStream * ostream = value::as<OStream>(args[0]);
			ostream->get() << stringify(args[1], core); 
			return value::null;
		}
		else {
			throw except::not_output();
		}
	}



	Value read_str::func(Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		if (is_istream(args[0])) {
			IStream * istream = value::as<IStream>(args[0]);
			std::string value;
			istream->get() >> value;
			if(istream->get()) {
				auto ref = core.heap.alloc(String{std::move(value)});
				return value::string(ref);
			}
			else {
				istream->get().clear();
				return value::null;
			}
		}
		else {
			throw except::not_input();
		}
	}



	Value read_line::func(Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		if (is_istream(args[0])) {
			IStream * istream = value::as<IStream>(args[0]);
			std::string value;
			std::getline(istream->get(), value);
			if(istream->get()) {
				auto ref = core.heap.alloc(String{std::move(value)});
				return value::string(ref);
			}
			else {
				istream->get().clear();
				return value::null;
			}
		}
		else {
			throw except::not_input();
		}
	}



	Value read_bool::func(Context * context, const Value * args) {
		if (is_istream(args[0])) {
			IStream * istream = value::as<IStream>(args[0]);
			bool value;
			istream->get() >> std::ws;

			if(istream->get().peek() == '0') {
				value = false;
				istream->get().ignore();
			}
			
			else if(istream->get().peek() == '1') {
				value = true;
				istream->get().ignore();
			}
			
			else  {
				istream->get() >> std::boolalpha >> value >> std::noboolalpha;
			}

			if(istream->get()) {
				return value::boolean(value);
			}
			else {
				istream->get().clear();
				return value::null;
			}
		}
		else {
			throw except::not_input();
		}
	}



	Value read_char::func(Context * context, const Value * args) {
		if (is_istream(args[0])) {
			IStream * istream = value::as<IStream>(args[0]);
			char value;
			istream->get() >> value;
			if(istream->get()) {
				return value::integer(value);
			}
			else {
				istream->get().clear();
				return value::null;
			}
		}
		else {
			throw except::not_input();
		}
	}



	Value read_int::func(Context * context, const Value * args) {
		if (is_istream(args[0])) {
			IStream * istream = value::as<IStream>(args[0]);
			std::int64_t value;
			istream->get() >> value;
			if(istream->get()) {
				return value::integer(value);
			}
			else {
				istream->get().clear();
				return value::null;
			}
		}
		else {
			throw except::not_input();
		}
	}



	Value read_float::func(Context * context, const Value * args) {
		if (is_istream(args[0])) {
			IStream * istream = value::as<IStream>(args[0]);
			ltn_Float value;
			istream->get() >> value;
			if(istream->get()) {
				return value::floating(value);
			}
			else {
				istream->get().clear();
				return value::null;
			}
		}
		else {
			throw except::not_input();
		}
	}



	Value read_all::func(Context * context, const Value * args) {
		VMCore & core = *static_cast<VMCore*>(context->core);
		if (is_istream(args[0])) {
			IStream * istream = value::as<IStream>(args[0]);
			std::ostringstream oss;
			oss << istream->get().rdbuf();
			const auto ref = core.heap.alloc(String{oss.str()});
			return value::string(ref);
		}
		else {
			throw except::not_input();
		}
	}



	Value set_fg_color::func(Context * context, const Value * args) {
		const auto color = req_int(args + 1);
		if(is_ostream(args[0])) {
			std::ostream & out = value::as<OStream>(args[0])->get();
			out	<< "\u001b[3" << color % 8; 
			if(color >= 8) out << ";1";
			out << "m";
			return value::null;
		}
		else throw except::invalid_argument();
	}



	Value set_bg_color::func(Context * context, const Value * args) {
		const auto color = req_int(args + 1);
		if(is_ostream(args[0])) {
			std::ostream & out = value::as<OStream>(args[0])->get();
			out	<< "\u001b[4" << color % 8;
			if(color >= 8) out << ";1";
			out << "m";
			return value::null;
		}
		else throw except::invalid_argument();
	}



	Value reset_color::func(Context * context, const Value * args) {
		if(is_ostream(args[0])) {
			std::ostream & out = value::as<OStream>(args[0])->get();
			out	<< "\u001b[0m";
			return value::null;
		}
		else throw except::invalid_argument();
	}
}