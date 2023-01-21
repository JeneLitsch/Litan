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

		ltn_CObject param_object(std::uint64_t index, void * core) {
			return unwrap(core)->params.get<LibraryObj>(index).get();
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

		void return_object(ltn_CObject value, void * core) {

			auto ref = unwrap(core)->heap->alloc(LibraryObj{value, unwrap(core)->library});
			unwrap(core)->return_value = value::library_obj(ref);
		};
	}



	CoreWrapper wrap_core(Heap & heap, const Array & args, Value library) {
		return CoreWrapper {
			.params = ext::Parameters { heap, args },
			.heap = &heap,
			.return_value = value::null,
			.library = library,
		};
	}



	ltn_CApi bind_api(CoreWrapper & wrapper) {
		return ltn_CApi {
			.core = reinterpret_cast<void*>(&wrapper),
			
			.param_int = param_int,
			.param_bool = param_bool, 
			.param_float = param_float,
			.param_string = param_string,
			.param_object = param_object,

			.return_int = return_int, 
			.return_bool = return_bool,
			.return_float = return_float,
			.return_string = return_string,
			.return_object = return_object,
		};
	}
}