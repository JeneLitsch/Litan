#pragma once
#include "ltnc/sst/SST.hxx"
namespace ltn::c {
	const sst::Functional * resolve(
		const std::vector<const sst::Functional *> & functions,
		const Namespace & from,
		const Namespace & to,
		const std::string_view name,
		const std::size_t parameters);

	const sst::Definition * resolve(
		const std::vector<const sst::Definition *> & definitions,
		const Namespace & from,
		const Namespace & to,
		const std::string_view name);

	const sst::Global * resolve(
		const std::vector<const sst::Global *> & globals,
		const Namespace & from,
		const Namespace & to,
		const std::string_view name);

	const sst::FunctionTemplate * resolve(
		const std::vector<const sst::FunctionTemplate *> & functions,
		const Namespace & from,
		const Namespace & to,
		const std::string_view name,
		const std::size_t function_parameters,
		const std::size_t template_parameters);
}