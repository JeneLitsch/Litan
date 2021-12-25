#include "LtnBackend.hxx"
#include "compiling.hxx"
void ltn::c::compile::LtnBackend::compile(
	const Config & config,
	const ast::Source & source) {
	
	compile::CompilerInfo info {
		config,
		this->fxTable,
		this->memberTable,
		this->jumpMarkCounter};
	
	this->buffer << compile::source(source, info);
}

void ltn::c::compile::LtnBackend::yield(std::ostream & out) {
	// Jump to main()
	if(const auto fxmain = this->fxTable.resolve("main", {}, 0)) {
		out	<< compile::inst::call(fxmain->id) 
			<< compile::inst::exlt
			<< "\n";
		out << this->buffer.rdbuf();
	}
	else {
		throw CompilerError {"main() is undefined", 0};
	}
}