#include <iostream>
#include <vector>
#include <map>
#include <string>
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
    private:
        Operator getOp(char given);
        bool isOp(char c);
};

class Separator{

};

class ExpressionTree{

};