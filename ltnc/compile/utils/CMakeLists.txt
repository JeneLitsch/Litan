cmake_minimum_required(VERSION 3.13)

target_sources(libltnc PRIVATE
	CompilerInfo.cxx
	MajorScope.cxx
	MemberTable.cxx
	MinorScope.cxx
	namespace_resolution.cxx
	Scope.cxx
	Variable.cxx
)