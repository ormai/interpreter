cmake_minimum_required(VERSION 3.12)
project(interpreter CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(${PROJECT_NAME} ${SOURCES}
        src/AST/AddExpression.hpp
        src/AST/Expression.hpp
        src/AST/ExponentialExpression.hpp
        src/AST/BinaryExpression.hpp
        src/AST/Constant.hpp
        src/Context.hpp
        src/AST/AssignmentExpression.hpp
        src/AST/DivideExpression.hpp
        src/AST/Identifier.hpp
        src/AST/MinusExpression.hpp
        src/AST/MultiplyExpression.hpp
        src/Parser.hpp
        src/AST/PlusExpression.hpp
        src/AST/SubtractExpression.hpp
        src/AST/UnaryExpression.hpp
        src/Color.hpp
        src/SyntaxError.hpp
        src/main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

# Enable warnings
if (MSVC)
    target_compile_options(${PROJECT_NAME} PRIVATE /W4)
else ()
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -Wpedantic)
endif ()

# Test
find_package(GTest REQUIRED)

add_executable(tests test/Parser.cpp)
target_link_libraries(tests GTest::GTest GTest::Main)

add_test(interpreter tests COMMAND $<TARGET_FILE:tests>)

enable_testing()
