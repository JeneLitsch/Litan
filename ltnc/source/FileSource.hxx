#pragma once
#include "Source.hxx"
#include <filesystem>

namespace ltn::c {
	class FileSource : public Source {
	public:
		FileSource(std::filesystem::path path);
		virtual std::unique_ptr<std::istream> make_istream() const override;
		virtual std::string get_name() const override;
		virtual std::string get_full_name() const override;
	private:
		std::filesystem::path path;
	};
}