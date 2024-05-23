cmake_minimum_required(VERSION 3.13)

target_sources(libltnc PRIVATE
	BlockScope.cxx
	CaseScope.cxx
	ExceptScope.cxx
	FunctionScope.cxx
	GlobalScope.cxx
	IifeScope.cxx
	LocalScope.cxx
	MajorScope.cxx
	MinorScope.cxx
	Scope.cxx
	Variable.cxx
)