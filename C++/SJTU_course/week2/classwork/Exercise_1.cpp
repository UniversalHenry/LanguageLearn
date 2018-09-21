/*
** 作者: 王贇超
** 输入: 文本, 查询目标
** 输出: 目标数量, 目标位置
** 说明: 这个联系结果可以多样, 取决于"单词"的定义
*/
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<map>
#include<vector>
#include<sstream>
#include<stdio.h>

using namespace std;

int main()
{
    fstream file;
    file.open("lesson/shakespeare.txt", ios::in);
    vector<char> ignoreSet;
    ignoreSet.push_back('#');
    ignoreSet.push_back(',');
    ignoreSet.push_back('.');
    ignoreSet.push_back('?');
    ignoreSet.push_back('!');
    ignoreSet.push_back('[');
    ignoreSet.push_back(']');
    ignoreSet.push_back('{');
    ignoreSet.push_back('}');
    ignoreSet.push_back('*');
    ignoreSet.push_back('>');
    ignoreSet.push_back('<');
    ignoreSet.push_back(':');
    if(file.is_open())
    {
        map<string, vector<vector<string>>> dict;
        int lineNum = 0;
        string preWord = "";
        while(!file.eof())
        {
            string line = "";
            getline(file, line);
            lineNum++;
            if(line == "by William Shakespeare")
            {
                lineNum = 1;
            }
            if(line[line.length()-1] == '-')
            {
                string temp = "";
                file >> temp;
                line = line.substr(0, line.length() - 1) + temp;
            }
            for (int i = 0; i < ignoreSet.size();i++)
            {
                int index = line.find(ignoreSet[i]);
                while(index != -1)
                {
                    line.replace(index, 1, " ");
                    index = line.find(ignoreSet[i]);
                }
            }
            stringstream ss(line);
            int wordNum = 0;
            while (!ss.eof())
            {
                string word = "";
                ss >> word;
                wordNum++;
                if(word == "")
                {
                    continue;
                }
                if(preWord != "")
                {
                    dict[preWord][dict[preWord].size() - 1][3] = word;
                }
                vector<string> info;
                info.push_back(to_string(lineNum));
                info.push_back(to_string(wordNum));
                info.push_back(preWord);
                info.push_back("");
                auto it = dict.find(word);
                if(it == dict.end())
                {
                    dict[word] = vector<vector<string>>();
                }
                dict[word].push_back(info);
                preWord = word;
            }
        }
        while(true)
        {
            cout << "Please enter the word you want to find: ";
            string target = "";
            cin >> target;
            auto it = dict.find(target);
            if(it == dict.end())
            {
                cout << "no such word!" << endl;
            }
            else
            {
                vector<vector<string>> tempV = it->second;
                for (int i = 0; i < it->second.size();i++)
                {
                    printf("(%-*s,%-*s) pre:%-*s after:%-*s\n", 6, tempV[i][0].c_str(), 6, tempV[i][1].c_str(), 10, tempV[i][2].c_str(), 10, tempV[i][3].c_str());
                }
                cout << "word number: " << it->second.size() << endl;
            }
        }
    }
    cout << "ProgramFinished.";
    int test;
    cin >> test;
}