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

struct transfer
{
    int p1;
    int p2;
    double money;
    double date;
    bool used;
};

map<int,set<int> > date_info;

bool judgedata(int t1, int t2)
{
    auto tmp = date_info.find(t1);
    if(tmp == date_info.end()) return false;
    return tmp->second.count(t2);
}

int main()
{
    // time start
    double dur;
    clock_t start,end;
    start = clock();

    ifstream file("C:\\Users\\Administrator\\Desktop\\GitHub\\LanguageLearn\\exefile\\transfer.txt");
    ofstream out("transfer_loop.txt");
    vector<struct transfer> transfers;
    map<int, vector<int>> info;
    string s;
    int i = 0;
    while (getline(file, s))
    {
        string tmp1, tmp2, tmp3;
        int start = 0, end = 0;
        end = s.find(" | ");
        tmp1 = s.substr(start, end - start);
        start = end + 3;
        end = s.find(" | ", start);
        tmp2 = s.substr(start, end - start);
        start = end + 3;
        end = s.find(" | ", start);
        tmp3 = s.substr(start, end - start);
        start = end + 3;
        double tmp4 = atof(s.substr(start, 4).c_str()) * 365 + atof(s.substr(start + 5, 2).c_str()) * 30 + atof(s.substr(start + 8, 2).c_str());
        struct transfer tmp;
        tmp.p1 = atoi(tmp1.c_str());
        tmp.p2 = atoi(tmp2.c_str());
        tmp.money = atof(tmp3.c_str());
        tmp.date = tmp4;
        tmp.used = 0;
        transfers.push_back(tmp);
        info[tmp.p1].push_back(i);
        ++i;
    }

    cout << transfers.size() << endl;
    cout << "Preparing ..." << endl;
    map<int,vector<struct transfer> > transfer_info;
    map<int,vector<struct transfer> > money_info;
    for(int i = 0; i < transfers.size(); i++){
        for(int j = i+1; j < transfers.size(); j++){
            if(transfers[i].p1 == transfers[j].p2 && transfers[i].p2 == transfers[j].p1
                 && transfers[i].money == transfers[j].money){
                    transfer_info[transfers[i].p1].push_back(transfers[i]);
                    transfer_info[transfers[i].p2].push_back(transfers[i]);
                    money_info[transfers[i].money].push_back(transfers[i]);
            }
        }
        if(i % 1000 == 0){
        cout << i << endl;
        end = clock();
        dur = (double)(end - start);
        cout << endl << "UseTime:" << (dur / CLOCKS_PER_SEC) << endl;}
    }
    cout << transfer_info.size() << endl;

// time stop
    end = clock();
    dur = (double)(end - start);
    cout << endl << "UseTime:" << (dur / CLOCKS_PER_SEC) << endl;
    system("pause");
    return 0;
}