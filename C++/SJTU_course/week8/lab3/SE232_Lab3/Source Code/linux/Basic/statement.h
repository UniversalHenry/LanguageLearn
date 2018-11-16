/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include <memory>
#include <string>
#include "program.h"

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

class Program;

class Statement{

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

   // To indicate the next line when GOTO, if normal order show -1
   int next_program_line;

   Statement():next_program_line(-1){};

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~Statement(){};

/*
 * Method: execute
 * Usage: stmt->execute(state){};
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

   virtual void execute(EvalState & state) = 0;

};

/*
 * The remainder of this file must consists of subclass
 * definitions for the individual statement forms.  Each of
 * those subclasses must define a constructor that parses a
 * statement from a scanner and a method called execute,
 * which executes that statement.  If the private data for
 * a subclass includes data allocated on the heap (such as
 * an Expression object), the class implementation must also
 * specify its own destructor method to free that memory.
 */

class Complex_statement:public Statement{
  // statements with more than one word
  public:
    Complex_statement(const Complex_statement& statement):
      line(statement.line),program_ptr(statement.program_ptr){};
    Complex_statement(const string &s, Program* p_ptr):
      line(s),program_ptr(p_ptr){};
    void execute(EvalState & state) override;
  private:
    string line;
    Program* program_ptr;
};

class Simple_statement:public Statement{
  // statements with only one word
  public:
    Simple_statement(const Simple_statement& statement):
      line(statement.line),program_ptr(statement.program_ptr){};
    Simple_statement(const string &s):line(s){};
    Simple_statement(const string &s, Program* p_ptr):
      line(s),program_ptr(p_ptr){};
    void execute(EvalState & state) override;
  private:
    string line;
    Program* program_ptr;
};

class Check_statement:public Statement{
  // check the program syntax
  public:
    Check_statement(const string &s):line(s){};
    Check_statement(const Check_statement& statement):line(statement.line){};
    void execute(EvalState & state) override; 
  private:
    string line;
};

class Run_statement:public Statement{
  // run the program
  public:
    Run_statement(const Run_statement& statement):program_ptr(statement.program_ptr){};
    Run_statement(const string &s){};
    Run_statement(const string &s, Program* p_ptr):program_ptr(p_ptr){};
    void execute(EvalState & state) override;
  private:
    Program* program_ptr;
};

#endif
