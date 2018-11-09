/*
 * File: Basic.cpp
 * ---------------
 * Name: 陆昊成(Henry Lu)
 * StudentID: 517021910649
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the BASIC interpreter from
 * Assignment #6.
 * [TODO: extend and correct the documentation]
 */

#include <cctype>
#include <iostream>
#include <string>
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);

/* Main program */

int main() {
   EvalState state;
   Program program;
   cout << "Stub implementation of BASIC" << endl;
   while (true) {
      try {
         processLine(getLine(), program, state);
      } catch (ErrorException & ex) {
         cerr << "Error: " << ex.getMessage() << endl;
      }
   }
   return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program & program, EvalState & state) {
   TokenScanner scanner;
   scanner.ignoreWhitespace();
   scanner.scanNumbers();
   scanner.setInput(line + " "); // add " " in case input is empty
   string firstToken = scanner.nextToken();
   if (scanner.getTokenType(firstToken) == NUMBER) {
        // save program
			if (scanner.hasMoreTokens()){
				int i = scanner.getPosition();
                // TODO_ME:: IF CHECK PASS
				program.addSourceLine(atoi(firstToken.c_str()), line.substr(i));
                // ELSE CERR
			}
			else{
                // CERR
            }
   }
   else{
       // excute the line
       // IF NO ERR DO
       // ELSE CERR
   }
}

// void processExp(string line, EvalState & state) {
//    TokenScanner scanner;
//    scanner.ignoreWhitespace();
//    scanner.scanNumbers();
//    scanner.setInput(line);
//    Expression *exp = parseExp(scanner);
//    int value = exp->eval(state);
//    cout << value << endl;
//    delete exp;
// }