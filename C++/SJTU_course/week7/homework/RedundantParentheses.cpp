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

int main(void){
    string output;
    while(true){
        output = get_output(0);
        cout << output;
    }
    return 0;
}

int get_level(const char &c){
    switch(c){
        case '+':return 1;
        case '-':return 2;
        case '*':return 3;
        case '/':return 4;
        default: return 0;
    }
}

string get_output(const int &front_level){
    string output = "";
    int now_level = 5, tmp_level = 0;
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
            case ')':{
                cin.get(token);
                cin.unget();
                tmp_level = get_level(token);
                if(now_level < front_level || (now_level == front_level && front_level % 2 == 0) || (now_level / 2) < (tmp_level / 2))
                    return ("(" + output + ")");
                else return output;
            }
            case '\n':{
                return (output + token);
            }
            default:
                if(isalpha(token) || isdigit(token)) output += token;
        }
    }
}