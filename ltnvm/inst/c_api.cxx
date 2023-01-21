#include "c_api.hxx"

namespace ltn::vm {
	namespace {
		CoreWrapper * unwrap(void * core) {
			return reinterpret_cast<CoreWrapper*>(core);
		}



		std::int64_t param_int(std::uint64_t index, void * core) {
			return unwrap(core)->params.get<std::int64_t>(index);
		}

		std::uint8_t param_bool(std::uint64_t index, void * core) {
			return unwrap(core)->params.get<bool>(index);
		};

		stx::float64_t param_float(std::uint64_t index, void * core) {
			return unwrap(core)->params.get<stx::float64_t>(index);
		};

		const char * param_string(std::uint64_t index, void * core) {
			return unwrap(core)->params.get<std::string>(index).c_str();
		};


		
		void return_int(std::int64_t value, void * core) {
			unwrap(core)->return_value = value::integer(value);
		};

		void return_bool(std::uint8_t value, void * core) {
			unwrap(core)->return_value = value::boolean(value != 0);
		};

		void return_float(stx::float64_t value, void * core) {
			unwrap(core)->return_value = value::floating(value);
		};
		
		void return_string(const char * value, void * core) {
			auto ref = unwrap(core)->heap->alloc(std::string{value});
			unwrap(core)->return_value = value::string(ref);
		};
	}



	CoreWrapper wrap_core(Heap & heap, const Array & args) {
		return CoreWrapper {
			.params = ext::Parameters { heap, args },
			.heap = &heap,
			.return_value = value::null
		};
	}



	CApi bind_api(CoreWrapper & wrapper) {
		return CApi {
			.core = reinterpret_cast<void*>(&wrapper),
			.param_int = param_int,
			.param_bool = param_bool, 
			.param_float = param_float,
			.param_string = param_string,
			.return_int = return_int, 
			.return_bool = return_bool,
			.return_float = return_float,
			.return_string = return_string,
		};
	}
}