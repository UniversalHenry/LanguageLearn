#include <iostream>
#include <cstdlib> 
#include <cstdio>
#include <sstream>
#include <cmath>
#include <ctime>
#include <cstring>
#include <stack>

using namespace std;

int get_level(const char &c);

string get_output(const int &front_level);

int main(void){ // main function here
    string output;
    while(true){
        output = get_output(0); // 0 represets the front level is the lowest, see the implementation
        cout << output;
    }
    return 0;
}

int get_level(const char &c){ // decide the level of operator
    switch(c){
        case '+':return 1;
        case '-':return 2;
        case '*':return 3;
        case '/':return 4;
        default: return 0;
    }
}

string get_output(const int &front_level){ // get the output of the input
    string output = "";
    int now_level = 5, tmp_level = 0; // set the init level, 5 is the highest and 0 is the lowest
    char token;
    while(cin.get(token)){
        switch(token){
            case '(':{
                output += get_output(tmp_level);
                break;
            }
            case '+':
            case '-':
            case '*':
            case '/':{
                tmp_level = get_level(token);
                if(tmp_level < now_level) now_level = tmp_level;
                output += token;
                break;
            }
            case ')':{ // if ), decide whether to output ()
                cin.get(token);
                cin.unget();
                tmp_level = get_level(token);
                if(now_level < front_level || (now_level == front_level && front_level % 2 == 0) || (now_level / 2) < (tmp_level / 2))
                    return ("(" + output + ")");
                else return output;
            }
            case '\n':{// if '\n', output result
                return (output + token);
            }
            default:// for variables only read in alpha and digit
                if(isalpha(token) || isdigit(token)) output += token;
        }
    }
}