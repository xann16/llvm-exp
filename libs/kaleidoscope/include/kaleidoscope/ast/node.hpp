#pragma once

namespace llvm_exp::kaleidoscope::ast
{
    class node
    {
    public:
        virtual ~node() = default;

    protected:
        node() noexcept = default;
    };
}
