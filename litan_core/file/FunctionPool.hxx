#pragma once
#include <vector>
#include <cstdint>
#include <string>
#include <span>
#include <optional>

namespace ltn {
	struct FunctionContext {
		std::string name;
		std::uint8_t arity;
		std::uint64_t address;
		std::uint64_t frame_size;
		std::uint64_t except_handler;
		bool is_external;
		bool is_variadic;
	};



	class FunctionPool {
	public:
		FunctionPool() = default;
		virtual ~FunctionPool() = default;
		
		// Serialization
		void read(std::span<const std::uint8_t>::iterator & it);
		void write(std::vector<std::uint8_t> & bytecode) const;

		// Access
		const FunctionContext * operator[](std::uint64_t id) const;
		std::optional<std::uint64_t> find_by_name(const std::string_view name) const;
		const FunctionContext * get_by_name(const std::string_view name) const;
		bool contains(const std::string_view name) const;
		void push_back(FunctionContext entry);


	private:
		std::vector<FunctionContext> entries;
	};
}