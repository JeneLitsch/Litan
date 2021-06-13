#pragma once
#include <string>
#include "LtncCodeObject.hxx"
namespace ltnc {
	class Inst : public ICodeObject {
	public:
		virtual std::string toString() const override;

		static Inst newl(std::uint32_t value);
		static Inst newu(std::uint32_t value);
		static Inst newi(std::uint64_t value);
		static Inst newi(std::int64_t value);
		static Inst newf(double value);

		static Inst load(std::uint32_t addr);
		static Inst store(std::uint32_t addr);

	protected:
		Inst(const std::string & string = "");
		std::string string;
	};
}