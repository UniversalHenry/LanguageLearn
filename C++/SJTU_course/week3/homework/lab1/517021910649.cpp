#include <iostream>
#include <cstdlib> 
#include <cstdio>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>

using namespace std;

/****************************************************************************************************/
// Definition of Token
/****************************************************************************************************/
class Token{
    char kind; // Record the type of Token, signals will be represented by themselves
	double value; // Value of the operand
    public:
    static const char ANS; // Represent ANS
    static const char end; // Prints the result of calculation
    static const char number; // Indicates that this is a number
	Token(char ch):kind(ch), value(0){} // Operator
	Token(char ch, double val) :kind(ch), value(val){} // Operand
    const char & get_kind(){return kind;} // Get kind of a token
    const double & get_value(){return value;} // Get value of a token
};
//Initialize the static members of Token
const char Token::ANS = 'a'; // Represent ANS
const char Token::end = ';'; // Prints the result of calculation
const char Token::number = 'n'; // Indicates that this is a number

/****************************************************************************************************/
// Definition of Stream of Tokens
/****************************************************************************************************/
class Token_stream{
    bool full; // If 'full' = true, get() will use symbol from buffer
	Token buffer; // Holds a symbol that wasn't used by specific function
    stringstream input; // Holds the input string stream
    double ANS; // Record the ANS
    double res; // Record the temporary result when calculating
	int bracket; // Record the number of bracket
    bool err; // Record whether the result is error
public:
	Token_stream():full(0),buffer(0),ANS(0),res(0),bracket(0),err(0){input.clear();} // Initialize the Token stream
	Token get(); // Get the charactors from input stream
	void putback(Token t); // Returns symbol to buffer. If 'full' = true, get() will use symbol from buffer
    stringstream& get_input(){return input;} // Input stream for read and write
    string calculate(); // Calculate the result according to the token serial
    void tidy(); // Tidy the token stream for next input stream
    friend double primary(); // Declaration of primary(),processes semicolons,bracket, numbers and ANS
    friend double term(); // Declaration of term(),performs '*', '/', '!' and '%'
    friend double expression(); // Declaration of expression(),performs '+' and '-' operations
};
// Returns symbol to buffer. If 'full' = true, get() will use symbol from buffer
void Token_stream::putback(Token t){buffer=t; full=true;}

// Get the charactors from input stream
Token Token_stream::get(){
    if(full){full=false;return buffer;} // If buffer is not empty, return value from it
    char ch;
    get_input() >> ch;  // Otherwise start looking for characters in input stream
	switch (ch) {
	case '(':{bracket++;return Token(ch);}
	case ')':{bracket--;if(bracket<0)throw "left bracket miss";return Token(ch);}
	case ';':
	case '+':
	case '-':
	case '*':
	case '/':
	case '%':
	case '!':
        return Token(ch);
    case '.':
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
    {	get_input().unget(); // If it is a number then return it to the stream
		double val;
        get_input() >> val; // Read the complete value
		return Token(Token::number,val);
	}
    default:
        if(isalpha(ch)){ // If it is a letter
			string s;
			s += ch; // Put the letter in 's' because it has been already read
			while(get_input().get(ch) && isalpha(ch)) s+=ch; // Continue to read in 's'
			get_input().unget(); // Return the character into the stream
			if(s == "ANS")return Token(Token::ANS,ANS); // Return name of variable
        }
        throw "bad token";
    }
}

double primary(); // Declaration of primary(),processes bracket, numbers and ANS
double term(); // Declaration of term(),performs '*', '/', '!' and '%'
double expression(); // Declaration of expression(),performs '+' and '-' operations

// Calculate from the stream, return the result of the input stream
string Token_stream::calculate(){
	try{
	Token t = this->get(); // Get a new character
	if(t.get_kind() == Token::end)return "error"; // Stop calculate if it is the end of the token stream
	this->putback(t); // Return a character into the stream
	res = expression(); // Output the result
	}
	catch(const char* c){ // If containing error then output "error"
		err = true;
		// cerr << c << endl;
		return "error";
	}
	catch(exception& e){
		err = true;
		// cerr << "exception" << endl;
		return "error";
	}
	if(!err){
		// cout << res << endl;
		stringstream ss; // Otherwise output the result of calculation
		string s;
		ss << res;
		ss >> s;
		return s;
	}
}

// Tidy the token stream for next input stream
void Token_stream::tidy(){
	get_input().str("");
	if(!err)ANS = res;
	err = false;
	bracket = 0;
	res = 0;
	full = false;
	buffer = Token(0);
}


/****************************************************************************************************/
// Static declaration of a token stream object
/****************************************************************************************************/
Token_stream ts; 


/****************************************************************************************************/
// Definition of primary()
/****************************************************************************************************/
// Processes bracket, numbers and ANS
double primary(){
	Token t = ts.get(); // Get a character
	switch (t.get_kind()) {
	case '(': 
	{	double d = expression(); // Perform calculations in semicolons
		t = ts.get(); // Get a ')' closing character
		if (t.get_kind() != ')')throw "right bracket miss"; // If there wasn't any ')' return an error
		return d;
	}
	case '-': // For negative digits
		return -term(); // Return negative digit
	case '+': // For positive digits
		return term(); // Return positive digit
	case Token::number: // If Token is a number
		return t.get_value(); // Return the number
	case Token::ANS: // If Token is ANS
		return t.get_value(); // Return the value of ANS
	default:
		throw "primary"; // Return an error if an inappropriate character was provided
	}
}


/****************************************************************************************************/
// Definition of term()
/****************************************************************************************************/
// Performs '*', '/', '!' and '%'
double term(){
	double left = primary(); // Get a number
	while(true) {
		Token t = ts.get(); // Get a new character
		switch(t.get_kind()){
		case '*': // Multiplication
			left *= primary(); 
			break;
		case '/': // Division
		{	double d = primary(); 
			if(d == 0)throw "division"; // Division by zero is prohibited
			left /= d;
			break;
		}
        case '!': // Factorial
            {   
                int x = left;
                if(abs(abs(x)-left)>1e-10)throw "factorial";
                for (int i = 1; i < left; i++) { // Get a multiplication of all numbers before x (including x)
                    x*=i;
                }
                if (x == 0) left = 1;
                else left = x;
                break;
            }        
        case '%': // Modulo
            {
                double d = primary();
                if(d == 0)throw "mudulo";
                left = fmod(left,d); // Use fmod to divide floating-point numbers with remainder
                break;
            }
		default:
			ts.putback(t); // If nothing was done return character to the stream
			if (left == -0) return 0; // Change -0 to 0 when it was multiplied or divided by negative digit
			return left; // Return new or unchanged value of 'left'
		}
	}
}


/****************************************************************************************************/
// Definition of expression()
/****************************************************************************************************/
// Performs '+' and '-' 
double expression(){
    double left = term(); // Get the number or the result of calculations in term
	while(true){
		Token t = ts.get();
		switch(t.get_kind()){
		case '+':
			left += term(); // Addition
			break;
		case '-':
			left -= term(); // Subtraction
			break;
		default:
			ts.putback(t); // If nothing was done return character to the stream
			return left; // Return the new or unchanged value of 'left'
		}
	}
}


/****************************************************************************************************/
//main function
/****************************************************************************************************/
int main(void){
    // Reading input file and calculate the output result
    ifstream in_file("lab1_input.txt");
	string input;
	vector <string> output;
	while(getline(in_file,input)){
        ts.get_input() << input;
        output.push_back(ts.calculate());
        ts.tidy();
    }
    in_file.close();
    // Output the result to the output file
    ofstream out_file("lab1_output.txt",ios_base::trunc);
    for(int i=0;i<output.size();i++){
		if(i < output.size()-1)out_file<<output.at(i)<<endl;
		if(i == output.size()-1)out_file<<output.at(i);
	}
    out_file.close();

	// cout << "\nProgram finished.";
	// int test;
	// cin >> test;
    return 0;
}