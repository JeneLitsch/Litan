#pragma once
#include <string>

namespace ltn::c::compile::inst {
	const std::string comment(std::string msg);
	const std::string jumpmark(const std::string_view id);
	const std::string_view error = "error\n";
	
	const std::string_view add = "add\n";
	const std::string_view sub = "sub\n";
	const std::string_view mlt = "mlt\n";
	const std::string_view div = "div\n";
	const std::string_view mod = "mod\n";
	const std::string_view sml = "sml\n";
	const std::string_view bgr = "bgr\n";
	const std::string_view smleql = "smleql\n";
	const std::string_view bgreql = "bgreql\n";
	const std::string_view eql = "eql\n";
	const std::string_view ueql = "ueql\n";
	const std::string_view neg = "neg\n";
	const std::string_view n0t = "not\n";

	const std::string newu(std::uint64_t value);
	const std::string newi(std::int64_t value);
	const std::string newf(double value);
	const std::string_view truE = "true\n";
	const std::string_view falsE = "false\n";
	const std::string_view null = "null\n";
	const std::string_view newarr = "newarr\n";

	const std::string jump(const std::string_view & to);
	const std::string call(const std::string_view & to);
	const std::string_view reTurn = "return\n";
	const std::string ifelse(const std::string_view & to);
	const std::string_view exlt = "exit\n";

	const std::string_view read = "read\n";
	const std::string_view write = "write\n";
	const std::string_view scrap = "scrap\n";
	const std::string_view makevar = "makevar\n";
	const std::string newref(std::uint64_t value);
	
	const std::string byte(std::uint8_t byte);
}