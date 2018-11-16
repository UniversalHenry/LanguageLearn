/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 * in which none of the methods do anything beyond returning a
 * value of the correct type.  Your job is to fill in the bodies
 * of each of these methods with an implementation that satisfies
 * the performance guarantees specified in the assignment.
 */

#include <string>
#include "program.h"
#include "statement.h"
using namespace std;

Program::Program() {
   // Replace this stub with your own code
}

Program::~Program() {
   // Replace this stub with your own code
}

void Program::clear() {
   // Replace this stub with your own code
   program_state.clear();
}

void Program::addSourceLine(int lineNumber, string line) {
   // Replace this stub with your own code
   map<int,string>::iterator the_state;
   the_state = program_state.find(lineNumber); // find lineNumber in the existing program
   if(the_state == program_state.end()) program_state.insert(make_pair(lineNumber,line)); // if not exist, put in
   else the_state->second = line; // if exist, change line content
}

void Program::removeSourceLine(int lineNumber) {
   // Replace this stub with your own code
   map<int,string>::iterator the_state;
   the_state = program_state.find(lineNumber); // find lineNumber in the existing program
   if(the_state == program_state.end()) return; // if not exist, ignore
   else program_state.erase(the_state); // if exist, delete
}

string Program::getSourceLine(int lineNumber) {
    // Replace this stub with your own code
   map<int,string>::iterator the_state;
   the_state = program_state.find(lineNumber); // find lineNumber in the existing program
   if(the_state == program_state.end()) return ""; // if not exist, ignore
   else return the_state->second; // if exist, show it
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    // Replace this stub with your own code
    map<int,Statement*>::iterator the_parsed_state;
    the_parsed_state = program_parsed_state.find(lineNumber);
    map<int,string>::iterator the_state;
    the_state = program_state.find(lineNumber);
    if(the_state == program_state.end()) error("LINE NUMBER ERROR");
    else if(the_parsed_state == program_parsed_state.end()) program_parsed_state.insert(make_pair(lineNumber,stmt));
    else the_parsed_state->second = stmt;
}

Statement *Program::getParsedStatement(int lineNumber) {
    // Replace this stub with your own code
    map<int,Statement*>::iterator the_parsed_state;
    the_parsed_state = program_parsed_state.find(lineNumber);
    if(the_parsed_state == program_parsed_state.end()) return NULL;
    else return the_parsed_state->second;
}

int Program::getFirstLineNumber() {
    // Replace this stub with your own code
    if(program_state.empty()) return -1;
    else return program_state.begin()->first;
}

int Program::getNextLineNumber(int lineNumber) {
    // Replace this stub with your own code
    map<int,string>::iterator the_state;
    the_state = program_state.find(lineNumber);
    if(the_state == program_state.end()) return -1;
    else the_state++;
    if(the_state == program_state.end()) return -1;
    else return the_state->first;
}
