#include "truthTable.h"

Operator NOT = Operator('~','~', 5, 1);
Operator AND = Operator('V','V', 4, 2);
Operator OR = Operator('^','^', 3, 2);
Operator IMPLY = Operator('>','>', 2, 2);
Operator IFF = Operator('-','-', 1, 2);
Operator leftParen = Operator('(', '(', 0, 0);
Operator rightParen = Operator(')', ')', 0, 0);

char TRUE = 'T';
char FALSE = 'F';

//From char returns the defined operator.
Operator Operator::getOp(char c){
    if(c == NOT.inputChar){
        return NOT;
    }
    if(c == AND.inputChar){
        return AND;
    }
    if(c == OR.inputChar){
        return OR;
    }
    if(c == IMPLY.inputChar){
        return IMPLY;
    }
    if(c == IFF.inputChar){
        return IFF;
    }
}

bool isOp(char c){
    if(c == NOT.inputChar || c == AND.inputChar || c == OR.inputChar || c == IMPLY.inputChar
        || c == IFF.inputChar || c == leftParen.inputChar || c == rightParen.inputChar){
            return true;
        }
        return false;
}

ExpressionTree::ExpressionTree(char data){
        setData(data);
}

void ExpressionTree::insert(ExpressionTree *newTree){
    if(leftChild == NULL){
        leftChild = newTree;
    }
    if(rightChild == NULL){
        rightChild == newTree;
    }
    else{
        leftChild->insert(newTree);
    }
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

bool TruthTable::isVar(char c){
    if(c >= 'a' && c <= 'z' || c >= 'A' && c <= 'Z'){
        return true;
    }
    return false;
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

bool TruthTable::hasValidChars(string expr){
    //Check if expression has all valid characters
    for(int i = 0; i < expr.length(); i++){
        char inputChar = expr[i];
        if(!isOp(inputChar)){
            if(!isVar(inputChar)){
                return false;
            }
        }
    }
    return true;
}

//If a character is an operand push that into stack
//If a character is an operator pop two values from the stack make them its child
//and push the current node again.
void TruthTable::toPostfix(string infix){
    stack<char> opStack;
    
    for(int i = 0; i < infix.length(); i++){
        char c = infix[i];

        if(isVar(c)){
            postfix += c;
        }
        else if(c == leftParen.inputChar){
            opStack.push(c);
        }
        else if(c == rightParen.inputChar){
            while(!opStack.empty() && opStack.top() != leftParen.inputChar){
                postfix += opStack.top();
                opStack.pop();
            }
            opStack.pop();
        }
        else if(isOp(c)){
            while(!opStack.empty() && getOp(opStack.top()).precedence >= getOp(c).precedence){
                postfix += opStack.top();
                opStack.pop();
            }
            opStack.push(getOp(c).outputChar);
        }
    }

    //Add remaining operators on the stack.
    while(!opStack.empty()){
        postfix += opStack.top();
        opStack.pop();
    }
}

void TruthTable::createInfix(ExpressionTree beginNode){

    for(int i = 0; beginNode[i] != getData(); i++){
        if(isOp(beginNode[i])){

        }
    }

}
