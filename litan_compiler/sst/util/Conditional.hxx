#pragma once
#include "litan_compiler/sst/SST.hxx"

namespace ltn::c::sst {
    template<typename Node>
    struct Conditional : Node {
        using Node::Node;
        using node_ptr = std::unique_ptr<Node>;

        void add_case(expr_ptr cond, node_ptr body) {
            this->cases.push_back(std::make_tuple(std::move(cond), std::move(body)));
        }
        
        void set_else(node_ptr body) {
            this->else_branch = std::move(body);
        }

        std::vector<std::tuple<expr_ptr, node_ptr>> cases;
        node_ptr else_branch;
    };
}