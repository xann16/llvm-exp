#pragma once

#include <string>
#include <istream>

#include "kaleidoscope/token.hpp"

namespace llvm_exp::kaleidoscope
{
    class lexer
    {
    public:
        [[nodiscard]] std::string const& current_identifier() const noexcept { return m_current_identifier; }
        [[nodiscard]] double current_num_literal() const noexcept { return m_current_num_literal; }
        [[nodiscard]] char current_operator() const noexcept { return m_current_operator; }

        token_t next_token(std::istream& input);

    //private:


    private:
        std::string m_current_identifier;
        double m_current_num_literal{};
        int m_last_char = ' ';
        char m_current_operator{};
    };

}
