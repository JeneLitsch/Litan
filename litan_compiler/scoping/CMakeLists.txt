cmake_minimum_required(VERSION 3.13)

target_sources(litan_compiler PRIVATE
	BlockScope.cxx
	CaseScope.cxx
	ExceptScope.cxx
	FunctionScope.cxx
	IifeScope.cxx
	LocalScope.cxx
	MajorScope.cxx
	MinorScope.cxx
	Scope.cxx
	Variable.cxx
)