#include <catch2/catch_test_macros.hpp>
#include <kaleidoscope/sample.hpp>

TEST_CASE("Sample unit test", "[sample]")
{
    REQUIRE(llvm_exp::kaleidoscope::answer() == 42);
}
