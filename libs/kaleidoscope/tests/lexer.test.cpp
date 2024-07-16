#include <catch2/catch_test_macros.hpp>

#include <kaleidoscope/lexer.hpp>

#include <sstream>
#include <string>

TEST_CASE("Kaleidoscope lexer should handle empty string", "[kaleidoscope][lexer]")
{
    auto iss = std::istringstream{""};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);

    REQUIRE(t == llvm_exp::kaleidoscope::token_t::end_of_file);
}

TEST_CASE("Kaleidoscope lexer should grcefully handle lexing past end of file", "[kaleidoscope][lexer]")
{
    auto iss = std::istringstream{""};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);
    REQUIRE(t == llvm_exp::kaleidoscope::token_t::end_of_file);

    t = l.next_token(iss);
    REQUIRE(t == llvm_exp::kaleidoscope::token_t::end_of_file);

    t = l.next_token(iss);
    REQUIRE(t == llvm_exp::kaleidoscope::token_t::end_of_file);

}

TEST_CASE("Kaleidoscope lexer should handle whitespaces", "[kaleidoscope][lexer]")
{
    auto iss = std::istringstream{"               "};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);

    REQUIRE(t == llvm_exp::kaleidoscope::token_t::end_of_file);
}

TEST_CASE("Kaleidoscope lexer should handle comment only", "[kaleidoscope][lexer]")
{
    auto iss = std::istringstream{"   # This is a comment!    "};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);

    REQUIRE(t == llvm_exp::kaleidoscope::token_t::end_of_file);
}

TEST_CASE("Kaleidoscope lexer should handle def keyword", "[kaleidoscope][lexer][def]")
{
    auto iss = std::istringstream{"def"};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);

    REQUIRE(t == llvm_exp::kaleidoscope::token_t::kw_def);

    // extra end of file verification
    REQUIRE(l.next_token(iss) == llvm_exp::kaleidoscope::token_t::end_of_file);
}

TEST_CASE("Kaleidoscope lexer should handle extern keyword", "[kaleidoscope][lexer][extern]")
{
    auto iss = std::istringstream{"extern"};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);

    REQUIRE(t == llvm_exp::kaleidoscope::token_t::kw_extern);

    // extra end of file verification
    REQUIRE(l.next_token(iss) == llvm_exp::kaleidoscope::token_t::end_of_file);
}

TEST_CASE("Kaleidoscope lexer should handle addition operator", "[kaleidoscope][lexer][operator]")
{
    auto iss = std::istringstream{"+"};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);

    REQUIRE(t == llvm_exp::kaleidoscope::token_t::operator_);
    REQUIRE(l.current_operator() == '+');


    // extra end of file verification
    REQUIRE(l.next_token(iss) == llvm_exp::kaleidoscope::token_t::end_of_file);
}

TEST_CASE("Kaleidoscope lexer should handle subtraction operator", "[kaleidoscope][lexer][operator]")
{
    auto iss = std::istringstream{"-"};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);

    REQUIRE(t == llvm_exp::kaleidoscope::token_t::operator_);
    REQUIRE(l.current_operator() == '-');

    // extra end of file verification
    REQUIRE(l.next_token(iss) == llvm_exp::kaleidoscope::token_t::end_of_file);
}

TEST_CASE("Kaleidoscope lexer should handle multiplication operator", "[kaleidoscope][lexer][operator]")
{
    auto iss = std::istringstream{"*"};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);

    REQUIRE(t == llvm_exp::kaleidoscope::token_t::operator_);
    REQUIRE(l.current_operator() == '*');

    // extra end of file verification
    REQUIRE(l.next_token(iss) == llvm_exp::kaleidoscope::token_t::end_of_file);
}

TEST_CASE("Kaleidoscope lexer should handle division operator", "[kaleidoscope][lexer][operator]")
{
    auto iss = std::istringstream{"/"};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);

    REQUIRE(t == llvm_exp::kaleidoscope::token_t::operator_);
    REQUIRE(l.current_operator() == '/');

    // extra end of file verification
    REQUIRE(l.next_token(iss) == llvm_exp::kaleidoscope::token_t::end_of_file);
}

TEST_CASE("Kaleidoscope lexer should handle equality operator", "[kaleidoscope][lexer][operator]")
{
    auto iss = std::istringstream{"="};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);

    REQUIRE(t == llvm_exp::kaleidoscope::token_t::operator_);
    REQUIRE(l.current_operator() == '=');

    // extra end of file verification
    REQUIRE(l.next_token(iss) == llvm_exp::kaleidoscope::token_t::end_of_file);
}

TEST_CASE("TODO - Kaleidoscope lexer should fail on unsupported operators", "[kaleidoscope][lexer][operator][todo]")
{
    SKIP();

    /*
    auto iss = std::istringstream{"?"};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);

    REQUIRE(t == llvm_exp::kaleidoscope::token_t::invalid);
    */
}

TEST_CASE("Kaleidoscope lexer should handle integers", "[kaleidoscope][lexer][operator]")
{
    auto iss = std::istringstream{"42"};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);

    REQUIRE(t == llvm_exp::kaleidoscope::token_t::num_literal);
    REQUIRE(l.current_num_literal() == 42.0);

    // extra end of file verification
    REQUIRE(l.next_token(iss) == llvm_exp::kaleidoscope::token_t::end_of_file);
}

TEST_CASE("Kaleidoscope lexer should handle integer literals", "[kaleidoscope][lexer][num_literal]")
{
    auto iss = std::istringstream{"42"};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);

    REQUIRE(t == llvm_exp::kaleidoscope::token_t::num_literal);
    REQUIRE(l.current_num_literal() == 42.0);

    // extra end of file verification
    REQUIRE(l.next_token(iss) == llvm_exp::kaleidoscope::token_t::end_of_file);
}

TEST_CASE("Kaleidoscope lexer should handle floating-point literals", "[kaleidoscope][lexer][num_literal]")
{
    auto iss = std::istringstream{"12345.67890"};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);

    REQUIRE(t == llvm_exp::kaleidoscope::token_t::num_literal);
    REQUIRE(l.current_num_literal() == 12345.67890);

    // extra end of file verification
    REQUIRE(l.next_token(iss) == llvm_exp::kaleidoscope::token_t::end_of_file);
}

TEST_CASE("Kaleidoscope lexer should handle fractional literals without leading zero", "[kaleidoscope][lexer][num_literal]")
{
    auto iss = std::istringstream{".369"};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);

    REQUIRE(t == llvm_exp::kaleidoscope::token_t::num_literal);
    REQUIRE(l.current_num_literal() == 0.369);

    // extra end of file verification
    REQUIRE(l.next_token(iss) == llvm_exp::kaleidoscope::token_t::end_of_file);
}

TEST_CASE("TODO - Kaleidoscope lexer should handle numeric literals in scientific notation", "[kaleidoscope][lexer][num_literal][todo]")
{
    SKIP();

    /*
    auto iss = std::istringstream{"1e4"};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);

    REQUIRE(t == llvm_exp::kaleidoscope::token_t::num_literal);
    REQUIRE(l.current_num_literal() == 1e4);

    // extra end of file verification
    REQUIRE(l.next_token(iss) == llvm_exp::kaleidoscope::token_t::end_of_file);
    */
}

TEST_CASE("TODO - Kaleidoscope lexer should handle numeric literals in scientific notation with negative exponent", "[kaleidoscope][lexer][num_literal][todo]")
{
    SKIP();

    /*
    auto iss = std::istringstream{"1e-4"};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);

    REQUIRE(t == llvm_exp::kaleidoscope::token_t::num_literal);
    REQUIRE(l.current_num_literal() == 1e-4);

    // extra end of file verification
    REQUIRE(l.next_token(iss) == llvm_exp::kaleidoscope::token_t::end_of_file);
    */
}

TEST_CASE("Kaleidoscope lexer should handle alpha identifiers", "[kaleidoscope][lexer][identifier]")
{
    auto iss = std::istringstream{"identifier"};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);

    REQUIRE(t == llvm_exp::kaleidoscope::token_t::identifier);
    REQUIRE(l.current_identifier() == "identifier");

    // extra end of file verification
    REQUIRE(l.next_token(iss) == llvm_exp::kaleidoscope::token_t::end_of_file);
}

TEST_CASE("Kaleidoscope lexer should bs case-sensitive with identifiers", "[kaleidoscope][lexer][identifier]")
{
    auto iss = std::istringstream{"Def"};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);

    REQUIRE(t == llvm_exp::kaleidoscope::token_t::identifier);
    REQUIRE(l.current_identifier() == "Def");

    // extra end of file verification
    REQUIRE(l.next_token(iss) == llvm_exp::kaleidoscope::token_t::end_of_file);
}

TEST_CASE("Kaleidoscope lexer should handle alphanumeric identifiers", "[kaleidoscope][lexer][identifier]")
{
    auto iss = std::istringstream{"identifier42"};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);

    REQUIRE(t == llvm_exp::kaleidoscope::token_t::identifier);
    REQUIRE(l.current_identifier() == "identifier42");

    // extra end of file verification
    REQUIRE(l.next_token(iss) == llvm_exp::kaleidoscope::token_t::end_of_file);
}

TEST_CASE("TODO - Kaleidoscope lexer should underscores in identifiers", "[kaleidoscope][lexer][identifier][todo]")
{
    SKIP();

    /*
    auto iss = std::istringstream{"identifier_with_underscores"};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);

    REQUIRE(t == llvm_exp::kaleidoscope::token_t::identifier);
    REQUIRE(l.current_identifier() == "identifier_with_underscores");

    // extra end of file verification
    REQUIRE(l.next_token(iss) == llvm_exp::kaleidoscope::token_t::end_of_file);
    */
}

TEST_CASE("Kaleidoscope lexer should handle identifiers directly following numbers", "[kaleidoscope][lexer][identifier][num_literal]")
{
    auto iss = std::istringstream{"4x"};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);
    REQUIRE(t == llvm_exp::kaleidoscope::token_t::num_literal);
    REQUIRE(l.current_num_literal() == 4.0);

    t = l.next_token(iss);
    REQUIRE(t == llvm_exp::kaleidoscope::token_t::identifier);
    REQUIRE(l.current_identifier() == "x");

    // extra end of file verification
    REQUIRE(l.next_token(iss) == llvm_exp::kaleidoscope::token_t::end_of_file);
}

TEST_CASE("Kaleidoscope lexer should handle numbers preceded by unary minus", "[kaleidoscope][lexer][operator][num_literal]")
{
    auto iss = std::istringstream{"-17"};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);
    REQUIRE(t == llvm_exp::kaleidoscope::token_t::operator_);
    REQUIRE(l.current_operator() == '-');

    t = l.next_token(iss);
    REQUIRE(t == llvm_exp::kaleidoscope::token_t::num_literal);
    REQUIRE(l.current_num_literal() == 17.0);

    // extra end of file verification
    REQUIRE(l.next_token(iss) == llvm_exp::kaleidoscope::token_t::end_of_file);
}

TEST_CASE("Kaleidoscope lexer shaold handle basic arithmetic expression", "[kaleidoscope][lexer][operator][num_literal][identifier]")
{
    auto iss = std::istringstream{"x=y+7"};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);
    REQUIRE(t == llvm_exp::kaleidoscope::token_t::identifier);
    REQUIRE(l.current_identifier() == "x");

    t = l.next_token(iss);
    REQUIRE(t == llvm_exp::kaleidoscope::token_t::operator_);
    REQUIRE(l.current_operator() == '=');

    t = l.next_token(iss);
    REQUIRE(t == llvm_exp::kaleidoscope::token_t::identifier);
    REQUIRE(l.current_identifier() == "y");

    t = l.next_token(iss);
    REQUIRE(t == llvm_exp::kaleidoscope::token_t::operator_);
    REQUIRE(l.current_operator() == '+');

    t = l.next_token(iss);
    REQUIRE(t == llvm_exp::kaleidoscope::token_t::num_literal);
    REQUIRE(l.current_num_literal() == 7.0);

    // extra end of file verification
    REQUIRE(l.next_token(iss) == llvm_exp::kaleidoscope::token_t::end_of_file);
}

TEST_CASE("Kaleidoscope lexer should handle parenthesized arithmetic expression", "[kaleidoscope][lexer][operator][num_literal][identifier]")
{
    auto iss = std::istringstream{"(4 - alpha) / beta"};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);
    REQUIRE(t == llvm_exp::kaleidoscope::token_t::operator_);
    REQUIRE(l.current_operator() == '(');

    t = l.next_token(iss);
    REQUIRE(t == llvm_exp::kaleidoscope::token_t::num_literal);
    REQUIRE(l.current_num_literal() == 4.0);

    t = l.next_token(iss);
    REQUIRE(t == llvm_exp::kaleidoscope::token_t::operator_);
    REQUIRE(l.current_operator() == '-');

    t = l.next_token(iss);
    REQUIRE(t == llvm_exp::kaleidoscope::token_t::identifier);
    REQUIRE(l.current_identifier() == "alpha");

    t = l.next_token(iss);
    REQUIRE(t == llvm_exp::kaleidoscope::token_t::operator_);
    REQUIRE(l.current_operator() == ')');

    t = l.next_token(iss);
    REQUIRE(t == llvm_exp::kaleidoscope::token_t::operator_);
    REQUIRE(l.current_operator() == '/');

    t = l.next_token(iss);
    REQUIRE(t == llvm_exp::kaleidoscope::token_t::identifier);
    REQUIRE(l.current_identifier() == "beta");

    // extra end of file verification
    REQUIRE(l.next_token(iss) == llvm_exp::kaleidoscope::token_t::end_of_file);
}

TEST_CASE("Kaleidoscope lexer should handle basic function definition", "[kaleidoscope][lexer][operator][identifier][num_literal]")
{
    auto iss = std::istringstream{"def getAnswer()\n    42"};
    auto l = llvm_exp::kaleidoscope::lexer{};

    auto t = l.next_token(iss);
    REQUIRE(t == llvm_exp::kaleidoscope::token_t::kw_def);

    t = l.next_token(iss);
    REQUIRE(t == llvm_exp::kaleidoscope::token_t::identifier);
    REQUIRE(l.current_identifier() == "getAnswer");

    t = l.next_token(iss);
    REQUIRE(t == llvm_exp::kaleidoscope::token_t::operator_);
    REQUIRE(l.current_operator() == '(');

    t = l.next_token(iss);
    REQUIRE(t == llvm_exp::kaleidoscope::token_t::operator_);
    REQUIRE(l.current_operator() == ')');

    t = l.next_token(iss);
    REQUIRE(t == llvm_exp::kaleidoscope::token_t::num_literal);
    REQUIRE(l.current_num_literal() == 42.0);

    // extra end of file verification
    REQUIRE(l.next_token(iss) == llvm_exp::kaleidoscope::token_t::end_of_file);
}
