#include <iostream>
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
    // TODO
    int i = 0;
    string str = "";
    Token t;
    while (i < line.length()) {
        if (!(isspace(line.at(i)))) {
            str += line.substr(i,1);
            //printf(" (not a space) ");
            //printf("%s",str.c_str());
        }
        else {
            //printf(" %s ",str.c_str());
            t = {str};
            tokens.push_back(t);
            //printf(" %s ",tokens.back().value.c_str());
            str = "";
            //printf(" (is a space) ");
        }
        //printf("%c\n", str.at(i));
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
    // TODO

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

// Detection

bool isValidPostfix(const vector<Token>& tokens) {
    // TODO

    if (!(isValidExpression(tokens)) || hasParens(tokens)) {
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

    printf("\nLINE 111"); return false;
}

bool isValidInfix(const vector<Token>& tokens) {
    // TODO

    if (!isValidExpression(tokens)) {
        return false;
    }

    int parens = 0;
    for (int i = 0; i < tokens.size(); i++) {

        //printf(" %s ", tokens[i].value.c_str());

        if (tokens[i].value == "(" || tokens[i].value == ")") {
            parens++;
        }
        else if (parens % 2 == 0) { // even, or "normal" (not shifted from parens)
            if (i % 2 == 0 && isOperator(tokens[i].value)) { // checks if the element is an op, which it should not
                printf("\nLINE 131"); return false;
            }
            if (i % 2 == 1 && !(isOperator(tokens[i].value))) { // checks if the element is a num, which it should not
                printf("\nLINE 134"); return false;
            }
        }
        else { // "shifted" from the parens
            if (i % 2 == 1 && isOperator(tokens[i].value)) { // checks if the element is an op, which it should not
                printf("\nLINE 139"); return false;
            }
            if (i % 2 == 0 && !(isOperator(tokens[i].value))) { // checks if the element is a num, which it should not
                printf("\nLINE 142"); return false;
            }
        }
    }

    return true;
}

// Conversion

vector<Token> infixToPostfix(const vector<Token>& tokens) {
    vector<Token> output;
    ArrayStack<Token> ops;
    // TODO

    for (int i = 0; i < tokens.size(); i++) {
        Token t = tokens[i];
        ops.printStack();
        if (precedence(t.value) != -1) { // is operator or parens
            //ops.push(t);
            if (ops.size() >= 1) { // has to be more than 1 operator in stack
                if (t.value != "(" && t.value != ")" && precedence(ops.top().value) == precedence(t.value)) { // if the current op and the previous op are of the same precedence, ignores if parens
                    output.push_back(ops.top());
                    ops.pop();
                    ops.push(t);
                }

                else if (precedence(t.value) == 4) { // op is a closing parens, ")"
                    while (precedence(ops.top().value) != 3) { // while op in stack is not an opening parens, "("
                        output.push_back(ops.top());
                        ops.pop();
                    }
                    ops.pop(); // gets rid of "(" in stack
                }

                else { // prev op is not of same precedence & can be opening parens
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

    output.push_back(ops.top());
    ops.pop();

    return output;
}

// Evaluation

double evalPostfix(const vector<Token>& tokens) {
    ArrayStack<double> stack;
    // TODO
    return 0.0;
}

// Printing

void printTokens(const vector<Token>& tokens) {
    for (int i = 0; i < tokens.size(); i++) {
        printf("%s ", tokens[i].value.c_str());
    }
    cout << endl;
}

// Main

int main() {
    string line;
    getline(cin, line);

    vector<Token> tokens = tokenize(line);

    /*

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

    */

    printTokens(tokens);

    tokens = infixToPostfix(tokens);

     ///FOR TESTING TOKENIZER
    printTokens(tokens);

    printf("\n%d",isValidExpression(tokens));
    printf("\n%d",isValidPostfix(tokens));
    printf("\n%d",isValidInfix(tokens));

    return 0;
}
