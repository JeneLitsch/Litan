#pragma once
#include <string>

namespace ltn::c::compile::inst {
	std::string comment(std::string msg);
	std::string jumpmark(const std::string_view id);
	const std::string_view r3turn = "return\n";
	const std::string_view error = "error\n";
	
	const std::string_view addi = "addi";
	const std::string_view subi = "subi";
	const std::string_view mlti = "mlti";
	const std::string_view divi = "divi";
	const std::string_view modi = "modi";
	const std::string_view smli = "smli";
	const std::string_view bgri = "bgri";
	const std::string_view smleqli = "smleqli";
	const std::string_view bgreqli = "bgreqli";
	const std::string_view eqli = "eqli";
	const std::string_view ueqli = "ueqli";

	const std::string_view addf = "addf";
	const std::string_view subf = "subf";
	const std::string_view mltf = "mltf";
	const std::string_view divf = "divf";
	const std::string_view modf = "modf";
	const std::string_view smlf = "smlf";
	const std::string_view bgrf = "bgrf";
	const std::string_view smleqlf = "smleqlf";
	const std::string_view bgreqlf = "bgreqlf";
	const std::string_view eqlf = "eqlf";
	const std::string_view ueqlf = "ueqlf";

}