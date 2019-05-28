/*
 * File: RandomWriter.cpp
 * ----------------------
 * [TODO: fill in your name and student ID]
 * Name: 陆昊成
 * Student ID: 517021910649
 * This file is the starter project for the random writer problem of Lab 2.
 * [TODO: extend the documentation]
 */

#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <ctime>
using namespace std;
#define MAX_CHAR_NUM 2000 // the maximum number of output characters

// get filename
void read_file(ifstream &file_input);

// get order number
int read_order();

// build model
void model_read(ifstream &file_input, const int &order, map<string, vector<char>> &model);

// write
void random_write(const int &order, map<string, vector<char>> &model);

// choose the random output char according to the model
char select_char(const map<string, vector<char>>::iterator &piece);

void read_file(ifstream &file_input)
{
    // TODO: your code here
    while (true)
    {
        cout << "Please enter filename containing source text:";
        string file_name;
        cin >> file_name;
        file_input.open(file_name.c_str());
        if(file_input.is_open())break;      // break the loop only when the input file name is valid
    }
}

int read_order()
{
    // TODO: your code here
    while (true)
    {   
        cout << "Please enter order number:";
        int order_num = -1;         // default initialize the order number as -1
        cin >> order_num;
        if (cin.good() && order_num >= 0 && order_num < MAX_CHAR_NUM)return order_num;        // break the loop only when the input order number is valid
        cin.clear(); cin.sync();         // clear the cin for next input
    }
}

void model_read(ifstream &file_input, const int &order, map<string, vector<char>> &model)
{
    // TODO: your code here
    // initialize temporary variables
    char ch = '\0';
    string tmps = "";
    map<string, vector<char>>::iterator piece;
     // when is not the end of the file
    while(file_input.get(ch)){
        if(tmps.size() == order){       // when the choosen string piece == the order number, build model
            if((piece = model.find(tmps)) == model.end()){      // if the choosen string piece not exist in the model, initialize and insert it
                vector<char> vch;
                vch.push_back(ch);
                model.insert(make_pair(tmps,vch));
            }else{piece->second.push_back(ch);}         // if exist in the model, insert the new char into the piece of model
            if(order > 0)tmps = tmps.substr(1,tmps.size()-1);     // if the order number > 0, substr for new char to add
        }
        if(tmps.size() < order)tmps += ch;        // add the new char into the choosen string piece
    }
    // when is the end of the file
    if(tmps.size() == order){        // if the choosen string piece not exist in the model, initialize and insert '\0' to it
        if((piece = model.find(tmps)) == model.end()){
            vector<char> vch;
            vch.push_back('\0');
            model.insert(make_pair(tmps,vch));
        }
    }
}

void random_write(const int &order, map<string, vector<char>> &model)
{
    // TODO: your code here
    // initialize temporary variables
    char ch;
    string tmps = "";
    map<string, vector<char>>::iterator piece;
    // record the most frequent string pieces, and output one randomly
    vector<map<string, vector<char>>::iterator> freq_pieces;
    piece = model.begin(); freq_pieces.push_back(piece);
    while(piece != model.end()){
        if(piece->second.size() > freq_pieces.back()->second.size()){       // if find a more frequent piece, clear freq_pieces and insert
            freq_pieces.clear();
            freq_pieces.push_back(piece);
        }
        else if(piece->second.size() == freq_pieces.back()->second.size()){     // if find the same frequent piece, insert
            freq_pieces.push_back(piece);
        }
        piece++;
    }
    piece = freq_pieces[rand() / (double(RAND_MAX) + 1) * freq_pieces.size()];      // choose the most frequent piece randomly
    cout << piece->first;
    // start to output the following characters
    tmps = piece->first;
    for(int output_char = order; output_char < MAX_CHAR_NUM; output_char++){    // start from the order because one piece has been output
        ch = select_char(piece);        // choose the random output char according to the model
        if(ch == '\0')break;        // if meet the '\0', which means end the output
        cout << ch;
        if(order > 0){      // if the order number > 0, add the new character to the string piece
            tmps = tmps.substr(1,tmps.size() - 1);
            tmps += ch;
            piece = model.find(tmps);
        }
    }
}

char select_char(const map<string, vector<char>>::iterator &piece){        // choose the random output char according to the model
    int index = rand() / (double(RAND_MAX) + 1) * piece->second.size();
    return piece->second[index];
}

int main()
{   
    // time start
    double dur;
    clock_t start,end;
    start = clock();
    // TODO: your code here
    srand(1);        // generate a random seed
    map<string, vector<char>> model;        // initialize the Markov model
    ifstream input;         // initialize the input file
    int order = -1;         // initialize the order number
    read_file(input);       // open the file
    order = read_order();       // input the order number
    model_read(input, order, model);    // generate the model according to the file and order
    input.close();      // close the file
    random_write(order, model);     // random write the output
    // time stop
    end = clock();
    dur = (double)(end - start);
    printf("\nUseTime:%f",(dur / CLOCKS_PER_SEC));
	cout << "\nProgram finished.";
    cin >> dur;
    return 0;
}
