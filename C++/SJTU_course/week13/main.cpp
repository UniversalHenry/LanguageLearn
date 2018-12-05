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

struct transfer{
    int p1;
    int p2;
    double money;
    double date;
    bool used;
};

bool datejduge(struct transfer t1, struct transfer t2){
    return (t1.date - t2.date) <= 30;
}

int main()
{
    ifstream file("./transfer.txt/transfer.txt");
    ofstream out("transfer_loop.txt");
    vector<struct transfer> transfers;
    map<int, vector<int> > ptotransfer;
    string s;
    int i = 0;
    while(getline(file, s))
    {
        string tmp1, tmp2, tmp3;
        int start=0, end=0;
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
        ptotransfer[tmp.p1].push_back(i);
        ++i;
    }

    queue<vector<int> > q;
    vector<int> tmp;
    for(map<int, vector<int> >::iterator it = ptotransfer.begin(); it != ptotransfer.end(); ++it) {
        for(int j = 0; j < it -> second.size(); ++j)
        {
            tmp.push_back(it -> second[j]);
            transfers[it -> second[j]].used = 1;
            q.push(tmp);
            while(q.size() != 0)
            {
                tmp = q.front();
                q.pop();
                for(int m = 0; m < ((int)tmp.size()) - 2; ++m)
                {
                    if(transfers[tmp[m]].p1 == transfers[tmp[tmp.size() - 1]].p2)
                    {
                        cout << "Find:" << transfers[tmp[m]].p1;
                        out << "Find:" << transfers[tmp[m]].p1;
                        for(m; m < tmp.size(); ++m)
                        {
                            cout << " -> " << transfers[tmp[m]].p2;
                            out << " -> " << transfers[tmp[m]].p2;
                        }

                        cout << endl;
                        out << endl;
                    }
                }
                int n = transfers[tmp[tmp.size() - 1]].p2;
                for(int k = 0; k < ptotransfer[n].size(); ++k)
                {
                    if(!transfers[ptotransfer[n][k]].used && datejduge(transfers[ptotransfer[n][k]], transfers[tmp[tmp.size() - 1]]))
                    {
                        tmp.push_back(ptotransfer[n][k]);
                        transfers[ptotransfer[n][k]].used = 1;
                        q.push(tmp);
                        tmp.pop_back();
                    }
                }
            }
            tmp.clear();
        }
    }

    int test;
    cin >> test;
    return 0;
}
