#include "LtnaMarkerTable.hxx"

void ltna::MarkerTable::clear() {
	this->markers.clear();
}

void ltna::MarkerTable::add(const std::string & name, std::uint64_t addr) {
	if(this->markers.contains(name)) {
		throw std::runtime_error("Redefinition of marker " + name);
	}
	this->markers.insert({name, addr});
}

std::uint64_t ltna::MarkerTable::find(const std::string & marker) const {
	if(this->markers.contains(marker)) {
		return this->markers.at(marker);
	}
	else {
		throw std::runtime_error("There is no marker named " + marker + " nor found");
	}
}

bool ltna::MarkerTable::contains(const std::string & name) const {
	return this->markers.contains(name);
}
