#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <queue>
#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
#include <set>
#include <map>
#include <ctime>
#include <cstring>

using namespace std;

struct Info
{
    string id,title,detail;
    int year;
    string org;
};

int main()
{
    vector<string> files = 
    {"C:\\Users\\Administrator\\Desktop\\GitHub\\LanguageLearn\\exefile\\papers\\aminer_papers_0.txt",
    "C:\\Users\\Administrator\\Desktop\\GitHub\\LanguageLearn\\exefile\\papers\\aminer_papers_1.txt",
    "C:\\Users\\Administrator\\Desktop\\GitHub\\LanguageLearn\\exefile\\papers\\aminer_papers_2.txt",
    "C:\\Users\\Administrator\\Desktop\\GitHub\\LanguageLearn\\exefile\\papers\\aminer_papers_3.txt",
    "C:\\Users\\Administrator\\Desktop\\GitHub\\LanguageLearn\\exefile\\papers\\aminer_papers_4.txt"};

    string s;
    map<string,vector<pair<int,streamoff> > > idInfo; // author , pointer in file
    map<string,int> refInfo; // id, ref times

    cout << "Indexing..." << endl;
    // time start
    double dur;
    clock_t Tstart,Tend;
    Tstart = clock();
    Info tmpInfo;


    for(int i = 0; i < 5; i++){
        ifstream file(files[i].c_str());
        streamoff p = file.tellg();
        while (getline(file, s))
        {
            // author
            {
                string tmps;
                int start = 0, end = 0;
                start = s.find("authors");
                if(start > 0){
                    start = s.find("[",start) + 1;
                    end = s.find("]",start);
                    tmps = s.substr(start,end - start);
                    start = 0;
                    while(true){
                        string author,name;
                        start = tmps.find("{",start) + 1;
                        if(start <= 0) break;
                        end = tmps.find("}",start);
                        author = tmps.substr(start,end - start);

                        int st = 0, ed = 0;
                        st = author.find("name");
                        st = author.find(":",st);
                        st = author.find("\"",st) + 1;
                        ed = author.find("\"",st);
                        name = author.substr(st,ed - st);
                        idInfo[name].push_back(make_pair(i,p));
                    }
                }
            }
            p = file.tellg();
        }
        // time stop
        Tend = clock();
        cout << "Step1:" << i;
        dur = (double)(Tend - Tstart);
        cout << endl << "UseTime:" << (dur / CLOCKS_PER_SEC) << endl;
    }

    for(int i = 0; i < 5; i++){
        ifstream file(files[i].c_str());
        while (getline(file, s))
        {
            // ref
            {
                string tmps;
                int start = 0, end = 0;
                start = s.find("references");
                if(start > 0){
                    start = s.find("[",start) + 1;
                    end = s.find("]",start);
                    tmps = s.substr(start,end - start);
                    start = 0;
                    while(true){
                        string ref;
                        start = tmps.find("\"",start) + 1;
                        if(start <= 0) break;
                        end = tmps.find("\"",start);
                        ref = tmps.substr(start,end - start);
                        if(refInfo.count(ref)){
                            refInfo[ref]++;
                        }else{
                            refInfo[ref] = 0;
                        }
                        start = tmps.find(",",start) + 1;
                        if(start <= 0) break;
                    }
                }
            }
        }
        // time stop
        cout << "Step2:" << i;
        Tend = clock();
        dur = (double)(Tend - Tstart);
        cout << endl << "UseTime:" << (dur / CLOCKS_PER_SEC) << endl;
    }
    cout << idInfo.size() << endl;
    cout << refInfo.size() << endl;

    while(true){
        // time start
        string tarAuthor;
        cin >> tarAuthor;
        string s;
        vector<Info> tarInfo;
        multimap<int, string> tarTitle;
        multimap<int, string> tarOrg;
        map<string, int> tarRef;
        cout << "Searching..." << endl;
        double dur;
        clock_t Tstart,Tend;
        Tstart = clock();
        Info tmpInfo;
        if(idInfo.count(tarAuthor) == 0) continue;
        auto the_author = idInfo.find(tarAuthor)->second;
        for(int j = 0; j < the_author.size(); j++){
            int i = the_author[j].first;
            streamoff p = the_author[j].second;
            ifstream file(files[i].c_str());
            file.seekg(p);
            getline(file, s);
            // id
            {
                int start = 0, end = 0;
                start = s.find("id");
                start = s.find(":",start);
                start = s.find("\"",start) + 1;
                end = s.find("\"",start);
                tmpInfo.id = s.substr(start,end - start);
            }
            // title
            {
                int start = 0, end = 0;
                start = s.find("title");
                if(start > 0){
                    start = s.find(":",start);
                    start = s.find("\"",start) + 1;
                    end = s.find("\"",start);
                    tmpInfo.title = s.substr(start,end - start);
                }
            }
            // year
            {
                int year = 0;
                int start = 0, end = 0;
                start = s.find("year");
                if(start > 0){
                    start = s.find(":",start) + 2;
                    string tmps = s.substr(start,4);
                    tmpInfo.year = atoi(tmps.c_str());
                }
                else tmpInfo.year = 0;
            }
            {
                tmpInfo.detail = s;
                tarInfo.push_back(tmpInfo);
                tarTitle.insert(make_pair(tmpInfo.year,tmpInfo.title));
                tarOrg.insert(make_pair(tmpInfo.year, tmpInfo.org));
                tarRef[tmpInfo.id] = 0;
            }
            

        }

        cout << endl << "#####DETAILS######" << endl << endl;
        for(auto it = tarInfo.begin(); it != tarInfo.end(); it ++) cout << it->detail << endl << endl;

        cout << endl << "#####TITLES######" << endl << endl;
        for(auto it = tarTitle.begin(); it != tarTitle.end(); it ++) cout << it->first << "\t" << it->second << endl;

        cout << endl << "#####ORGS######" << endl << endl;
        for(auto it = tarOrg.begin(); it != tarOrg.end(); it ++) cout << it->first << "\t" << it->second << endl;

        cout << endl << "#####REFS######" << endl << endl;
        int cite = 0;
        for(auto it = tarRef.begin(); it != tarRef.end(); it ++){
            cout << it->first << "\t" << it->second << endl;
            cite += it->second;
        }
        cout << "ALL CITATION:" << cite << endl;
        
        // time stop
        Tend = clock();
        dur = (double)(Tend - Tstart);
        cout << endl << "UseTime:" << (dur / CLOCKS_PER_SEC) << endl;
    }

    Tend = clock();
    dur = (double)(Tend - Tstart);
    cout << endl << "UseTime:" << (dur / CLOCKS_PER_SEC) << endl;

    system("pause");
    return 0;

}