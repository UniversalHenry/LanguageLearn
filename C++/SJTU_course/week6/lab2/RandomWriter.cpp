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
#define MAX_CHAR_NUM 2000

// get filename
void read_file(ifstream &file_input);

// get order number
int read_order();

// build model
void model_read(ifstream &file_input, const int &order, map<string, vector<char>> &model);

// write
void random_write(const int &order, map<string, vector<char>> &model);

// choose the random output char according to the model
char select_char(map<string, vector<char>>::iterator &piece);

void read_file(ifstream &file_input)
{
    // TODO: your code here
    while (true)
    {
        cout << "Please enter filename containing source text:";
        string file_name;
        cin >> file_name;
        file_input.open(file_name.c_str());
        if(file_input.is_open())break;
    }
}

int read_order()
{
    // TODO: your code here
    while (true)
    {   
        cout << "Please enter order number:";
        int order_num = -1;
        cin >> order_num;
        if (cin.good() && order_num >= 0 && order_num<MAX_CHAR_NUM)return order_num;
        cin.clear();cin.sync();
    }
}

void model_read(ifstream &file_input, const int &order, map<string, vector<char>> &model)
{
    // TODO: your code here
    char ch = '\0';
    string tmps = "";
    map<string, vector<char>>::iterator piece;
    while(file_input.get(ch)){
        if(tmps.size() == order){
            if((piece = model.find(tmps)) == model.end()){
                vector<char> vch;
                vch.push_back(ch);
                model.insert(make_pair(tmps,vch));
            }else{piece->second.push_back(ch);}
            if(order>0)tmps = tmps.substr(1,tmps.size()-1);
        }
        if(tmps.size()<order)tmps += ch;
    }

    if(tmps.size() == order){
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
    char ch;
    string tmps = "";
    map<string, vector<char>>::iterator piece;
    vector<map<string, vector<char>>::iterator> freq_pieces;
    piece = model.begin();freq_pieces.push_back(piece);
    while(piece != model.end()){
        if(piece->second.size() > freq_pieces.back()->second.size()){
            freq_pieces.clear();
            freq_pieces.push_back(piece);
        }
        else if(piece->second.size() == freq_pieces.back()->second.size()){
            freq_pieces.push_back(piece);
        }
        piece++;
    }
    piece = freq_pieces[rand()/(double(RAND_MAX)+1)*(freq_pieces.size())];
    cout << piece->first;
    tmps = piece->first;
    for(int output_char = order;output_char<MAX_CHAR_NUM;output_char++){
        ch = select_char(piece);
        if(ch == '\0')break;
        cout << ch;
        if(order > 0){
            tmps = tmps.substr(1,tmps.size()-1);
            tmps += ch;
            piece = model.find(tmps);
        }
    }
}

char select_char(map<string, vector<char>>::iterator &piece){
    int index = rand()/(double(RAND_MAX)+1)*(piece->second.size());
    return piece->second[index];
}

int main()
{   
    // time start
    double dur;
    clock_t start,end;
    start = clock();
    // TODO: your code here
    srand(1);
    map<string, vector<char>> model;
    ifstream input;
    int order = -1;
    read_file(input);
    order = read_order();
    model_read(input, order, model);
    input.close();
    random_write(order, model);
    // time stop
    end = clock();
    dur = (double)(end - start);
    printf("\nUseTime:%f",(dur/CLOCKS_PER_SEC));
	cout << "\nProgram finished.";
    cin >> dur;
    return 0;
}
