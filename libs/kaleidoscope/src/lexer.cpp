#include "kaleidoscope/lexer.hpp"

namespace llvm_exp::kaleidoscope
{
    token_t lexer::next_token(std::istream& input)
    {
        // skip all whitespaces
        while (std::isspace(m_last_char)) m_last_char = input.get();

        // detect and read identifier or keyword
        if (std::isalpha(m_last_char))
        {
            m_current_identifier = static_cast<char>(m_last_char);
            while (std::isalnum(m_last_char = input.get()))
            {
                m_current_identifier += static_cast<char>(m_last_char);
            }

            if (m_current_identifier == "def") return token_t::kw_def;
            else if (m_current_identifier == "extern") return token_t::kw_extern;
            else return token_t::identifier;
        }

        // detect numerical literal
        if (std::isdigit(m_last_char) || m_last_char == '.')
        {
            auto num_str = std::string{};
            do
            {
                num_str += static_cast<char>(m_last_char);
                m_last_char = input.get();
            } while (std::isdigit(m_last_char) || m_last_char == '.');

            // TODO: consider improved error handling on double parsing
            m_current_num_literal = std::strtod(num_str.c_str(), nullptr);
            return token_t::num_literal;
        }

        // detect comment - skip everything until end of line
        if (m_last_char == '#')
        {
            do m_last_char = input.get(); 
            while (m_last_char != EOF && m_last_char != '\n' && m_last_char != '\r');

            // continue tokenizing if EOF is not encountered
            if (m_last_char != EOF) return next_token(input);
        }

        // detect end of file
        if (m_last_char == EOF) return token_t::end_of_file;

        // interpret any other character as operator
        // TODO: handle invalid characters as well
        m_current_operator = static_cast<char>(m_last_char);
        m_last_char = input.get();
        return token_t::operator_;
    }
}
