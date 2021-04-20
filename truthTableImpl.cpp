/**
 * @file truthTableImpl.cpp
 * @author Shannon Burke
 * @brief 
 * @version 0.1
 * @date 2021-04-19
 * 
 * @copyright Copyright (c) 2021
 * 
 */
#include "truthTable.h"

void toBinary(vector<char>& var, vector<int>& val){

    int incr = 1;
	for (int i = var.size() - 1; i >= 0; i--) {
		if (val[var[i] - 'A'] == 1 && incr == 1) {
			val[var[i] - 'A'] = 0;
			
		}
		else if (incr == 1) {
			val[var[i] - 'A'] = 1;
			incr = 0;
		}
	}
}

void printTable(string s){
    vector<char> var; //stores all variables that are present in the boolean expression s
	vector<int> val(26, -1); //stores the value of each boolean variable
							
	string postfix; 

	for (int i = 0; i < s.length(); i++) {

		if (s[i] >= 'A' && s[i] <= 'Z' && val[s[i] - 'A'] == -1) {
			val[s[i] - 'A'] = 0;
			var.push_back(s[i]);
		}

	}

	postfix = Expression::toPostFix(s);

	for (int i = 0; i < var.size(); i++) {
		cout << "|" << var[i] << setw(1);
	}
	cout << "|" << s << setw(1) << endl;

	for(int i = 0; i < var.size() + 1; i++){
		cout << "+";
		for(int j = 0; j < 1; j++){
			cout << "-";
		}
	}
	cout << "\n";

	for (int i = 0; i < pow(2, var.size()); i++) {

		for (int i = 0; i < var.size(); i++) {
			if(val[var[i] - 'A'] == 0){
				cout << "|" << "F" << setw(1);
			}
			if(val[var[i] - 'A'] == 1){
				cout << "|" << "T" << setw(1);
			}
		}

		if(Expression::evalExpr(postfix, val) == 0){
			cout << "|" << "F" << endl;
		}
		if(Expression::evalExpr(postfix, val) == 1){
			cout << "|" << "T" << endl;
		}
		toBinary(var, val);

		for(int k = 0; k < var.size() + 1; k++){
			cout << "+";
			for(int z = 0; z < 1; z++){
                cout << "-";
			}
		}
		cout << "\n";
	}
}

int main(){

    cout << "*----------------------------------------------------------------------------------------------------------------*\n";
    cout << "* This program generates truth tables for propositional logic formulas.                                          *\n";
    cout << "* You can enter the given logical operators: AND(^), OR(+), NOT(~), COND(>), BICOND(-) in many different formats.*\n";
    cout << "* For example, you may enter a propositional logic such as: (P^Q)+(Q^C) and also one as: ~(P+Q)^(P>C) and etc.   *\n";
    cout << "*----------------------------------------------------------------------------------------------------------------*\n";

    string s;
    cout << "Enter Boolean Expression: ";
    cin >> s;
    cout << "\n";
    cout << "---------------------------------------------------------\n";

    printTable(s);
}


