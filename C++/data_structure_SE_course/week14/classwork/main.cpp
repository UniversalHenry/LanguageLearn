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
#include <queue>

using namespace std;

struct record{
    int outer;
    int inner;
    double money;
    int y;
    int m;
    int d;
};

int main(void){
// time start
    double dur;
    clock_t start,end;
    start = clock();

// try here
    ifstream input("./transfer.txt/transfer.txt");
    map<int, vector<int> > rec;
    vector<record> rec_tem;
    string s;
    while(getline(input,s)){
        record tmp_rec;
        stringstream ss;
        ss << s;
        ss >> tmp_rec.outer >> s >> tmp_rec.inner >> s >> tmp_rec.money >> s;
        ss >> tmp_rec.y;
        ss.get();
        ss >> tmp_rec.m;
        ss.get();
        ss >> tmp_rec.d;
        rec_tem.push_back(tmp_rec);
        rec[tmp_rec.outer].push_back(tmp_rec.inner);
    }  

    queue<vector<int> > bfs;
    vector<int> tmp;
    map<int, vector<int> >::iterator p;
    p = rec.begin();
    while(p!=rec.end()){
        tmp.push_back(p->first);
        for(int i = 0; i < p->second.size(); i++){
        }
        p++;
    }

    
// time stop
    end = clock();
    dur = (double)(end - start);
    cout << endl << "UseTime:" << (dur / CLOCKS_PER_SEC) << endl;
    system("pause");
    return 0;
}

int what_day(const record &r){
    int y = r.y,m = r.m,d = r.d;
    int sum;
    switch(m)
    {
        case 1:sum=0;break;
        case 2:sum=31;break;
        case 3:sum=59;break;
        case 4:sum=90;break;
        case 5:sum=120;break;
        case 6:sum=151;break;
        case 7:sum=181;break;
        case 8:sum=212;break;
        case 9:sum=243;break;
        case 10:sum=273;break;
        case 11:sum=304;break;
        case 12:sum=334;break;
    }
    sum=sum+d;
    if(((y%4 == 0 && y%100 != 0) || y%400==0) && m>2) sum=sum+1;
    return sum;
}

bool judge_time(const record &r1,const record &r2){
    if(abs(r1.y - r2.y) > 1) return false;
    int d = abs((r1.y - r2.y) * 365 + what_day(r1) - what_day(r2));
    return (d < 31);
}