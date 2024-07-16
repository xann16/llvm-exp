#pragma once

#include <string>
#include <vector>

#include "kaleidoscope/ast/node.hpp"

namespace llvm_exp::kaleidoscope::ast
{
    class function_prototype : public node
    {
    public:
        function_prototype(std::string function_name,
                           std::vector<std::string> arg_names) 
        : m_function_name{std::move(function_name)},
          m_arg_names{std::move(arg_names)}
        {}

        virtual ~function_prototype() = default;

        [[nodiscard]] std::string const& function_name() const noexcept { return m_function_name; }
        [[nodiscard]] std::vector<std::string> const& arg_names() const noexcept { return m_arg_names; }

    private:
        std::string m_function_name;
        std::vector<std::string> m_arg_names;
    };
}
