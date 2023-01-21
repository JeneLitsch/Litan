#include "c_api.hxx"

namespace ltn::vm {
	namespace {
		std::int64_t param_int(std::uint64_t index, void * core) {
			auto * wrapper = reinterpret_cast<CoreWrapper*>(core);
			return wrapper->params.get<std::int64_t>(index);
		}

		std::uint8_t param_bool(std::uint64_t index, void * core) {
			auto * wrapper = reinterpret_cast<CoreWrapper*>(core);
			return wrapper->params.get<bool>(index);
		};

		stx::float64_t param_float(std::uint64_t index, void * core) {
			auto * wrapper = reinterpret_cast<CoreWrapper*>(core);
			return wrapper->params.get<stx::float64_t>(index);
		};

		void return_int(std::int64_t value, void * core) {
			auto * wrapper = reinterpret_cast<CoreWrapper*>(core);
			wrapper->return_value = value::integer(value);
		};

		void return_bool(std::uint8_t value, void * core) {
			auto * wrapper = reinterpret_cast<CoreWrapper*>(core);
			wrapper->return_value = value::boolean(value != 0);
		};

		void return_float(stx::float64_t value, void * core) {
			auto * wrapper = reinterpret_cast<CoreWrapper*>(core);
			wrapper->return_value = value::floating(value);
		};
	}

	CApi bind_api(CoreWrapper & wrapper) {
		return CApi {
			.core = reinterpret_cast<void*>(&wrapper),
			.param_int = param_int,
			.param_bool = param_bool, 
			.param_float = param_float,
			.return_int = return_int, 
			.return_bool = return_bool,
			.return_float = return_float,
		};
	}
}