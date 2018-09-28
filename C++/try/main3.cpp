#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#include <fstream>
using namespace std;

int main(void) {
  ifstream in_file("lab1_input.txt");
  string input;
  while(getline(in_file,input)){
    cout << input << '\n';
  }
  in_file.close();
  cout << "Program finished.";
  int test;
  cin >> test;
  return 0;
}