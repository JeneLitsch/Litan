#pragma once
#include <span>
#include <string_view>

int run(std::string_view script_path, std::span<const std::string_view> script_args);