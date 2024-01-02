cmake_minimum_required(VERSION 3.13)

target_sources(libltnc PRIVATE
	CustomLiteral.cxx
	CustomResolver.cxx
	DefinitionTable.cxx
	FunctionQueue.cxx
	MemberTable.cxx
	GlobalTable.cxx
	namespace_resolution.cxx
)