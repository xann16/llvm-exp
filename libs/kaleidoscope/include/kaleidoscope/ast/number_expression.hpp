#pragma once

#include "kaleidoscope/ast/expression.hpp"

namespace llvm_exp::kaleidoscope::ast
{
    class number_expression : public expression
    {
    public:
        explicit number_expression(double value) : m_value{value} {}

        virtual ~number_expression() = default;

        [[nodiscard]] double value() const noexcept { return m_value; }

    private:
        double m_value = 0.0;
    };
}
