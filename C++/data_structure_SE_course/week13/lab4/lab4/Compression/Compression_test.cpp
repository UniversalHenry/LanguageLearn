#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include "huffman.h"

using namespace std;

void naiveCopy(string inputFilename, string outputFilename)
{
  ofstream ofs(outputFilename.c_str(), ios::out | ios::binary);
  ifstream ifs(inputFilename.c_str(), ios::in | ios::binary);
  char c;
  while (ifs.get(c))
    ofs.put(c);
  ofs.close();
  ifs.close();
}

void compress(string inputFilename, string outputFilename)
{
  ofstream ofs(outputFilename.c_str(), ios::out | ios::binary);
  ifstream ifs(inputFilename.c_str(), ios::in | ios::binary);
  Huffman hfm_coder;
  char c;
  vector<unsigned char> input, output;
  while (ifs.get(c))
    input.push_back(c);
  output = hfm_coder.encode(input);
  for (int i = 0; i < output.size(); i++)
    ofs.put(output[i]);
  ofs.close();
  ifs.close();
};

void decompress(string inputFilename, string outputFilename)
{
  ofstream ofs(outputFilename.c_str(), ios::out | ios::binary);
  ifstream ifs(inputFilename.c_str(), ios::in | ios::binary);
  Huffman hfm_coder;
  char c;
  vector<unsigned char> input, output;
  while (ifs.get(c))
    input.push_back(c);
  output = hfm_coder.decode(input);
  for (int i = 0; i < output.size(); i++)
    ofs.put(output[i]);
  ofs.close();
  ifs.close();
}

int main()
{
  string inputFilename, outputFilename, genFile;
  inputFilename = "./test.txt";
  outputFilename = "output.txt";
  genFile = "genfile.txt";
  compress(inputFilename, outputFilename);
  decompress(outputFilename, genFile);
  // naiveCopy(inputFilename,genFile);
  system("pause");
  return 0;
}
