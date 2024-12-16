#include <gtest/gtest.h>

#include "../src/Context.hpp"
#include "../src/Parser.hpp"
#include "../src/SyntaxError.hpp"

TEST(InterpreterTest, InvalidExpressions) {
  Context context;
  EXPECT_THROW(Parser::parse("1 + 5 abc")->interpret(context), SyntaxError);
  EXPECT_THROW(Parser::parse("a = 5 + 58 b = 35 - 4")->interpret(context),
               SyntaxError);
}

TEST(InterpreterTest, WhitespaceAgnostic) {
  Context context;
  EXPECT_EQ(Parser::parse("1+1")->interpret(context), 2);
  EXPECT_EQ(Parser::parse(" 1+1")->interpret(context), 2);
  EXPECT_EQ(Parser::parse("                  1^1")->interpret(context), 1);
  EXPECT_EQ(Parser::parse("1 / 1")->interpret(context), 1);
  EXPECT_EQ(Parser::parse("1 * 1                  ")->interpret(context), 1);
  EXPECT_EQ(Parser::parse("1    -   1")->interpret(context), 0);
}

TEST(InterpreterTest, Parenthesis) {
  Context context;
  EXPECT_THROW(Parser::parse("()")->interpret(context), SyntaxError);
  EXPECT_NO_THROW(Parser::parse("((((((((((1))))))))))")->interpret(context));
  EXPECT_THROW(Parser::parse(")(")->interpret(context), SyntaxError);
  EXPECT_THROW(Parser::parse("(")->interpret(context), SyntaxError);
  EXPECT_THROW(Parser::parse(")")->interpret(context), SyntaxError);
  EXPECT_NO_THROW(Parser::parse("((1)+((1)+(1))+(((1)+((1))+(((1)+(((1)+(1))+("
                                "1))+(1))+(1)+((1)+(1)))+(1))))")
                      ->interpret(context));
}

TEST(InterpreterTest, Assignment) {
  Context context;
  EXPECT_EQ(Parser::parse("a = 1 + 1")->interpret(context), 2);
  EXPECT_EQ(Parser::parse("a")->interpret(context), 2);

  EXPECT_THROW(Parser::parse("var")->interpret(context), std::runtime_error);

  // reassignment
  EXPECT_EQ(Parser::parse("a = 5")->interpret(context), 5);

  // multiple assignment
  EXPECT_EQ(Parser::parse("a = b = c = d = 3")->interpret(context), 3);
  EXPECT_EQ(Parser::parse("a")->interpret(context), 3);
  EXPECT_EQ(Parser::parse("b")->interpret(context), 3);
  EXPECT_EQ(Parser::parse("c")->interpret(context), 3);
  EXPECT_EQ(Parser::parse("d")->interpret(context), 3);

  // assignment to a non identifier expression
  EXPECT_THROW(Parser::parse("2 ^ 2 = 1 + 1"), SyntaxError);
}

TEST(InterpreterTest, Addition) {
  Context context;
  EXPECT_EQ(Parser::parse("5 + 3")->interpret(context), 8);
  EXPECT_THROW(Parser::parse("+")->interpret(context), SyntaxError);
  EXPECT_THROW(Parser::parse("1 +")->interpret(context), SyntaxError);
}

TEST(InterpreterTest, Subtraction) {
  Context context;
  EXPECT_EQ(Parser::parse("258 - 412")->interpret(context), -154);
}

TEST(InterpreterTest, Multiplication) {
  Context context;
  EXPECT_EQ(Parser::parse("4294967296 * 5")->interpret(context), 21474836480);
}

TEST(InterpreterTest, Division) {
  Context context;
  EXPECT_EQ(Parser::parse("-5 / -2")->interpret(context), 2.5);

  // Division by zero
  EXPECT_THROW(Parser::parse("1 / 0")->interpret(context), std::domain_error);
}

TEST(InterpreterTest, Exponential) {
  Context context;
  EXPECT_EQ(Parser::parse("2 ^ 5")->interpret(context), 32);

  // Right associativity
  EXPECT_EQ(Parser::parse("4 ^ 3 ^ 2")->interpret(context), 262144);
}

TEST(InterpreterTest, Positive) {
  Context context;
  EXPECT_EQ(Parser::parse("+379")->interpret(context), 379);
  EXPECT_EQ(Parser::parse("+-1")->interpret(context), -1);
  EXPECT_EQ(Parser::parse("++++++++++++++++++1")->interpret(context), 1);
}

TEST(InterpreterTest, Negative) {
  Context context;
  EXPECT_EQ(Parser::parse("-1")->interpret(context), -1);
  EXPECT_EQ(Parser::parse("--1")->interpret(context), 1);
  EXPECT_EQ(Parser::parse("---1")->interpret(context), -1);
  EXPECT_EQ(Parser::parse("----1")->interpret(context), 1);
}

TEST(InterpreterTest, Precedence) {
  Context context;
  EXPECT_EQ(Parser::parse("3 * (18 - 26) ^ 2 * 4 --1")->interpret(context),
            769);
  EXPECT_EQ(
      Parser::parse("128^5 + 1 + 2^3 - 3 * 4 / 1 - 128^5")->interpret(context),
      -3);
  EXPECT_EQ(
      Parser::parse(
          "(-5 + 2)^(3 - 1) - 3 ^ (1 + 2 - 7 * 2^5) * (128 - 5 ^ -(1 / 3))")
          ->interpret(context),
      9);
  Parser::parse("z=y=x=12-5*2")->interpret(context);
  EXPECT_EQ(Parser::parse("2*-12^(y*2)-25/11*1/z^5")->interpret(context),
            41471.928977272728);
}
