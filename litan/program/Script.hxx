#pragma once
#include "ByteCode.hxx"
#include "TokenPackage.hxx"
namespace ltn {

	class Script {
		public:
			static Script load(const std::string & fileName);
			static Script parse(const std::string & source);

			Script(const std::vector<TokenPackage> & commands) : commands(commands) {}
			inline const std::vector<TokenPackage> & getCommands() const{
				return this->commands;
			}
		private:
			std::vector<TokenPackage> commands;
	};



}