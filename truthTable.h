/**
 * @file truthTable.h
 * @author Shannon Burke
 * @brief 
 * @version 0.1
 * @date 2021-04-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stack>
#include <math.h>
#include <iomanip>
#include <algorithm>
using namespace std;
class Expression{

    static int getPrec(char c) {
		if (c == '~'){
            return 4;
        }		
		else if (c == '^'){
            return 3;
        } 
        else if (c == '+') {
            return 2;
        } 
        else if (c == '>'){
            return 1;
        } 
        else {
            return 0;
        }		
	}

	static bool isOp(char c) {
		return c == '^' || c == '+' || c == '>' || c == '-' || c == '~';
	}

	static bool isOperand(char c) {
		return c >= 'A' && c <= 'Z';
	}
      
public:

    /**
     * 1) If a character is an operand push that into stack
     * 2) If a character is an operator pop two values from the stack make them its child
     *      and push the current node again
     * 3) Pop again to remove extra '(' from the stack as it is already paired with ')' 
     * 
     * @param infix 
     * @return string 
     */
    static string toPostFix(string infix){
        stack<char> opStack;

		string postfix; //stores final postfix expression
		char c; //stores each token of infix expression

		infix.insert(0, 1, '(');
		infix.push_back(')');

		postfix = "";
		for (int i = 0; i < infix.length(); i++) {
			c = infix[i];
			if (c == '(') {
				opStack.push(c);
			}
			else if (isOperand(c)) {
				postfix.push_back(c);
			}
			else if (isOp(c)) {
				while (isOp(opStack.top()) && (getPrec(opStack.top()) >= getPrec(c))) {
					char curr = opStack.top();
					opStack.pop();
					postfix.push_back(curr);
				}
				opStack.push(c);
			}
			else if (c == ')') {
				while (opStack.top() != '(') {
					char curr = opStack.top();
					opStack.pop();
					postfix.push_back(curr);
				} 
				opStack.pop();
			}
		}
		return postfix;
    }


/**
 * Algorithm to evaluate postfix expressions:
 *  1) Create a stack to store operands (or values).
 *  2) Scan the given expression and do following for every scanned element.
 *      a) If the element is a number, push it into the stack
 *      b) If the element is a operator, pop operands for the operator from stack. 
 *          Evaluate the operator and push the result back to the stack
 *  3) When the expression is ended, the number in the stack is the final answer
 * 
 */
    static int evalExpr(string& postfix, vector<int>& val){
        stack<int> exprStack;
		char c;

		for (int i = 0; i < postfix.length(); i++) {
			c = postfix[i];
			if (isOperand(c)) {
				exprStack.push(val[c - 'A']);
			}
			else if (isOp(c)) {
				int e1, e2;
				if (c == '~') {
					e1 = exprStack.top();
					exprStack.pop();
					exprStack.push(!e1);
				}
				else {
					e1 = exprStack.top();
					exprStack.pop();
					e2 = exprStack.top();
					exprStack.pop();
					switch (c) {
					case '+':
						exprStack.push(e2 | e1);
						break;
					case '^':
						exprStack.push(e2 & e1);
						break;
                    case '>':
                        exprStack.push((e2 & !e1) ? 0 : 1);
                        break;
                    case '-':
                        exprStack.push((e2 & e1) || (!e2 & !e1));
                        break;
					}
				}
			}
		}
		return exprStack.top();
	}
};
