/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
using namespace std;

/* Implementation of the Statement class */

Statement::Statement() {
    /* Empty */
}

Statement::~Statement() {
    /* Empty */
}

void Complex_statement::execute(EvalState & state){

}

void Simple_statement::execute(EvalState & state){
	if (line == "HELP") {
		cout << "http://tcloud.sjtu.edu.cn/course/se106/2014/assignments/lab3/index.php" << endl;
		return;
	}
	if (line == "QUIT") {
		return;
	}
	if (line == "LIST") {
		outputProgram();
		return;
	}
	if (line == "CLEAR") {
		program.clear();
		variables.clear();
		program[0] = "";
		return;
	}
	if (line == "RUN") {
		runProgram();
		return;
	}
	error("SYNTAX ERROR");
	return;
}