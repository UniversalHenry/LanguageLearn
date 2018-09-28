#include <iostream>
#include <cstdlib> 
#include <cstdio>
#include <fstream>
#include <vector>
#include <iterator>

using namespace std;

class Token{

};

class Token_stream{

};
Token_stream::Token_stream():full(false),buffer(0){

}
void Token_stream::putback(Token t){

}
Token Token_stream::get(){


}
Token_stream ts;
double expression();

double primary(){

}
double term(){

}
double expression(){
    
}
int main(void){
    ifstream in_file("lab1_input.txt");
    string input;
    vector <string> output; 
    while(getline(in_file,input)){
        output.
    }
    in_file.close();
    ofstream out_file("lab1_input.txt",ios_base::trunc);
    for (int i=0;i<output.size();i++)cout<<output.at(i)<<endl;
    out_file.close();
    cout << "\nProgram finished.";
    int test;
    cin >> test;
    return 0;
}