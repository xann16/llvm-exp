project(
    kaleidoscope
    LANGUAGES CXX
)

set(HEADERS
    include/kaleidoscope/ast/node.hpp
    include/kaleidoscope/ast/expression.hpp
    include/kaleidoscope/ast/number_expression.hpp
    include/kaleidoscope/ast/variable_expression.hpp
    include/kaleidoscope/ast/binary_expression.hpp
    include/kaleidoscope/ast/function_call_expression.hpp
    include/kaleidoscope/ast/function_prototype.hpp
    include/kaleidoscope/ast/function_definition.hpp
    include/kaleidoscope/lexer.hpp
    include/kaleidoscope/token.hpp
)
set(SOURCES
    src/ast/node.cpp
    src/ast/expression.cpp
    src/ast/number_expression.cpp
    src/ast/variable_expression.cpp
    src/ast/binary_expression.cpp
    src/ast/function_call_expression.cpp
    src/ast/function_prototype.cpp
    src/ast/function_definition.cpp
    src/lexer.cpp
    src/token.cpp
)
set(TESTS
    tests/lexer.test.cpp
    tests/ast.test.cpp
)

add_library(${PROJECT_NAME}
    STATIC
    ${HEADERS}
    ${SOURCES}
)
add_library(${CMAKE_PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_BINARY_DIR}
)

target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_20)

if (BUILD_TESTING)

    add_executable(${PROJECT_NAME}-unit-tests
        ${TESTS}
    )

    target_link_libraries(${PROJECT_NAME}-unit-tests
        PRIVATE
            ${PROJECT_NAME}
            Catch2::Catch2WithMain    
    )

    target_compile_options(${PROJECT_NAME}-unit-tests
        PRIVATE
            "-Wno-float-equal"
    )

    catch_discover_tests(${PROJECT_NAME}-unit-tests
        PROPERTIES
            SKIP_RETURN_CODE 4    
    )

endif()