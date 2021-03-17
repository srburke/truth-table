#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stack>
using namespace std;
class Operator: private TruthTable{
    public:
        char inputChar;
        char outputChar;
        int precedence = 0, connective = 0;

        Operator(char inChar, char outChar, int prec, int con){
            inputChar = inChar;
            outputChar = outChar;
            precedence = prec;
            connective = con;
        }
    private:
        Operator getOp(char given);
        
};

//If a charcter is an operand push that into stack
//If a character is an operator pop two values from the stack make them its child
//and push the current node again.
class ExpressionTree{
    private:
        char data;
        ExpressionTree *leftChild, *rightChild;

        ExpressionTree(char c){
            data = '\0';
            leftChild = NULL;
            rightChild = NULL;
        }

        //ExpressionTree():data('\0'), leftChild(nullptr), rightChild(nullptr){};

    public:
        ExpressionTree(char data);
        void insert(ExpressionTree *newTree);
        bool virtual isEmpty();
        ExpressionTree getLeftChild();
        ExpressionTree getRightChild();
        char getData();
        void setData(char theData);
        ~ExpressionTree();
};

class TruthTable{
    public:
        TruthTable(string input, bool isTrueFirst);

        vector<char> getVars();
        vector<string> getInputVals();
        vector<char> getOutputVals();
        string getInfix();
        string getPostfix();
        bool getIsValid();
        bool isVar(char c);
        void print();
        ~TruthTable();

    private:
        void determineVars();
        string trim(string ignoreSpace);
        bool hasValidChars(string expr);
        void toPostfix(string infix);
        void createInfix(ExpressionTree beginNode);
        void toInfix(ExpressionTree mainExprTree);
        void checkForErrors();
        void generateInputVals();
        bool evaluate(bool isTrueFirst);
};