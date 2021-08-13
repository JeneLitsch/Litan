#include "LtnaMarkerTable.hxx"
#include "LtnaRedefinedMarker.hxx"
#include "LtnaUnknownMarker.hxx"

void ltn::a::MarkerTable::clear() {
	this->markers.clear();
}

void ltn::a::MarkerTable::add(const std::string & name, std::uint64_t addr) {
	if(this->markers.contains(name)) {
		throw RedefinedMarker(name);
	}
	this->markers.insert({name, addr});
}

std::uint64_t ltn::a::MarkerTable::find(const std::string & marker) const {
	if(this->markers.contains(marker)) {
		return this->markers.at(marker);
	}
	else {
		throw UnknownMarker(marker);
	}
}

bool ltn::a::MarkerTable::contains(const std::string & name) const {
	return this->markers.contains(name);
}
