#include "Evaluator.h"

/**
 * Main function for interactive expression evaluation
 * This program provides an interactive interface for users to enter
 * mathematical expressions and see their evaluated results. It continues
 * to prompt for expressions until the user chooses to quit.
 *
 * Supported features:
 * - Arithmetic operators: +, -, *, /, %, ^
 * - Comparison operators: >, <, =
 * - Logical operators: &&, ||, !
 * - Parentheses for grouping: ()
 * - Unary operators: +, -, !
 */
int main() {
    // Create an instance of the Evaluator class
    Evaluator eval;

    // Display welcome message and instructions
    std::cout << "===============================================" << std::endl;
    std::cout << "    Infix Expression Evaluator" << std::endl;
    std::cout << "===============================================" << std::endl;
    std::cout << std::endl;

    // Display supported operators and their precedence
    std::cout << "Supported operators (in precedence order):" << std::endl;
    std::cout << "  ! //logical not           - precedence 8" << std::endl;
    std::cout << "  ++ //prefix increment     - precedence 8" << std::endl;
    std::cout << "  -- //prefix decrement     - precedence 8" << std::endl;
    std::cout << "  - //negative              - precedence 8" << std::endl;
    std::cout << "  ^ //power                 - precedence 7" << std::endl;
    std::cout << "  *, /, % //arithmetic      - precedence 6" << std::endl;
    std::cout << "  +, - //arithmetic         - precedence 5" << std::endl;
    std::cout << "  >, >=, <, <= //comparison - precedence 4" << std::endl;
    std::cout << "  ==, != //equality comparison - precedence 3" << std::endl;
    std::cout << "  && //logical and          - precedence 2" << std::endl;
    std::cout << "  || //logical or           - precedence 1" << std::endl;
    std::cout << "  () //parentheses for grouping" << std::endl;
    std::cout << std::endl;

    // Display example expressions
    std::cout << "Example expressions:" << std::endl;
    std::cout << "  1+2*3          -> 7" << std::endl;
    std::cout << "  2+2*2*3        -> 14" << std::endl;
    std::cout << "  1==2           -> 0 //or false if the type is bool" << std::endl;
    std::cout << "  1+3 > 2        -> 1 //or true if the type is bool" << std::endl;
    std::cout << "  (4>=4) && 0    -> 0 //or false if the type is bool" << std::endl;
    std::cout << "  (1+2)*3        -> 9" << std::endl;
    std::cout << "  +++2-5*(3^2)   -> -41" << std::endl;
    std::cout << std::endl;

    return 0;  // Program completed successfully
}