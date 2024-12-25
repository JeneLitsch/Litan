#pragma once
#include <fstream>
#include <filesystem>

std::ofstream open_file(const std::filesystem::path & path, std::ios::openmode openmode);
