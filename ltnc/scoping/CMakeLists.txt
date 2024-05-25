cmake_minimum_required(VERSION 3.13)

target_sources(libltnc PRIVATE
	"BlockScope.cxx"
	"CaseScope.cxx"
	"ExceptScope.cxx"
	"FunctionScope.cxx"
	"RootScope.cxx"
	"IifeScope.cxx"
	"LocalScope.cxx"
	"MinorScope.cxx"
	"NamespaceScope.cxx"
	"Scope.cxx"
)