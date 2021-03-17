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

vector<char> vars = vector<char>();
vector<string> inputVal = vector<string>();
vector<char> outputVal = vector<char>();

//From char returns the defined operator.
Operator Operator::getOp(char given){
    if(given == NOT.inputChar){
        return NOT;
    }
    if(given == AND.inputChar){
        return AND;
    }
    if(given == OR.inputChar){
        return OR;
    }
    if(given == IMPLY.inputChar){
        return IMPLY;
    }
    if(given == IFF.inputChar){
        return IFF;
    }
}

bool Operator::isOp(char c){
    if(c == NOT.inputChar || c == AND.inputChar || c == OR.inputChar || c == IMPLY.inputChar
        || c == IFF.inputChar || c == leftParen.inputChar || c == rightParen.inputChar){
            return true;
        }
        return false;
}