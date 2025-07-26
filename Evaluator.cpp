#include "Evaluator.h"

//Get the precedence value for an operator

int Evaluator::getPrecedence(const std::string& op) {
    if (op == "!" || op == "++" || op == "--") return 8;  // Logical not, prefix increment/decrement
    if (op == "^") return 7;  // Power/exponentiation
    if (op == "*" || op == "/" || op == "%") return 6;  // Multiplication, division, modulo
    if (op == "+" || op == "-") return 5;  // Addition, subtraction (binary)
    if (op == ">" || op == ">=" || op == "<" || op == "<=") return 4;  // Comparison
    if (op == "==" || op == "!=") return 3;  // Equality comparison
    if (op == "&&") return 2;  // Logical AND
    if (op == "||") return 1;  // Logical OR - lowest precedence
    return 0;  // Unknown operator
}

//Check if a string is a valid operator

bool Evaluator::isOperator(const std::string& op) {
    return op == "+" || op == "-" || op == "*" || op == "/" || op == "%" ||
           op == "^" || op == ">" || op == ">=" || op == "<" || op == "<=" ||
           op == "==" || op == "!=" || op == "&&" || op == "||" || op == "!" ||
           op == "++" || op == "--";
}

//Check if an operator can be used as a unary operator
 
bool Evaluator::isUnaryOperator(const std::string& op) {
    return op == "+" || op == "-" || op == "!" || op == "++" || op == "--";
}

//Perform a binary arithmetic or logical operation
int Evaluator::performOperation(int a, int b, const std::string& op) {
    if (op == "+") return a + b;  // Simple addition
    if (op == "-") return a - b;  // Simple subtraction
    if (op == "*") return a * b;  // Simple multiplication
    
    if (op == "/") {
        // Check for division by zero before performing operation
        if (b == 0) {
            throw std::runtime_error("Division by zero @ char " + std::to_string(pos));
        }
        return a / b;  // Integer division
    }
    
    if (op == "%") {
        // Check for modulo by zero (same as division by zero)
        if (b == 0) {
            throw std::runtime_error("Division by zero @ char " + std::to_string(pos));
        }
        return a % b;  // Modulo operation
    }
    
    if (op == "^") {
        // Power operation - implemented using repeated multiplication
        // Note: This assumes non-negative integer exponents
        int result = 1;
        for (int i = 0; i < b; i++) {
            result *= a;
        }
        return result;
    }
    
    if (op == ">") return (a > b) ? 1 : 0;  // Greater than comparison
    if (op == ">=") return (a >= b) ? 1 : 0;  // Greater than or equal
    if (op == "<") return (a < b) ? 1 : 0;  // Less than comparison
    if (op == "<=") return (a <= b) ? 1 : 0;  // Less than or equal
    if (op == "==") return (a == b) ? 1 : 0;  // Equality comparison
    if (op == "!=") return (a != b) ? 1 : 0;  // Not equal comparison
    
    if (op == "&&") {
        // Logical AND - treats 0 as false, non-zero as true
        return (a && b) ? 1 : 0;
    }
    
    if (op == "||") {
        // Logical OR - treats 0 as false, non-zero as true
        return (a || b) ? 1 : 0;
    }
    
    return 0;  // Unknown operator
}

//Perform a unary operation

int Evaluator::performUnaryOperation(int a, const std::string& op) {
    if (op == "+") return a;     // Unary plus - returns the value unchanged
    if (op == "-") return -a;    // Unary minus - negates the value
    if (op == "!") return (a == 0) ? 1 : 0;  // Logical NOT
    if (op == "++") return a + 1;  // Prefix increment
    if (op == "--") return a - 1;  // Prefix decrement
    
    return a;  // Unknown unary operator, return unchanged
}

//Skip whitespace characters in the expression

void Evaluator::skipWhitespace() {
    while (pos < expression.length() && std::isspace(expression[pos])) {
        pos++;  // Move past each whitespace character
    }
}

//Parse a multi-digit number from the current position

int Evaluator::parseNumber() {
    int num = 0;
    
    // Continue reading digits and building the number
    while (pos < expression.length() && std::isdigit(expression[pos])) {
        num = num * 10 + (expression[pos] - '0');  // Convert char digit to int
        pos++;  // Move to next character
    }
    
    return num;
}

//Parse the next operator from the current position

std::string Evaluator::parseOperator() {
    if (pos >= expression.length()) return "";
    
    // Check for two-character operators first
    if (pos + 1 < expression.length()) {
        std::string twoChar = expression.substr(pos, 2);
        if (twoChar == "++" || twoChar == "--" || twoChar == ">=" || 
            twoChar == "<=" || twoChar == "==" || twoChar == "!=" || 
            twoChar == "&&" || twoChar == "||") {
            pos += 2;  // Advance past the two-character operator
            return twoChar;
        }
    }
    
    // Check for single-character operators
    char c = expression[pos];
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' ||
        c == '^' || c == '>' || c == '<' || c == '!' ||
        c == '&' || c == '|') {
        pos++;  // Advance past the single-character operator
        return std::string(1, c);
    }
    
    return "";  // Not an operator
}

//Validate the expression for syntax errors

void Evaluator::validateExpression() {
    // Check for empty expression
    if (expression.empty()) {
        throw std::runtime_error("Empty expression");
    }
    
    // Check for invalid starting characters
    if (expression[0] == ')') {
        throw std::runtime_error("Expression can't start with a closing parenthesis @ char 0");
    }
    
    // Quick check for binary operators at start
    size_t tempPos = 0;
    while (tempPos < expression.length() && std::isspace(expression[tempPos])) {
        tempPos++;
    }
    if (tempPos < expression.length()) {
        std::string firstOp = "";
        if (tempPos + 1 < expression.length()) {
            std::string twoChar = expression.substr(tempPos, 2);
            if (isOperator(twoChar)) firstOp = twoChar;
        }
        if (firstOp.empty() && tempPos < expression.length()) {
            char c = expression[tempPos];
            if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' ||
                c == '^' || c == '>' || c == '<' || c == '!' ||
                c == '&' || c == '|') {
                firstOp = std::string(1, c);
            }
        }
        
        if (!firstOp.empty() && !isUnaryOperator(firstOp)) {
            throw std::runtime_error("Expression can't start with a binary operator @ char 0");
        }
    }
    
    // State tracking variables for syntax validation
    bool lastWasOperator = false;   // Track if previous non-whitespace token was operator
    bool lastWasOperand = false;    // Track if previous non-whitespace token was operand
    int parenCount = 0;             // Track parentheses balance
    
    // Temporary position for validation scanning
    size_t scanPos = 0;
    
    // Scan through the entire expression
    while (scanPos < expression.length()) {
        // Skip whitespace
        while (scanPos < expression.length() && std::isspace(expression[scanPos])) {
            scanPos++;
        }
        
        if (scanPos >= expression.length()) break;
        
        char c = expression[scanPos];
        
        if (c == '(') {
            parenCount++;              // Increment parentheses counter
            lastWasOperator = false;   // Reset state flags
            lastWasOperand = false;
            scanPos++;
        }
        else if (c == ')') {
            parenCount--;              // Decrement parentheses counter
            
            // Check for too many closing parentheses
            if (parenCount < 0) {
                throw std::runtime_error("Mismatched parentheses @ char " + std::to_string(scanPos));
            }
            
            lastWasOperator = false;   // Closing paren acts like an operand
            lastWasOperand = true;
            scanPos++;
        }
        else if (std::isdigit(c)) {
            // Check for two operands in a row (missing operator)
            if (lastWasOperand) {
                throw std::runtime_error("Two operands in a row @ char " + std::to_string(scanPos));
            }
            
            // Skip the entire number
            while (scanPos < expression.length() && std::isdigit(expression[scanPos])) {
                scanPos++;
            }
            
            lastWasOperator = false;
            lastWasOperand = true;
        }
        else {
            // Check for operator
            std::string op = "";
            
            // Check for two-character operators first
            if (scanPos + 1 < expression.length()) {
                std::string twoChar = expression.substr(scanPos, 2);
                if (isOperator(twoChar)) {
                    op = twoChar;
                    scanPos += 2;
                }
            }
            
            // If no two-character operator found, check single character
            if (op.empty()) {
                if (c == '+' || c == '-' || c == '*' || c == '/' || c == '%' ||
                    c == '^' || c == '>' || c == '<' || c == '!' ||
                    c == '&' || c == '|') {
                    op = std::string(1, c);
                    scanPos++;
                }
            }
            
            if (!op.empty()) {
                // Check for two binary operators in a row
                if (lastWasOperator && !isUnaryOperator(op)) {
                    throw std::runtime_error("Two binary operators in a row @ char " + std::to_string(scanPos - op.length()));
                }
                
                lastWasOperator = true;
                lastWasOperand = false;
            }
            else {
                // Invalid character found
                throw std::runtime_error("Invalid character @ char " + std::to_string(scanPos));
            }
        }
    }
    
    // Check for unmatched parentheses at the end
    if (parenCount != 0) {
        throw std::runtime_error("Mismatched parentheses");
    }
}

/**
 * Evaluate an infix expression string
 * Algorithm:
 * 1. Validate the expression syntax
 * 2. Scan left to right through the expression
 * 3. For operands: push onto operand stack
 * 4. For operators: handle based on precedence and associativity
 * 5. For parentheses: process enclosed expressions immediately
 * 6. Process any remaining operators
 */
int Evaluator::eval(const std::string& expr) {
    expression = expr;  // Store the expression
    pos = 0;           // Reset position to start
    
    try {
        // First, validate the entire expression for syntax errors
        validateExpression();
        
        // Two stacks for the Shunting Yard algorithm
        std::stack<int> operands;           // Stack for numeric values
        std::stack<std::string> operators;  // Stack for operators (now strings)
        
        bool expectOperand = true;    // Flag to distinguish unary vs binary operators
        
        // Main parsing loop - process each token
        while (pos < expression.length()) {
            skipWhitespace();  // Skip any whitespace
            
            // Check if we've reached the end after skipping whitespace
            if (pos >= expression.length()) break;
            
            char current = expression[pos];
            
            if (std::isdigit(current)) {
                // Found a number - parse it and push onto operand stack
                operands.push(parseNumber());
                expectOperand = false;  // Next operator should be binary
            }
            else if (current == '(') {
                // Opening parenthesis - push onto operator stack
                operators.push("(");
                pos++;
                expectOperand = true;   // Next token should be operand or unary operator
            }
            else if (current == ')') {
                // Closing parenthesis - process all operators until opening parenthesis
                while (!operators.empty() && operators.top() != "(") {
                    std::string op = operators.top();
                    operators.pop();
                    
                    // Handle unary operators (they only need one operand)
                    if (isUnaryOperator(op) && (op == "!" || op == "++" || op == "--" || 
                        (op == "+" || op == "-"))) {
                        if (operands.size() >= 1) {
                            int a = operands.top();
                            operands.pop();
                            operands.push(performUnaryOperation(a, op));
                        }
                    } else {
                        // Binary operator - needs two operands
                        if (operands.size() >= 2) {
                            int b = operands.top(); operands.pop();  // Right operand
                            int a = operands.top(); operands.pop();  // Left operand
                            operands.push(performOperation(a, b, op));
                        }
                    }
                }
                
                // Remove the opening parenthesis from operator stack
                if (!operators.empty()) {
                    operators.pop(); // Remove the "("
                }
                pos++;
                expectOperand = false;  // After closing paren, expect binary operator
            }
            else {
                // Try to parse an operator
                std::string op = parseOperator();
                
                if (!op.empty()) {
                    // Handle unary operators (when we expect an operand)
                    if (expectOperand && isUnaryOperator(op)) {
                        operators.push(op);
                        continue;  // Stay in "expect operand" state
                    }
                    
                    // Process binary operators with higher or equal precedence
                    // This maintains left-to-right evaluation for same precedence
                    while (!operators.empty() && operators.top() != "(" &&
                           getPrecedence(operators.top()) >= getPrecedence(op)) {
                        
                        std::string stackOp = operators.top();
                        operators.pop();
                        
                        // Determine if this is a unary operator
                        if (isUnaryOperator(stackOp) && (stackOp == "!" || stackOp == "++" || 
                            stackOp == "--" || stackOp == "+" || stackOp == "-")) {
                            if (operands.size() >= 1) {
                                int a = operands.top();
                                operands.pop();
                                operands.push(performUnaryOperation(a, stackOp));
                            }
                        } else {
                            // Definitely binary - needs two operands
                            if (operands.size() >= 2) {
                                int b = operands.top(); operands.pop();  // Right operand
                                int a = operands.top(); operands.pop();  // Left operand
                                operands.push(performOperation(a, b, stackOp));
                            }
                        }
                    }
                    
                    // Push current operator onto stack
                    operators.push(op);
                    expectOperand = true;   // After binary operator, expect operand
                }
                else {
                    // Skip unknown characters (should be caught by validation)
                    pos++;
                }
            }
        }
        
        // Process any remaining operators in the stack
        while (!operators.empty()) {
            std::string op = operators.top();
            operators.pop();
            
            // Handle remaining unary operators
            if (isUnaryOperator(op) && (op == "!" || op == "++" || op == "--" || 
                op == "+" || op == "-")) {
                if (operands.size() >= 1) {
                    int a = operands.top();
                    operands.pop();
                    operands.push(performUnaryOperation(a, op));
                }
            } else {
                // Handle remaining binary operators
                if (operands.size() >= 2) {
                    int b = operands.top(); operands.pop();  // Right operand
                    int a = operands.top(); operands.pop();  // Left operand
                    operands.push(performOperation(a, b, op));
                }
            }
        }
        
        // The final result should be the only item left on the operand stack
        return operands.empty() ? 0 : operands.top();
        
    } catch (const std::runtime_error& e) {
        // Re-throw any errors with their original messages
        throw;
    }
}