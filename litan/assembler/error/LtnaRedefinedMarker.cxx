#include "LtnaRedefinedMarker.hxx"

ltna::RedefinedMarker::RedefinedMarker(const std::string & marker)
:	InvalidMarker("Redefinition of marker \"" + marker + "\"", "", marker, 0) {}