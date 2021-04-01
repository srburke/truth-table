#include "truthTable.h"

const vector<char> OPS = vector<char>{'V', '^', '>', '-'};

//From char returns the defined operator.
bool isOp(char c){
    for(int i = 0; i < OPS.size(); i++){
        if(c == OPS[i]){
            return true;
        }
    }
    return false;
}

bool getPrec(char c){
    if(isOp(c)){
        if(c == '^' || c == 'V'){
            return 0;
        }
        if(c == '>' || c == '-'){
            return 1;
        }
    }
    return -1;
}

bool isOperand(char c){
    if(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'){
        return true;
    }
    return false;
}

bool AND (bool p, bool q){
    return p & q;
}
bool OR (bool p, bool q){
    return p | q;
}
bool IMPLY (bool p, bool q){
    return (p & !q) ? 1 : 0;
}
bool IFF (bool p, bool q){
    return (p & q) || (!p & !q);
}

bool Operator::eval(bool p, bool q){
    bool temp;
    switch(Operator::c){
        case '^':
                temp = AND(p, q);
                break;
        case 'V':
                temp = OR(p, q);
                break;
        case '>':
                temp = IMPLY(p, q);
                break;
        case '-':
                temp = IFF(p, q);
                break;
        default:
                temp = 1;
    }
    return temp;
}


vector<char> TruthTable::getVars(){
    return vars;
}

vector<string> TruthTable::getInputVals(){
    return inputVals;
}

vector<char> TruthTable::getOutputVals(){
    return outputVals;
}

string TruthTable::getInfix(){
    return infix;
}

string TruthTable::getPostfix(){
    return postfix;
}

bool TruthTable::getIsValid(){
    return isValid;
}


string TruthTable::trim(string ignoreSpace){
    string trim = "";

    for(int i = 0; i < ignoreSpace.length(); i++){
        char c = ignoreSpace[i];
        if(c != ' '){
            trim += c;
        }
    }
    return trim;
}


//If a character is an operand push that into stack
//If a character is an operator pop two values from the stack make them its child
//and push the current node again.
string TruthTable::toPostfix(string inFix){
    stack<char> opStack;
    
    for(int i = 0; i < inFix.length(); i++){
        char c = inFix[i];

        if(isOperand(c)){
            postfix += c;
        }
        else if(c == '('){
            opStack.push(c);
        }
        else if(c == ')'){
            while(!opStack.empty() && opStack.top() != '('){
                char temp = opStack.top();
                opStack.pop();
                postfix += temp;
            }
            opStack.pop();
        }
        else if(isOp(c)){
            while(!opStack.empty() && getPrec(opStack.top()) >= getPrec(c)){
                postfix += opStack.top();
                opStack.pop();
            }
            opStack.push(c);
        }
    }

    //Add remaining operators on the stack.
    while(!opStack.empty()){
        char temp = opStack.top();
        opStack.pop();
        postfix += temp;
    }
    return postfix;
}

void TruthTable::createInfix(ExpressionTree *beginNode){
    if(beginNode != NULL){
        if(isOp(beginNode->getData())){
            infix += '(';
        }

        createInfix(beginNode->getLeftChild());
        infix += beginNode->getData();
        createInfix(beginNode->getRightChild());

        if(isOp(beginNode->getData())){
            infix += ')';
        }
    }
}
//Creates an infix expression from an expression tree
void TruthTable::toInfix(ExpressionTree *mainExprTree){
    createInfix(mainExprTree);

    //Place negation in front of expression
    for(int i = 0; i < infix.length(); i++){
        if(infix[i] == '~'){
            //Find the NOTs left parenthesis
            for(int j = i; j >= 0; j--){
                if(infix[j] == '('){
                    string firstPart = infix.substr(0, j);
                    string negatedExpr = infix.substr(j, i);
                    string lastPart = infix.substr(i + 1, infix.length());

                    infix = firstPart + '~' + negatedExpr + lastPart;
                    break;
                }
            }
        }
    }
    //Remove outer left parenthesis 
    if(infix[0] == '('){
        infix = infix.substr(1);
    }

    //Remove outer right parenthesis
    if(infix[infix.length() - 1] == ')'){
        infix = infix.substr(0, infix.length() - 1);
    }
}

/**
 * Algorithm to construct a tree from the expression:
 *  Have a stack to store immediate values(which are trees),
 *  and examine each token from left to right
 *      - If it is an operand, turn it into a leaf node and
 *          push it on the stack
 *      - If it is an operator, pop two items from the stack,
 *          construct an operator node with those children,
 *             and push the new node on the stack
 * 
 */
//Should input the postfix expression to an expression tree
//If an error occurs then it's an invalid expression tree
bool TruthTable::inputPostExprToTree(){
    stack<ExpressionTree *> exprStack;
    ExpressionTree *nodeNew, *t1, *t2;
        for(int i = 0; i < postfix.length(); i++){
            char c = postfix[i];

            if(isOperand(c)){
                nodeNew = newNode(c);
                exprStack.push(nodeNew);
            } else if(c == '~'){
                nodeNew = newNode(c);
                t2 = exprStack.top();
                exprStack.pop();

                nodeNew->leftChild = t2;
                exprStack.push(nodeNew);
            } else if(isOp(c)){
                nodeNew = newNode(c);
                t1 = exprStack.top();
                exprStack.pop();
                t2 = exprStack.top();
                exprStack.pop();

                nodeNew->rightChild = t1;
                nodeNew->leftChild = t2;
                exprStack.push(nodeNew);

            }
        }
        nodeNew = exprStack.top();
        exprStack.pop();
        return nodeNew;
}


