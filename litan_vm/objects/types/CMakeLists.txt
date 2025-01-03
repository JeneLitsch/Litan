cmake_minimum_required(VERSION 3.13)

target_sources(litan_vm PRIVATE 
	"ArrayType.cxx"
	"BoolType.cxx"
	"ClockType.cxx"
	"CoroutineType.cxx"
	"FloatType.cxx"
	"FunctionType.cxx"
	"IntType.cxx"
	"NullType.cxx"
	"StringType.cxx"
	"MapType.cxx"
	"TupleType.cxx"
	"IteratorType.cxx"
	"StackType.cxx"
	"QueueType.cxx"
	"StructType.cxx"
	"IStreamType.cxx"
	"OStreamType.cxx"
)