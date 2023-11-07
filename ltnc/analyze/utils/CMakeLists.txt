cmake_minimum_required(VERSION 3.13)

target_sources(libltnc PRIVATE
	CustomLiteral.cxx
	CustomResolver.cxx
	DefinitionTable.cxx
	FunctionQueue.cxx
	FunctionScope.cxx
	MajorScope.cxx
	MemberTable.cxx
	GlobalTable.cxx
	MinorScope.cxx
	namespace_resolution.cxx
	Scope.cxx
	Variable.cxx
)