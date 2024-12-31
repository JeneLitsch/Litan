cmake_minimum_required(VERSION 3.13)

target_sources(litan_vm PRIVATE 
	"cast.cxx"
	"compare.cxx"
	"convert.cxx"
	"function.cxx"
	"GCLock.cxx"
	"json.cxx"
	"stringify.cxx"
	"to_value.cxx"
	"to_any.cxx"
)