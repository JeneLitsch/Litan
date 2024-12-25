#include "AST.hxx"

namespace ltn::c::ast {
    template<typename T>
    void merge_std_vectors(std::vector<T> & exisiting, std::vector<T> new_data) {
        for(auto & elem : new_data) {
            exisiting.push_back(std::move(elem));
        }
    }

    void merge(Program & ast, Program addition) {
        merge_std_vectors(ast.definitions, std::move(addition.definitions));
        merge_std_vectors(ast.enums,       std::move(addition.enums));
        merge_std_vectors(ast.functions,   std::move(addition.functions));
        merge_std_vectors(ast.globals,     std::move(addition.globals));
    }


	Program & operator+=(Program & ast, Program addition) {
        merge(ast, std::move(addition));
        return ast;
    }
}
