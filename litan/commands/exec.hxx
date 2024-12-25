#pragma once
#include <span>
#include <string_view>

int exec(std::string_view bytecode_path, std::span<const std::string_view> script_args);