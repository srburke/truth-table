#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <stack>
using namespace std;
class Operator{
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
       public:
        ExpressionTree(char data){
            setData(data);
        }

        void insert(ExpressionTree *newTree);

        ExpressionTree getLeftChild(){
            return *leftChild;
        }

        ExpressionTree getRightChild(){
            return *rightChild;
        }
        
        char getData(){
            return data;
        }

        void setData(char theData){
            data = theData;
        }
};

/**Inorder traversal of expression tree produces infix version of given postfix expression
* (same with postorder traversal it gives postfix expression)
**/
class TruthTable : public Operator, ExpressionTree{
    private:
        vector<char> vars = vector<char>();
        vector<string> inputVals = vector<string>();
        vector<char> outputVals = vector<char>();
        string infix = "";
        string postfix = "";
        bool isValid = false;   
        void determineVars();
        string trim(string ignoreSpace);
        bool hasValidChars(string expr);
        void toPostfix(string infix);
        void createInfix(ExpressionTree beginNode);
        void toInfix(ExpressionTree mainExprTree);
        void checkForErrors();
        void generateInputVals();
        bool evaluate(bool isTrueFirst);

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

    
};