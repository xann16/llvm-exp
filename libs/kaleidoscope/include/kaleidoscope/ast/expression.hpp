#pragma once

#include "kaleidoscope/ast/node.hpp"

namespace llvm_exp::kaleidoscope::ast
{
    class expression : public node
    {
    public:
        virtual ~expression() = default;

    protected:
        expression() noexcept = default;
    };
}
