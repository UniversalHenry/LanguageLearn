/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "statement.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"

using namespace std;

/* Implementation of the Statement class */

Statement::Statement(){
    /* Empty */
}

Statement::~Statement(){
    /* Empty */
}

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
				if(tmpLine == "-"){
					tmpLine = "-" + tmpScanner.nextToken();
				}
				if(tmpScanner.hasMoreTokens() || tmpScanner.getTokenType(tmpLine) != NUMBER) error("SYNTAX ERROR");
				for(auto ch = tmpLine.begin(); ch != tmpLine.end(); ch++)
					if(!isdigit(*ch)) error("SYNTAX ERROR");
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
		auto tmpstatement = program_ptr->getParsedStatement(atoi(tmpLine.c_str()));
		tmpstatement->execute(state);
		return;
	}
	error("SYNTAX ERROR");
}

void Simple_statement::execute(EvalState & state){
	if(line == "RUN"){
		if(program_ptr == NULL) return;
		int LineNum = program_ptr->getFirstLineNumber();
		while(LineNum >= 0){
			auto tmpstatement = program_ptr->getParsedStatement(LineNum);
			if(program_ptr->getSourceLine(LineNum) == "END") break;
			LineNum = program_ptr->getNextLineNumber(LineNum);
		}
		return;
	}
	if(line == "LIST"){
		if(program_ptr == NULL) return;
		int LineNum = program_ptr->getFirstLineNumber();
		while(LineNum >= 0){
			auto tmpLine = program_ptr->getSourceLine(LineNum);
			cout << tmpLine << endl;
			if(program_ptr->getSourceLine(LineNum) == "END") break;
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
	error("SYNTAX ERROR");
	return;
}