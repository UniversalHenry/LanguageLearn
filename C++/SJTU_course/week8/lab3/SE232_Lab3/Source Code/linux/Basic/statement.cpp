/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <memory>
#include <string>
#include <vector>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "evalstate.h"
#include "statement.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"

using namespace std;

/* Implementation of the Statement class */

void Complex_statement::execute(EvalState & state){
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(line);
	string firstToken = scanner.nextToken();
	if(firstToken == "REM"){
		return;
	}
	if(firstToken == "LET"){
		firstToken = scanner.nextToken();
		vector<string> order_name = {"REM","LET","PRINT","INPUT",
		"IF","THEN","GOTO","RUN","LIST","CLEAR","QUIT","HELP","END"};
		for(auto ptr = order_name.begin(); ptr != order_name.end(); ptr++)
			if(*ptr == firstToken) error("SYNTAX ERROR");
		scanner.setInput(line);
		scanner.nextToken();
		Expression *exp = parseExp(scanner);
		int value = exp->eval(state);
		return;
	}
	if(firstToken == "PRINT"){
		Expression *exp = parseExp(scanner);
		int value = exp->eval(state);
		cout << value << endl;
		return;
	}
	if(firstToken == "INPUT"){
		string name = scanner.nextToken();
		string tmpLine;
		while(true){
			try{
				cout << " ? ";
				getline(cin, tmpLine);
				TokenScanner tmpScanner(tmpLine);
				tmpLine = tmpScanner.nextToken();
				int negative = 0;
				if(tmpLine == "-"){
					negative = 1;
					tmpLine = "-" + tmpScanner.nextToken();
				}
				if(tmpScanner.hasMoreTokens()) error("INVALID NUMBER");
				for(auto ch = tmpLine.begin() + negative; ch != tmpLine.end(); ch++)
					if(!isdigit(*ch)) error("INVALID NUMBER");
				break;
			}
			catch(ErrorException& e){
				cout << e.getMessage() << endl;
			}
		}
		int val;
		stringstream ss;
		ss << tmpLine;
		ss >> val;
		state.setValue(name, val);
		return;
	}
	if(firstToken == "IF"){
		string tmpExpression;
		string tmp;
		while((tmp = scanner.nextToken()) != "=" && tmp != ">" && tmp != "<" && scanner.hasMoreTokens()){
			tmpExpression += tmp;
		}
		TokenScanner tmpScanner(tmpExpression);
		Expression *exp = parseExp(tmpScanner);
		int l_val = exp->eval(state);
		char op = tmp[0];
		tmpExpression = "";
		while((tmp = scanner.nextToken()) != "THEN"){
			tmpExpression += tmp;
		}
		tmpScanner.setInput(tmpExpression);
		exp = parseExp(tmpScanner);
		int r_val = exp->eval(state);
		switch(op){
			case '>':if(!(l_val > r_val)) return; break;
			case '<':if(!(l_val < r_val)) return; break;
			case '=':if(!(l_val == r_val)) return; break;
		}
		firstToken = "GOTO";
	}
	if(firstToken == "GOTO"){
		string tmpLine = scanner.nextToken();
		if(scanner.hasMoreTokens() || scanner.getTokenType(tmpLine) != NUMBER) error("SYNTAX ERROR");
		for(auto ch = tmpLine.begin(); ch != tmpLine.end(); ch++)
			if(!isdigit(*ch)) error("SYNTAX ERROR");
		next_program_line = atoi(tmpLine.c_str());
		if(program_ptr->getSourceLine(next_program_line) == "") error("LINE NUMBER ERROR");
		return;
	}
	error("SYNTAX ERROR");
}

void Simple_statement::execute(EvalState & state){
	if(line == "LIST"){
		if(program_ptr == nullptr) return;
		int LineNum = program_ptr->getFirstLineNumber();
		while(LineNum >= 0){
			auto tmpLine = program_ptr->getSourceLine(LineNum);
			cout << LineNum << " " << tmpLine << endl;
			LineNum = program_ptr->getNextLineNumber(LineNum);
		}
		return;
	}
	if(line == "CLEAR"){
		program_ptr->clear();
		state.clear();
		return;
	}
	if(line == "QUIT"){
		exit(0);
	}
	if(line == "HELP"){
		cout << "Stub implementation of BASIC" << endl;
		return;
	}
	if(line == ""){
		return;
	}
	error("SYNTAX ERROR");
	return;
}

void Check_statement::execute(EvalState & state){
	TokenScanner scanner;
	scanner.ignoreWhitespace();
	scanner.scanNumbers();
	scanner.setInput(line);
	string firstToken = scanner.nextToken();
	if(firstToken == "REM"){
		return;
	}
	if(firstToken == "LET"){
		Expression *exp = parseExp(scanner);
		return;
	}
	if(firstToken == "PRINT"){
		Expression *exp = parseExp(scanner);
		return;
	}
	if(firstToken == "INPUT"){
		string firstToken = scanner.nextToken();
		if(scanner.hasMoreTokens()) error("SYNTAX ERROR");
		return;
	}
	if(firstToken == "IF"){
		string tmpExpression;
		string tmp;
		while((tmp = scanner.nextToken()) != "=" && tmp != ">" && tmp != "<" && scanner.hasMoreTokens()){
			tmpExpression += tmp;
		}
		TokenScanner tmpScanner(tmpExpression);
		Expression *exp = parseExp(tmpScanner);
		tmpExpression = "";
		while((tmp = scanner.nextToken()) != "THEN"){
			tmpExpression += tmp;
		}
		tmpScanner.setInput(tmpExpression);
		exp = parseExp(tmpScanner);
		firstToken = "GOTO";
	}
	if(firstToken == "GOTO"){
		string tmpLine = scanner.nextToken();
		if(scanner.hasMoreTokens() || scanner.getTokenType(tmpLine) != NUMBER) error("SYNTAX ERROR");
		for(auto ch = tmpLine.begin(); ch != tmpLine.end(); ch++)
			if(!isdigit(*ch)) error("SYNTAX ERROR");
		return;
	}
	if(firstToken == "END"){
		return;
	}
	error("SYNTAX ERROR");
}

void Run_statement::execute(EvalState & state){
	if(program_ptr == nullptr) return;
	int LineNum = program_ptr->getFirstLineNumber();
	while(LineNum >= 0){
		auto tmpstmt = program_ptr->getParsedStatement(LineNum);
		if(program_ptr->getSourceLine(LineNum) == "END") break;
		tmpstmt->execute(state);
		LineNum = program_ptr->getNextLineNumber(LineNum);
		if(tmpstmt->next_program_line >= 0){
			LineNum = tmpstmt->next_program_line;
			tmpstmt->next_program_line = -1;
		}
	}
	return;
}