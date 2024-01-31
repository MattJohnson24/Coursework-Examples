#include <iostream>
#include <string>
#include <stack>
#include <queue>

#include "evalExp.h"

using std::string;
using std::stack;
using std::queue;
using std::cout;
using std::endl;
using std::min;
using std::max;


bool isValidExpression(const string &exp) {
    stack<char> expression;
    for (int i = 0; i < exp.length(); i++) {
        if (exp[i] == '(') {
            expression.push(exp[i]);
        }
        else if (exp[i] == ')') {
            if (!expression.empty() && expression.top() == '(' ) {
                expression.pop();
            }
            else {
                return false;
            }
        }
    }
    if (expression.empty()) {
        return true;
    }
    else {
        return false;
    }
}

queue<string> parseExpression(const string& exp) {
    queue<string> parsedExpression;
    string elements = "";

    for (int i = 0; i < exp.length(); i++) {
        if (exp[i] == '1' || exp[i] == '2' || exp[i] == '3' || exp[i] == '4' || exp[i] == '5' || exp[i] == '6' || exp[i] == '7' || exp[i] == '8' || exp[i] == '9' || exp[i] == '0') {
            elements = exp[i];
            while (exp[i+1] == '1' || exp[i + 1] == '2' || exp[i + 1] == '3' || exp[i + 1] == '4' || exp[i + 1] == '5' || exp[i + 1] == '6' || exp[i + 1] == '7' || exp[i + 1] == '8' || exp[i + 1] == '9' || exp[i + 1] == '0') {
                elements += exp[i+1];
                i++;
            }
            parsedExpression.push(elements);
            elements = "";
        }
        else if (exp[i] == 'm' && exp[i+1] == 'i' && exp[i+2] == 'n') {
            elements += "min";
            parsedExpression.push(elements);
            elements = "";
        }
        else if (exp[i] == 'm' && exp[i + 1] == 'a' && exp[i + 2] == 'x') {
            elements += "max";
            parsedExpression.push(elements);
            elements = "";
        }
        else if (exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' || exp[i] == '(' || exp[i] == ')' || exp[i] == ',') {
            elements += exp[i];
            parsedExpression.push(elements);
            elements = "";
        }
    }
    return parsedExpression;
}

bool checkPrec(const string &opr1, const string &opr2) {
    /* 
        Returns true if opr1 has higher or equal precedence as opr2.
        Returns false if opr1 has loWer precedence than opr2.
    */
    if ((opr1 == "(") ||
        (opr1 == "+" && opr2 == "*") ||
        (opr1 == "+" && opr2 == "/") ||
        (opr1 == "-" && opr2 == "*") ||
        (opr1 == "-" && opr2 == "/")) {
            return false;
    } else {
        return true;
    }
}

queue<string> inFixToPostFix(queue<string> &exp){
    queue<string> postfixExpression;
    stack<string> operators;
    
    while (!exp.empty()) {
        if (exp.front() == "(") {
            operators.push(exp.front());
            exp.pop();
        }
        else if (exp.front() == ")") {
            while (operators.top() != "("){
                postfixExpression.push(operators.top());
                operators.pop();
            } 
            operators.pop();
            exp.pop();
            if (!operators.empty() && (operators.top() == "max" || operators.top() == "min")) {
                postfixExpression.push(operators.top());
                operators.pop();
            }
        }
        else if (exp.front() == "*" || exp.front() == "/" || exp.front() == "+" || exp.front() == "-") {
            if (operators.empty()) {
                operators.push(exp.front());
                exp.pop();
            }
            else if(checkPrec(operators.top(), exp.front())) {
                postfixExpression.push(operators.top());
                operators.pop();
                operators.push(exp.front());
                exp.pop();
            }
            else {
                operators.push(exp.front());
                exp.pop();
            }
        }
        else if (exp.front() == "min" || exp.front() == "max") {
            operators.push(exp.front());
            exp.pop();
        }
        else if (exp.front() == ",") {
            while (operators.top() != "(") {
                postfixExpression.push(operators.top());
                operators.pop();
            }
            exp.pop();
        }
        else{ 
            postfixExpression.push(exp.front());
            exp.pop();
        }
    }
    while (!operators.empty()) {
        postfixExpression.push(operators.top());
        operators.pop();
    }

    return postfixExpression;
}

int EvalPostFixExp(queue<string> &exp) {
    stack<int> operands;
    int num = 0;
    int operand1 = 0;
    int operand2 = 0;
    int result = 0;
    string stringToInt = "";

    while(!exp.empty()) {
        if (exp.front() == "*") {
            operand1 = operands.top();
            operands.pop();
            operand2 = operands.top();
            operands.pop();
            result = operand1 * operand2;
            operands.push(result);
            exp.pop();
        }
        else if (exp.front() == "/") {
            operand1 = operands.top();
            operands.pop();
            operand2 = operands.top();
            operands.pop();
            result = operand2 / operand1;
            operands.push(result);
            exp.pop();
        }
        else if (exp.front() == "+") {
            operand1 = operands.top();
            operands.pop();
            operand2 = operands.top();
            operands.pop();
            result = operand1 + operand2;
            operands.push(result);
            exp.pop();
        }
        else if (exp.front() == "-") {
            operand1 = operands.top();
            operands.pop();
            operand2 = operands.top();
            operands.pop();
            result = operand2 - operand1;
            operands.push(result);
            exp.pop();
        }
        else if (exp.front() == "min") {
            operand1 = operands.top();
            operands.pop();
            operand2 = operands.top();
            operands.pop();
            result = min(operand1, operand2);
            operands.push(result);
            exp.pop();
        }
        else if (exp.front() == "max") {
            operand1 = operands.top();
            operands.pop();
            operand2 = operands.top();
            operands.pop();
            result = max(operand1, operand2);
            operands.push(result);
            exp.pop();
        }
        else {
            stringToInt = exp.front();
            num = stringToInt[0] - '0';
            for (int i = 0; i < stringToInt.length() - 1; i++) {
                num = num * 10;
                num = num + stringToInt[i + 1] - '0';
            }
            operands.push(num);
            exp.pop();
        }
    }
    return result;
}

int EvalExp(const string &exp) {
    if (!isValidExpression(exp)) {
        return -1024;
    } else {
        queue<string> parsedExp = parseExpression(exp);
        queue<string> postFixExp = inFixToPostFix(parsedExp);
        int x = EvalPostFixExp(postFixExp);
        return x;
    }
}