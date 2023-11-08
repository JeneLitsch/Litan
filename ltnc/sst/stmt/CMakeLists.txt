cmake_minimum_required(VERSION 3.13)

target_sources(libltnc PRIVATE 
	"Assign.cxx"
	"Block.cxx"
	"ForEach.cxx"
	"IfElse.cxx"
	"InfiniteLoop.cxx"
	"NoOp.cxx"
	"Return.cxx"
	"Switch.cxx"
	"Throw.cxx"
	"While.cxx"
)
