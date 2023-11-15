#pragma once
#include <string>
#include <vector>
#include "ltnc/sst/types.hxx"
#include "ltnc/sst/Node.hxx"

namespace ltn::c::sst::misc {
	struct Except final : public Node {
		Except(const std::string & errorname, stmt_ptr body);
		virtual ~Except();
		stmt_ptr body;
		std::string errorname;
	};

	std::unique_ptr<Except> except(const std::string & errorname, stmt_ptr body);
}