#pragma once

#include <memory>
#include <string>
#include <vector>

#include "kaleidoscope/ast/expression.hpp"

namespace llvm_exp::kaleidoscope::ast
{
    class function_call_expression : public expression
    {
    public:
        explicit function_call_expression(std::string callee_name,
                                          std::vector<std::unique_ptr<expression>> args) 
        : m_callee_name{std::move(callee_name)},
          m_args{std::move(args)}
        {}

        virtual ~function_call_expression() = default;

        [[nodiscard]] std::string const& callee_name() const noexcept { return m_callee_name; }
        [[nodiscard]] std::vector<std::unique_ptr<expression>> const& args() const noexcept { return m_args; }

    private:
        std::string m_callee_name;
        std::vector<std::unique_ptr<expression>> m_args;
    };
}
