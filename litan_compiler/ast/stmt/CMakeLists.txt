cmake_minimum_required(VERSION 3.13)

target_sources(litan_compiler PRIVATE 
	"Assign.cxx"
	"Block.cxx"
	"ForEach.cxx"
	"Conditional.cxx"
	"IfElse.cxx"
	"InfiniteLoop.cxx"
	"NewVar.cxx"
	"NoOp.cxx"
	"Return.cxx"
	"StatementExpression.cxx"
	"Switch.cxx"
	"Throw.cxx"
	"While.cxx"
	"Yield.cxx"
)
