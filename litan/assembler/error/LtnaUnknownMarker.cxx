#include "LtnaUnknownMarker.hxx"

ltn::a::UnknownMarker::UnknownMarker(const std::string & marker)
:	InvalidMarker("Marker \"" + marker + "\" is unknown", "", marker, 0) {}