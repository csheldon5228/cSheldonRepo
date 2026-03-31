#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <cctype>

#include "ArrayStack.h"

using namespace std;

// Token

struct Token {
    string value;   // number, operator, or parenthesis
};

// Tokenizer

vector<Token> tokenize(const string& line) {
    vector<Token> tokens;
    int i = 0;
    string str = "";
    Token t;
    while (i < line.length()) {
        if (!(isspace(line.at(i)))) {
            str += line.substr(i,1);
        }
        else {
            t = {str};
            tokens.push_back(t);
            str = "";
        }
        i++;
    }
    t = {str};
    tokens.push_back(t);

    return tokens;
}

// Helpers

bool isValidExpression(const vector<Token>& tokens) {

    int countParens = 0;
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i].value == "(") {
            countParens++;
        }
        if (tokens[i].value == ")") {
            countParens--;
        }
    }

    if (tokens.empty() || tokens.size() < 3 ||
        tokens.size() % 2 == 0 || countParens != 0) {
        return false;
    }
    return true;
}

int hasParens(const vector<Token>& tokens) {
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i].value == "(") {
            return i;
        }
    }
    return -1;
}

bool isOperator(const string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

int precedence(const string& op) {

    if (op == "+" || op == "-") {
        return 1;
    }
    else if (op == "*" || op == "/") {
        return 2;
    }
    else if (op == "(") {
        return 3;
    }
    else if (op == ")") {
        return 4;
    }
    else { // is num
        return -1;
    }
}

// Printing

void printTokens(const vector<Token>& tokens) {
    for (int i = 0; i < tokens.size(); i++) {
        printf("%s ", tokens[i].value.c_str());
    }
    cout << endl;
}

// Detection

bool isValidPostfix(const vector<Token>& tokens) {

    if (!(isValidExpression(tokens)) && !(hasParens(tokens))) {
        return false;
    }

    int countOps = 0;
    for (int i = 0; i < tokens.size(); i++) {
        if (isOperator(tokens[i].value)) {
            countOps++;
        }
        else {
            countOps--;
        }
    }

    if (!(isOperator(tokens[0].value)) && !(isOperator(tokens[1].value)) &&
        isOperator(tokens.back().value) && countOps == -1) {
        return true;
    }

    return false;
}

bool isValidInfix(const vector<Token>& tokens) {

    if (!isValidExpression(tokens)) {
        return false;
    }

    int parens = 0;
    for (int i = 0; i < tokens.size(); i++) {

        if (tokens[i].value == "(" || tokens[i].value == ")") {
            parens++;
        }
        else if (parens % 2 == 0) { // even, or "normal" (not shifted from parens)
            if (i % 2 == 0 && isOperator(tokens[i].value)) { // checks if the element is an op, which it should not
                return false;
            }
            if (i % 2 == 1 && !(isOperator(tokens[i].value))) { // checks if the element is a num, which it should not
                return false;
            }
        }
        else { // "shifted" from the parens
            if (i % 2 == 1 && isOperator(tokens[i].value)) { // checks if the element is an op, which it should not
                return false;
            }
            if (i % 2 == 0 && !(isOperator(tokens[i].value))) { // checks if the element is a num, which it should not
                return false;
            }
        }
    }

    return true;
}

// Conversion

vector<Token> infixToPostfix(const vector<Token>& tokens) {
    vector<Token> output;
    ArrayStack<Token> ops;

    for (int i = 0; i < tokens.size(); i++) {
        Token t = tokens[i];
        ops.printStack();
        printTokens(output);
        if (precedence(t.value) != -1) { // is operator or parens
            if (ops.size() >= 1 && output.size() > 1) { // has to be more than 1 operator in stack, and operator has to have more than 2
                if (t.value != "(" && t.value != ")" &&
                    (precedence(ops.top().value) == precedence(t.value) || (precedence(t.value) == 1 && precedence(ops.top().value) == 2)))

                    { // if the current op and the previous op are of the same precedence
                      // OR if the current op is of lower precedence than previous, prev gets added to output
                      // ignores if parens

                    output.push_back(ops.top());
                    ops.pop();

                    while (!(ops.empty()) && precedence(ops.top().value) == precedence(t.value)) {
                        output.push_back(ops.top());
                        ops.pop();
                    }

                    ops.push(t);
                }

                else if (precedence(t.value) == 4) { // op is a closing parens, ")"
                    while (precedence(ops.top().value) != 3) { // while op in stack is not an opening parens, "("
                        output.push_back(ops.top());
                        ops.pop();
                    }
                    ops.pop(); // gets rid of "(" in stack
                }

                else { // prev op is not of same precedence/previous op is not of higher precedence than current & can be opening parens
                    ops.push(t);
                }
            }
            else { // size of stack is 0, so gotta add this :)
                ops.push(t);
            }
        }
        else { // is num, just add to output
            output.push_back(t);
        }
    }

    while (!(ops.empty())) {
        output.push_back(ops.top());
        ops.pop();
    }

    return output;
}

// Evaluation

double evalPostfix(const vector<Token>& tokens) {
    ArrayStack<double> stack;

    for (int i = 0; i < tokens.size(); i++) {
        if (isOperator(tokens[i].value)) {
            // current token is an operator

            double num1 = stack.top();
            stack.pop();
            double num2 = stack.top();
            stack.pop();

            if (tokens[i].value == "+") {
                stack.push(num2 + num1);
            }
            else if (tokens[i].value == "-") {
                stack.push(num2 - num1);
            }
            else if (tokens[i].value == "*") {
                stack.push(num2 * num1);
            }
            else {
                stack.push(num2 / num1);
            }
        }
        else { // current token is a number
            stringstream stream;
            double num;

            stream << tokens[i].value;
            stream >> num;
            stack.push(num);

            stream.str("");
            stream.clear();
        }
    }

    return stack.top();
}

// Main

int main() {
    string line;
    getline(cin, line);

    vector<Token> tokens = tokenize(line);

    if (isValidPostfix(tokens)) {
        cout << "FORMAT: POSTFIX\n";
        cout << "RESULT: " << evalPostfix(tokens) << "\n";
    }
    else if (isValidInfix(tokens)) {
        vector<Token> postfix = infixToPostfix(tokens);
        cout << "FORMAT: INFIX\n";
        cout << "POSTFIX: ";
        for (const auto& t : postfix) {
            cout << t.value << " ";
        }
        cout << "\n";
        cout << "RESULT: " << evalPostfix(postfix) << "\n";
    }
    else {
        cout << "FORMAT: NEITHER\n";
        cout << "ERROR: invalid expression\n";
    }

    return 0;
}
