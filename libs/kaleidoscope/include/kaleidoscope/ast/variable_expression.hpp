#pragma once

#include <string>

#include "kaleidoscope/ast/expression.hpp"

namespace llvm_exp::kaleidoscope::ast
{
    class variable_expression : public expression
    {
    public:
        explicit variable_expression(std::string name) : m_name{std::move(name)} {}

        virtual ~variable_expression() = default;

        [[nodiscard]] std::string const& name() const noexcept { return m_name; }

    private:
        std::string m_name;
    };
}
