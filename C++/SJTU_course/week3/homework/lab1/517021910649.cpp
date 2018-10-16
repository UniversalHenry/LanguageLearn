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

const double MAX = 8.95e307; // The maximum value of the number
const double MIN = -8.95e307; // The minimum value of the number
const double EPS = 1e-10; // The minimun precision

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
		if(val > MAX)throw "too large input";
		if(val < MIN)throw "too small input";
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
// Processes bracket, numbers, ANS, signal and '!'
double primary(){
	Token t = ts.get(); // Get a character
	switch (t.get_kind()){
	case '(': 
	{	double d = expression(); // Perform calculations in semicolons
		t = ts.get(); // Get a ')' closing character
		if (t.get_kind() != ')')throw "right bracket miss"; // If there wasn't any ')' return an error
		while(true){// Check factorial
			Token t = ts.get();
			switch (t.get_kind()){
				case '!': // Factorial
				{   
					double x = d;
					if(abs(fmod(x,1))>EPS || x<=-EPS)throw "factorial";
					for (int i = 1; i < d; i++) { // Get a multiplication of all numbers before x (including x)
						x*=i;
						x = floor(x);
						if(x > MAX)throw "too large factorial";
					}
					if (abs(x) < EPS) d = 1;
					else d = x;
					break;
				}
				default:
					ts.putback(t); // If nothing was done return character to the stream
					if (d == -0) return 0; // Change -0 to 0 when it was multiplied or divided by negative digit
					return d; // Return new or unchanged value of 'left'
			}
		}
		return d;
	}
	case '-': // For negative digits
		return -primary(); // Return negative digit
	case '+': // For positive digits
		return primary(); // Return positive digit
	case Token::number: // If Token is a number
	case Token::ANS: // If Token is ANS
	{	double d = t.get_value();
		while(true){// Check factorial
			Token t = ts.get();
			switch (t.get_kind()){
				case '!': // Factorial
				{   
					double x = d;
					if(abs(fmod(x,1))>EPS || x<=-EPS)throw "factorial";
					for (int i = 1; i < d; i++) { // Get a multiplication of all numbers before x (including x)
						x*=i;
						x = floor(x);
						if(x > MAX)throw "too large factorial";
					}
					if (abs(x) < EPS) d = 1;
					else d = x;
					break;
				}
				default:
					ts.putback(t); // If nothing was done return character to the stream
					if (d == -0) return 0; // Change -0 to 0 when it was multiplied or divided by negative digit
					return d; // Return new or unchanged value of 'left'
			}
		}
		return d; // Return the number
	}
	default:
		throw "primary"; // Return an error if an inappropriate character was provided
	}
}


/****************************************************************************************************/
// Definition of term()
/****************************************************************************************************/
// Performs '*', '/' and '%'
double term(){
	double left = primary(); // Get a number
	while(true) {
		Token t = ts.get(); // Get a new character
		switch(t.get_kind()){
		case '*': // Multiplication
		{	double d = primary();
			if(left!=0 && d!=0 && (log10(abs(left))+log10(abs(d)))>log10(MAX))throw "too large multiplication"; // Too large multiplication is prohibited
			left *= d;
			break;
		}
		case '/': // Division
		{	double d = primary(); 
			if(d == double(0))throw "division by zero"; // Division by zero is prohibited
			if(left!=0 && d!=0 && (log10(abs(left))-log10(abs(d)))>log10(MAX))throw "too large division"; // Too large division is prohibited
			left /= d;
			break;
		}        
        case '%': // Modulo
            {
                double d = primary();
                if(d == double(0))throw "mudulo by zero"; // Mudulo by zero is prohibited
				if((abs(fmod(d,1)) > EPS)||abs(fmod(left,1)) > EPS)throw "mudulo not int"; // Mudulo not int is prohibited
                left = fmod(left-fmod(left,1),d-fmod(d,1)); // Use fmod to divide floating-point numbers with remainder
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
		{	
			double d = term();
			if(left > MAX || d > MAX)throw "too large number to add";
			if(left < MIN || d < MIN)throw "too small number to add";
			left += d; // Addition
			break;
		}
		case '-':
		{	
			double d = term();
			if(left > MAX || d > MAX)throw "too large number to minus";
			if(left < MIN || d < MIN)throw "too small number to minus";
			left -= d; // Subtraction
			break;
		}
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
    ifstream in_file("input.txt");
	string input;
	vector <string> output;
	while(getline(in_file,input)){
		// cout << input << endl;
        ts.get_input() << input;
        output.push_back(ts.calculate());
        ts.tidy();
    }
    in_file.close();
    // Output the result to the output file
    ofstream out_file("output.txt",ios_base::trunc);
    for(int i=0;i<output.size();i++){
		// cout << output.at(i) << endl;
		if(i < output.size()-1)out_file<<output.at(i)<<endl;
		if(i == output.size()-1)out_file<<output.at(i);
	}
    out_file.close();

	// cout << "\nProgram finished.";
	// getchar();
    return 0;
}