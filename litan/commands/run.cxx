#include "run.hxx"
#include "litan/shared/file.hxx"
#include "litan/shared/help.hxx"
#include "litan/shared/options.hxx"
#include "litan_compiler/Ltnc.hxx"
#include "litan_vm/litan_vm.hxx"

int run(std::span<const std::string_view> args) {
	std::span<const std::string_view> flags = cut_options(args);
	std::span<const std::string_view> rest = args.subspan(flags.size());
	RunOptions options = parse_options<RunOptions, read_run_option>(flags);
	
	if(options.help) {
		print_usage_hint();
		return EXIT_SUCCESS;
	}

	if(rest.size() < 1) {
		throw std::runtime_error{"Invalid run arguments"};
	}
	
	std::string_view script_path = rest[0];
	std::span<const std::string_view> script_args = rest.subspan(1);

	std::vector<ltn::Any> main_args;
	for (const auto & arg : script_args) {
		main_args.push_back(ltn::Any(arg));
	}

	const auto main_function = "";
	
	auto sources = ltn::c::read_sources({script_path});
	auto ast = ltn::c::parse(sources);
	auto sst = ltn::c::analyze(ast, options.build.analysis);
	auto instructions = ltn::c::compile(sst, options.build.compilation);
	auto bytecode = ltn::c::assemble(instructions);
	auto vm = ltn::vm::load(bytecode);
	ltn::vm::execute(vm, main_function, main_args);

	return EXIT_SUCCESS;
}