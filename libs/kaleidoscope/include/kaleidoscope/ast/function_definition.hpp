#pragma once

#include <memory>

#include "kaleidoscope/ast/node.hpp"
#include "kaleidoscope/ast/expression.hpp"
#include "kaleidoscope/ast/function_prototype.hpp"

namespace llvm_exp::kaleidoscope::ast
{
    class function_definition : public node
    {
    public:
        function_definition(std::unique_ptr<function_prototype> prototype,
                            std::unique_ptr<expression> body) 
        : m_prototype{std::move(prototype)},
          m_body{std::move(body)}
        {}

        virtual ~function_definition() = default;

        [[nodiscard]] function_prototype const * prototype() const noexcept { return m_prototype.get(); }
        [[nodiscard]] expression const * body() const noexcept { return m_body.get(); }

    private:
        std::unique_ptr<function_prototype> m_prototype;
        std::unique_ptr<expression> m_body;
    };
}
