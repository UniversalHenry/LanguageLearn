/*
 * File: WordLadder.cpp
 * --------------------
 * 陆昊成 517021910649
 * Name:
 * Student ID:
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
    set<string> english;
    set<string> record;
    vector<string> tmpld;
    queue<vector<string>> search;
    queue<vector<string>> ans;
    string start,dest,tmps;
    read_english(english);
    while(true){   
        tmpld.clear();record.clear();tmps.clear();
        while(!search.empty())search.pop();
        while(!ans.empty())ans.pop();
        input_words(start,dest);
        for(int i=0;i<start.size();i++)if(isalpha(start[i]))tmps+=tolower(start[i]);
        start=tmps;tmps="";
        for(int i=0;i<dest.size();i++)if(isalpha(dest[i]))tmps+=tolower(dest[i]);
        dest=tmps;tmps="";
        int len=dest.size();
        tmpld.push_back(start);
        search.push(tmpld);
        int found_len=0;
        while(!search.empty()){
            tmpld=search.front();search.pop();
            if(found_len && found_len<tmpld.size())break;
            if(tmpld.back()==dest){ans.push(tmpld);found_len=tmpld.size();}
            if(!found_len){
                tmps = tmpld.back();
                for(int i=0;i<26;i++)for(int j=0;j<len;j++){
                    char ch='a'+i; string tmps1=tmps; tmps1[j]=ch;
                    if(tmps1!=tmps && english.count(tmps1) && !record.count(tmps1)){
                        tmpld.push_back(tmps1);
                        search.push(tmpld);
                        tmpld.pop_back();
                        if(tmps1!=dest)record.insert(tmps1);
                    }
                }
            }
        }
        if(ans.empty())cout << "No word ladder exists!" << endl;
        while(!ans.empty()){
            tmpld=ans.front();ans.pop();
            show_ans(tmpld);
        }
    }
    return 0;
}