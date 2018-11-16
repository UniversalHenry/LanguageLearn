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
	if (line == "RUN") {
		while()
		return;
	}
	if (line == "LIST") {
		program_ptr.reset();
		return;
	}
	if (line == "CLEAR") {
		program_ptr->clear();
		state.clear();
		return;
	}
	if (line == "QUIT") {
		exit(0);
	}
	if (line == "HELP") {
		cout << "Stub implementation of BASIC" << endl;
		return;
	}
	error("SYNTAX ERROR");
	return;
}