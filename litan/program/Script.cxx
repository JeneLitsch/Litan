#include "Script.hxx"
#include "AssemblerParser.hxx"
#include <fstream>
#include <filesystem>
ltn::Script ltn::Script::load(const std::string & fileName){
	if(!std::filesystem::exists(fileName)){ throw std::runtime_error("Cannot open file: " + fileName); }
	std::ifstream file(fileName);
	std::string source((std::istreambuf_iterator<char>(file)),
                 std::istreambuf_iterator<char>());
	file.close();
	return Script::parse(source);
}

ltn::Script ltn::Script::parse(const std::string & source){
	return Script(AssemblerParser().parse(source));
}
