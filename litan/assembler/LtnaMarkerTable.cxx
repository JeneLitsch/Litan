#include "LtnaMarkerTable.hxx"
#include "LtnaRedefinedMarker.hxx"
#include "LtnaUnknownMarker.hxx"

void ltna::MarkerTable::clear() {
	this->markers.clear();
}

void ltna::MarkerTable::add(const std::string & name, std::uint64_t addr) {
	if(this->markers.contains(name)) {
		throw RedefinedMarker(name);
	}
	this->markers.insert({name, addr});
}

std::uint64_t ltna::MarkerTable::find(const std::string & marker) const {
	if(this->markers.contains(marker)) {
		return this->markers.at(marker);
	}
	else {
		throw UnknownMarker(marker);
	}
}

bool ltna::MarkerTable::contains(const std::string & name) const {
	return this->markers.contains(name);
}
