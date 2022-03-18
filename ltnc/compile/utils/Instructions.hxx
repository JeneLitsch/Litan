#pragma once
#include <string>
#include "ltn/float64_t.hxx"

namespace ltn::c::compile::inst {
	const std::string comment(std::string msg);
	const std::string jumpmark(const std::string_view id);
	const std::string jumpmark_except(const std::string_view id);
	const std::string_view error = "error\n";
	const std::string_view thr0w = "throw\n";
	const std::string_view c4tch = "catch\n";
	
	constexpr std::string_view add = "add\n";
	constexpr std::string_view sub = "sub\n";
	constexpr std::string_view mlt = "mlt\n";
	constexpr std::string_view div = "div\n";
	constexpr std::string_view mod = "mod\n";
	constexpr std::string_view sml = "sml\n";
	constexpr std::string_view bgr = "bgr\n";
	constexpr std::string_view smleql = "smleql\n";
	constexpr std::string_view bgreql = "bgreql\n";
	constexpr std::string_view eql = "eql\n";
	constexpr std::string_view ueql = "ueql\n";
	constexpr std::string_view comp = "comp\n";
	constexpr std::string_view approx = "approx\n";
	constexpr std::string_view notprox = "approx\n" "not\n";
	constexpr std::string_view shift_l = "shift_l\n";
	constexpr std::string_view shift_r = "shift_r\n";

	constexpr std::string_view neg = "neg\n";
	constexpr std::string_view n0t = "not\n";
	constexpr std::string_view inc = "inc\n";
	constexpr std::string_view dec = "dec\n";

	constexpr std::string_view capture = "capture\n";
	constexpr std::string_view invoke = "invoke\n";
	const std::string read_captured(std::uint64_t index);

	const std::string newu(std::uint64_t value);
	const std::string newi(std::int64_t value);
	const std::string newf(stx::float64_t value);
	const std::string newc(char value);
	constexpr std::string_view truE = "true\n";
	constexpr std::string_view falsE = "false\n";
	constexpr std::string_view null = "null\n";
	const std::string newarr(std::uint64_t size);
	const std::string newstr(std::string_view str);
	const std::string ch4r(char chr);
	const std::string elem = "elem\n";
	const std::string newfx(const std::string_view & fxName, std::size_t params);
	const std::string char_8(std::string_view & str);
	const std::string char_4(std::string_view & str);


	const std::string jump(const std::string_view & to);
	const std::string call(const std::string_view & to);
	const std::string tRy(const std::string_view & to);
	constexpr std::string_view reTurn = "return\n";
	const std::string ifelse(const std::string_view & to);
	const std::string parameters(std::uint64_t count);
	const std::string_view exlt = "exit\n";

	constexpr std::string_view read = "read\n";
	constexpr std::string_view write = "write\n";
	constexpr std::string_view scrap = "scrap\n";
	constexpr std::string_view duplicate = "duplicate\n";
	constexpr std::string_view makevar = "makevar\n";
	constexpr std::string_view at = "at\n";
	constexpr std::string_view at_write = "at_write\n";
	constexpr std::string_view read_0 = "read_0\n";
	constexpr std::string_view read_1 = "read_1\n";
	constexpr std::string_view read_2 = "read_2\n";
	constexpr std::string_view read_3 = "read_3\n";
	constexpr std::string_view write_0 = "write_0\n";
	constexpr std::string_view write_1 = "write_1\n";
	constexpr std::string_view write_2 = "write_2\n";
	constexpr std::string_view write_3 = "write_3\n";
	
	const std::string byte(std::uint8_t byte);

	const std::string read_x(std::uint64_t addr);
	const std::string write_x(std::uint64_t addr);

	const std::string member_read(std::uint64_t addr);
	const std::string member_write(std::uint64_t addr);
}