#ifndef EVALUATOR_H
#define EVALUATOR_H

#include <iostream>
#include <stack>
#include <string>
#include <cctype>
#include <stdexcept>

//class Evaluator
class Evaluator {
private:
    std::string expression;  ///< The current expression being parsed
    size_t pos;             ///< Current position in the expression string
    
    //Get the precedence value for an operator
    int getPrecedence(const std::string& op);
    
    //Check if a string is a valid operator
    bool isOperator(const std::string& op);
    
    //Check if an operator can be used as a unary operator
    bool isUnaryOperator(const std::string& op);
    
    //Perform a binary arithmetic or logical operation
    int performOperation(int a, int b, const std::string& op);
    
    //Perform a unary operation
    int performUnaryOperation(int a, const std::string& op);
    
    //Skip whitespace characters in the expression
    void skipWhitespace();
    
    //Parse a multi-digit number from the current position
    int parseNumber();
    
    //Parse the next operator from the current position
    std::string parseOperator();
    
    //Validate the expression for syntax errors
    void validateExpression();

public:
    //Evaluate an infix expression string

    int eval(const std::string& expr);
};

#endif // EVALUATOR_H