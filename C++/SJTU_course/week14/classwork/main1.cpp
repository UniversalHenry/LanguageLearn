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

bool datejduge(struct transfer t1, struct transfer t2){
    return (t1.date - t2.date) <= 30;
}

int main()
{
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
                    money_info[transfers[i].money].push_back(transfers[i]);
            }
        }
    }
    cout << transfer_info.size() << endl;


    int loop_time = 0;
    while(true){
        int ans_size = -1;
        map<int, vector<int> > ans;
        // find ans
        for(auto it = transfer_info.begin(); it != transfer_info.end();){
            if(it->second.size() == 0)it = transfer_info
        }

        // output
        int t = 0;
        for (auto tmp = ans.begin(); tmp != ans.end(); tmp++)
        {
            t += tmp->second.size();
        }

        loop_time++;
        cout << "loop time:" << loop_time << endl;

        if (t >= 4)
        {
            cout << "size:\t" << s << endl;
            set<int> rec;
            int t = 0;
            for (auto tmp = ans.begin(); tmp != ans.end(); tmp++)
            {
                for (int i = 0; i < tmp->second.size(); i++)
                {
                    if (rec.count(tmp->second[i]) == 0)
                    {
                        rec.insert(tmp->second[i]);
                        cout << "(" << tmp->first << "," << tmp->second[i] << ")\t";
                        t++;
                        if (t % 5 == 0)
                            cout << endl;
                    }
                }
            }
            cout << endl;
        }
        if(t == 0) break;
    }


    system("pause");
    return 0;
}
