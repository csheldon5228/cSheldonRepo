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

bool hasParens(const vector<Token>& tokens) {
    for (int i = 0; i < tokens.size(); i++) {
        if (tokens[i].value == "(" || tokens[i].value == ")") {
            return true;
        }
    }
    return false;
}

bool isOperator(const string& s) {
    return s == "+" || s == "-" || s == "*" || s == "/";
}

int precedence(const string& op) {
    // TODO
    return 0;
}

// Detection

bool isValidPostfix(const vector<Token>& tokens) {
    // TODO

    if (~isValidExpression(tokens) || hasParens(tokens)) {
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

    if (~isOperator(tokens[0].value) && ~isOperator(tokens[1].value) &&
        isOperator(tokens.back().value) && countOps == -1) {
        return true;
    }

    return false;
}

bool isValidInfix(const vector<Token>& tokens) {
    // TODO



    return true;
}

// Conversion

vector<Token> infixToPostfix(const vector<Token>& tokens) {
    vector<Token> output;
    // TODO
    return output;
}

// Evaluation

double evalPostfix(const vector<Token>& tokens) {
    ArrayStack<double> stack;
    // TODO
    return 0.0;
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

     ///FOR TESTING TOKENIZER
    for (int i = 0; i < tokens.size(); i++) {
        printf("%s\n", tokens[i].value.c_str());
    }


    return 0;
}
