cmake_minimum_required(VERSION 3.13)

target_sources(litan_compiler PRIVATE 
	"Assign.cxx"
	"Block.cxx"
	"Conditional.cxx"
	"CoReturn.cxx"
	"ForEach.cxx"
	"IfElse.cxx"
	"InfiniteLoop.cxx"
	"NoOp.cxx"
	"Return.cxx"
	"Switch.cxx"
	"Throw.cxx"
	"While.cxx"
	"Yield.cxx"
)
