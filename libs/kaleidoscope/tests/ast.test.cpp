#include <catch2/catch_test_macros.hpp>

#include <kaleidoscope/ast/number_expression.hpp>
#include <kaleidoscope/ast/variable_expression.hpp>
#include <kaleidoscope/ast/binary_expression.hpp>
#include <kaleidoscope/ast/function_call_expression.hpp>
#include <kaleidoscope/ast/function_prototype.hpp>
#include <kaleidoscope/ast/function_definition.hpp>

#include <memory>
#include <string>
#include <vector>

TEST_CASE("Kaleidoscope manual AST node for a number should hold proper value", "[kaleidoscope][ast]")
{
    auto expr = std::make_unique<llvm_exp::kaleidoscope::ast::number_expression>(42.0);

    REQUIRE(expr->value() == 42.0);
}   

TEST_CASE("Kaleidoscope manual AST node for a variable should hold proper name", "[kaleidoscope][ast]")
{
    auto expr = std::make_unique<llvm_exp::kaleidoscope::ast::variable_expression>("x");

    REQUIRE(expr->name() == "x");
}   

TEST_CASE("Kaleidoscope manual AST for adding two numbers should have accessible properties", "[kaleidoscope][ast]")
{
    using namespace llvm_exp::kaleidoscope;

    auto expr = std::make_unique<ast::binary_expression>('+',
        std::make_unique<ast::variable_expression>("y"),
        std::make_unique<ast::number_expression>(1.0));

    REQUIRE(expr->operation() == '+');
    REQUIRE(dynamic_cast<ast::variable_expression const *>(expr->lhs())->name() == "y");
    REQUIRE(dynamic_cast<ast::number_expression const *>(expr->rhs())->value() == 1.0);
}

TEST_CASE("Kaleidoscope manual AST function call must have accessible properties", "[kaleidoscope][ast]")
{
    using namespace llvm_exp::kaleidoscope;

    auto args = std::vector<std::unique_ptr<ast::expression>>{};
    args.emplace_back(std::make_unique<ast::variable_expression>("y"));
    args.emplace_back(std::make_unique<ast::number_expression>(1.0));

    auto expr = std::make_unique<ast::function_call_expression>("add", std::move(args));

    REQUIRE(expr->callee_name() == "add");
    REQUIRE(expr->args().size() == 2u);
    REQUIRE(dynamic_cast<ast::variable_expression const *>(expr->args()[0].get())->name() == "y");
    REQUIRE(dynamic_cast<ast::number_expression const *>(expr->args()[1].get())->value() == 1.0);
}

TEST_CASE("Kaleidoscope manual AST prototype for function 'add(x,y)' must have accessible properties", "[kaleidoscope][ast]")
{
    using namespace llvm_exp::kaleidoscope;

    auto expr = std::make_unique<ast::function_prototype>("add", std::vector<std::string>{"x", "y"});

    REQUIRE(expr->function_name() == "add");
    REQUIRE(expr->arg_names().size() == 2u);
    REQUIRE(expr->arg_names()[0] == "x");
    REQUIRE(expr->arg_names()[1] == "y");
}

TEST_CASE("Kaleidoscope manual AST definition for function 'add(x,y)' must have accessible properties", "[kaleidoscope][ast]")
{
    using namespace llvm_exp::kaleidoscope;

    auto expr = std::make_unique<ast::function_definition>(
        std::make_unique<ast::function_prototype>("add", std::vector<std::string>{"x", "y"}),
        std::make_unique<ast::binary_expression>('+',
            std::make_unique<ast::variable_expression>("x"),
            std::make_unique<ast::variable_expression>("y")));

    REQUIRE(expr->prototype()->function_name() == "add");
    REQUIRE(expr->prototype()->arg_names().size() == 2u);
    REQUIRE(expr->prototype()->arg_names()[0] == "x");
    REQUIRE(expr->prototype()->arg_names()[1] == "y");

    REQUIRE(dynamic_cast<ast::binary_expression const *>(expr->body())->operation() == '+');
    REQUIRE(dynamic_cast<ast::variable_expression const *>(dynamic_cast<ast::binary_expression const *>(expr->body())->lhs())->name() == "x");
    REQUIRE(dynamic_cast<ast::variable_expression const *>(dynamic_cast<ast::binary_expression const *>(expr->body())->rhs())->name() == "y");
}
