# Math interpreter

Build & Run

```sh
# from the project root directory
cmake -B build # configure cmake
cmake --build build # build the targets
build/math-interpreter # run the executable
```

```mermaid
classDiagram
    namespace AbstractSyntaxTree {
        class Expression {
            <<abstract>>
            +get_name()* string
            +interpret()* double
            +to_string()* string
        }

        class BinaryExpression {
            <<abstract>>
            #Expression op1
            #Expression op2
        }

        class UnaryExpression {
            <<abstract>>
            #Expression op
        }

        class AddExpression {
            +interpret() double
            +to_string() string
        }

        class SubtractExpression {
            +interpret() double
            +to_string() string
        }

        class MultiplyExpression {
            +interpret() double
            +to_string() string
        }

        class DivideExpression {
            +interpret() double
            +to_string() string
        }

        class PlusExpression {
            +interpret() double
            +to_string() string
        }

        class MinusExpression {
            +interpret() double
            +to_string() string
        }

        class Constant {
            -double value
            +interpret() double
            +to_string() string
        }

        class AssignmentExpression {
            -Expression identifier
            -Expression value
            +interpret() double
            +to_string() string
        }

        class Identifier {
            -string name
            +interpret() double
            +to_string() string
            +get_name() string
        }

    }

    class Context {
        -unorder_map variables
        +lookup() double
        +assign(double value)
    }

    class Parser {
        +parse(string expression) Expression $
    }

    Parser ..|> Expression : Builds
    Client --> Parser


    BinaryExpression --|> Expression
    UnaryExpression --|> Expression
    AddExpression --|> BinaryExpression
    SubtractExpression --|> BinaryExpression
    MultiplyExpression --|> BinaryExpression
    DivideExpression --|> BinaryExpression
    PlusExpression --|> UnaryExpression
    MinusExpression --|> UnaryExpression
    Constant --|> Expression
    AssignmentExpression --|> Expression
    Identifier --|> Expression
    AssignmentExpression ..> Context : Assign variable
    Identifier ..> Context : Evaluate variable
```
