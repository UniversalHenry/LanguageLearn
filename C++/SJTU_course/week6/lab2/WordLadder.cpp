/*
 * File: WordLadder.cpp
 * --------------------
 * [TODO: fill in your name and student ID]
 * Name: 陆昊成
 * Student ID: 517021910649
 * This file is the starter project for the word ladder problem of Lab 2.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <fstream>
#include <string>
#include <set>
#include <queue>
#include <vector>

using namespace std;

//find the dest and init
void show_ans(vector<string> &ans);

//input and start function
void input_words(string &start, string &dest);

// read lexicon from file
void read_english(set<string> &english);

void show_ans(vector<string> &ans)
{
    cout << "Found ladder:";
    cout << ans[0];
    for (int i = 1; i < ans.size(); i++)
    {
        cout << "->" << ans[i];
    }
    cout << endl
         << endl;
}

void input_words(string &start, string &dest)
{
    cout << "Enter start word (enter ':q' to quit):";
    cin >> start;
    if (start == ":q")
    {
        exit(0);
    }
    cout << "Enter destination word:";
    cin >> dest;
}

void read_english(set<string> &english)
{
    while (true)
    {
        cout << "Please enter filename containing source text:";
        string file_name;
        cin >> file_name;
        ifstream file_input(file_name.c_str());
        if (file_input.is_open())
        {
            string temp_word;
            while (getline(file_input, temp_word))
            {
                english.insert(temp_word);
            }
            break;
        }
    }
}

int main()
{   
    // TODO: your code here
    set<string> english;        // initialize the english dictionary
    set<string> record;         // initialize record for the word that has appeared before
    vector<string> tmpld;       // initialize temporary ladder
    queue<vector<string>> search;   // initialize the search queue
    queue<vector<string>> ans;      // initialize the answer queue
    string start,dest,tmps;     // initialize start ,destination and temporary words
    read_english(english);      // read the english dictionary
    while(true){
        // clear the variables
        tmpld.clear();
        record.clear();
        tmps.clear();
        while(!search.empty())search.pop();
        while(!ans.empty())ans.pop();
        // input start and destinationthe words
        input_words(start,dest);
        for(int i = 0; i < start.size(); i++)if(isalpha(start[i]))tmps += tolower(start[i]);    // change words into valid form
        start = tmps;
        tmps = "";
        for(int i = 0; i < dest.size(); i++)if(isalpha(dest[i]))tmps += tolower(dest[i]);
        dest = tmps;
        tmps = "";
        int len = dest.size();    // record the length of word
        // start to find the word ladders
        tmpld.push_back(start);
        search.push(tmpld);
        int found_len = 0;        // record the length of the shortest word ladder, 0 represents not found yet
        while(!search.empty()){
            tmpld = search.front(); search.pop();
            if(found_len && found_len<tmpld.size())break;       // if the corrent ladder if longer than found ladder, break
            if(tmpld.back() == dest){           // if found ladder, record it
                ans.push(tmpld);
                found_len = tmpld.size();
            }
            if(!found_len){                     // if haven't found yet, generate longer ladders
                tmps = tmpld.back();
                for(int i = 0; i < 26; i++)for(int j = 0; j < len; j++){
                    char ch = 'a' + i; string tmps1 = tmps; tmps1[j] = ch;      // generate words differ with one char
                    if(tmps1 != tmps && english.count(tmps1) && !record.count(tmps1)){        // if the words is valid and not appeared before
                        tmpld.push_back(tmps1);     // add the corrent ladder to search
                        search.push(tmpld);
                        tmpld.pop_back();
                        if(tmps1 != dest)record.insert(tmps1);    // add the corrent ladder to record
                    }
                }
            }
        }
        if(ans.empty())cout << "No word ladder exists!" << endl;    // if no answer
        while(!ans.empty()){        // show all answers
            tmpld = ans.front();
            ans.pop();
            show_ans(tmpld);
        }
    }
    return 0;
}