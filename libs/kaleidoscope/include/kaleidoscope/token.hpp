#pragma once

namespace llvm_exp::kaleidoscope
{
    enum class token_t
    {
        invalid,        
        end_of_file,

        identifier,
        operator_,
        num_literal,

        // keywords
        kw_def,
        kw_extern
    };
}
