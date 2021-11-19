#pragma once
#include <string>

namespace ltn::c::compile::inst {
	std::string comment(std::string msg);
	std::string jumpmark(const std::string_view id);
	const std::string_view r3turn = "return\n";
	const std::string_view error = "error\n";
	
	const std::string_view addi = "addi\n";
	const std::string_view subi = "subi\n";
	const std::string_view mlti = "mlti\n";
	const std::string_view divi = "divi\n";
	const std::string_view modi = "modi\n";
	const std::string_view smli = "smli\n";
	const std::string_view bgri = "bgri\n";
	const std::string_view smleqli = "smleqli\n";
	const std::string_view bgreqli = "bgreqli\n";
	const std::string_view eqli = "eqli\n";
	const std::string_view ueqli = "ueqli\n";
	const std::string_view negi = "negi\n";

	const std::string_view addf = "addf\n";
	const std::string_view subf = "subf\n";
	const std::string_view mltf = "mltf\n";
	const std::string_view divf = "divf\n";
	const std::string_view modf = "modf\n";
	const std::string_view smlf = "smlf\n";
	const std::string_view bgrf = "bgrf\n";
	const std::string_view smleqlf = "smleqlf\n";
	const std::string_view bgreqlf = "bgreqlf\n";
	const std::string_view eqlf = "eqlf\n";
	const std::string_view ueqlf = "ueqlf\n";
	const std::string_view negf = "negf\n";

	const std::string newu(std::uint64_t value);
	const std::string newi(std::int64_t value);
	const std::string newf(double value);
	const std::string_view truE = "true\n";
	const std::string_view falsE = "false\n";
	const std::string_view read = "read\n";
	const std::string_view write = "write\n";
	const std::string_view scrap = "scrap\n";

	std::string jump(const std::string_view & to);
	const std::string_view link = "link\n";
	const std::string_view reTurn = "return\n";
	const std::string_view iF = "if\n";

	std::string byte(std::uint8_t byte);
}