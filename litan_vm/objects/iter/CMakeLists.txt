cmake_minimum_required(VERSION 3.13)

target_sources(litan_vm PRIVATE 
	"Iterator.cxx"
	"ContiguousIterator.cxx"
	"CoroutineIterator.cxx"
	"CombinedIterator.cxx"
	"RangeIterator.cxx"
	"ReversedIterator.cxx"
	"StringIterator.cxx"
	"MapIterator.cxx"
)