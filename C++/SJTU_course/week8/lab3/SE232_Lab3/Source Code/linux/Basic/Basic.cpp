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
#include "statement.h"
#include "../StanfordCPPLib/error.h"
#include "../StanfordCPPLib/tokenscanner.h"
#include "../StanfordCPPLib/simpio.h"
#include "../StanfordCPPLib/strlib.h"
using namespace std;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);

/* Main program */

int main(){
   EvalState state;
   Program program;
   while(true){
      try{
         processLine(getLine(), program, state);
      } catch(ErrorException & ex){
         cout << ex.getMessage() << endl;
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
 * when the user enters a program line(which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program & program, EvalState & state){
    static bool last_run = false;
    static EvalState last_run_state = state;
    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line + " "); // add " " for the single input, like 15 END
    string firstToken = scanner.nextToken();
    if(scanner.getTokenType(firstToken) == NUMBER){
        // save program
        last_run = false;
        int order = atoi(firstToken.c_str());
        if(scanner.hasMoreTokens()){
            int i = scanner.getPosition();
            string tmpLine = line.substr(i);
            Check_statement check(tmpLine);
            check.execute(state);
            Complex_statement* stmt = new Complex_statement(tmpLine, &program);
            program.setParsedStatement(order, stmt);
            program.addSourceLine(order, tmpLine);
        }
        else{
        // remove the source line
            program.removeSourceLine(order);
        }
    }
    else if(scanner.hasMoreTokens()){
        // excute the line
        last_run = false;
        Complex_statement statement(line, &program);
        statement.execute(state);
    }
    else if(firstToken == "RUN"){
        // run the program in the former environment
        Run_statement statement(line, &program);
        if(last_run){
            state = last_run_state;
            statement.execute(state);
        }
        else{
            last_run_state = state;
            statement.execute(state);
        }
        last_run = true;
    }
    else{
        last_run = false;
        Simple_statement statement(line, &program);
        statement.execute(state);
    }
}