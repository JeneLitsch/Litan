cmake_minimum_required(VERSION 3.13)

target_sources(libltnvm PRIVATE 
	Clock.cxx
	Iterator.cxx
	ArrayIterator.cxx
	CombinedIterator.cxx
	RangeIterator.cxx
	ReversedIterator.cxx
	StringIterator.cxx
	RandomEngine.cxx
	Type.cxx
)