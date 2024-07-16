#pragma once

#include <memory>

#include "kaleidoscope/ast/expression.hpp"

namespace llvm_exp::kaleidoscope::ast
{
    class binary_expression : public expression
    {
    public:
        binary_expression(char operation,
                          std::unique_ptr<expression> lhs,
                          std::unique_ptr<expression> rhs) 
        : m_operation{operation},
          m_lhs{std::move(lhs)},
          m_rhs{std::move(rhs)}
        {}

        virtual ~binary_expression() = default;

        [[nodiscard]] char operation() const noexcept { return m_operation; }
        [[nodiscard]] expression const * lhs() const noexcept { return m_lhs.get(); }
        [[nodiscard]] expression const * rhs() const noexcept { return m_rhs.get(); }

    private:
        char m_operation = '\0';
        std::unique_ptr<expression> m_lhs;
        std::unique_ptr<expression> m_rhs;
    };
}
