#pragma once
#include <string>
#include "LtncCodeObject.hxx"
namespace ltn::c {
	class Inst : public ICodeObject {
	public:
		virtual std::string toString() const override;

		static Inst stackalloc(std::uint32_t count);
		
		static Inst call(const std::string & jumpMark);

		static Inst newl(std::uint32_t value);
		static Inst newu(std::uint32_t value);
		static Inst newi(std::uint64_t value);
		static Inst newi(std::int64_t value);
		static Inst newf(double value);

		static Inst got0(const std::string & markStr);
		static Inst mark(const std::string & markStr);


		static Inst load(std::uint32_t addr);
		static Inst store(std::uint32_t addr);
		
		static Inst allocateStruct(std::size_t size);

		static Inst stringData(const std::string & str);

		static Inst structRead(std::uint32_t addr);
		static Inst structWrite(std::uint32_t addr);

	protected:
		Inst(const std::string & string = "");
		std::string string;
	};
}