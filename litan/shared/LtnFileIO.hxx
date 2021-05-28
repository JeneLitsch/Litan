#pragma once


namespace ltn {
	inline std::string readFile(const std::string filename) {
		std::ifstream file(filename);
		std::string content((std::istreambuf_iterator<char>(file)),
					std::istreambuf_iterator<char>());
		file.close();
		return content;
	}

	inline void writeFile(const std::string & filename, const std::string content) {
		std::ofstream out(filename);
		out << content;
		out.close();
	}
}