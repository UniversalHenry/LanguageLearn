#include <iostream>
#include <cstdlib> 
#include <cstdio>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstring>
#include <sstream>

using namespace std;

stringstream ss;

stringstream& input_string_tmp(string &s){
  ss << s;
  return ss;
}
int main(void){
  // Reading input file and calculate the output result
  ifstream in_file("lab1_input.txt");
  string input;
  vector <string> output;
  while(getline(in_file,input)){
    string s = ">> ";
    input_string_tmp(s);
    input_string_tmp(input) >> input;
    output.push_back(input);
  }
  in_file.close();
  // Output the result to the output file
  ofstream out_file("lab1_output.txt",ios_base::trunc);
  for(int i=0;i<output.size();i++)out_file<<output.at(i)<<endl;
  out_file.close();

	cout << "\nProgram finished.";
	int test;
	cin >> test;
    return 0;
}