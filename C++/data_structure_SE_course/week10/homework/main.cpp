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

int main(void){
    int num = 0;
    vector<int> heights;
    int height;
    string s;
    getline(cin,s);
    heights.push_back(0);
    while(true){
        stringstream ss;
        ss << s;
        ss >> height;
        heights.push_back(height);
        ss >> s;
        if(s.empty() || s[0] != ',') break;
        else s = s.substr(1);
    }
    while(!heights.empty()){
        int highest = 0, sec_highest = 0;
        for(int i = 0; i < heights.size(); i++) if(heights[highest] < heights[i]) highest = i;
        for(int i = 0; i < heights.size(); i++){
            if(i == highest) continue;
            if(heights[sec_highest] < heights[i]) sec_highest = i;
        }
        int min = (highest < sec_highest) ? highest : sec_highest;
        int max = (highest > sec_highest) ? highest : sec_highest;
        for(int i = max; i > min; i--) if(heights[i] < heights[sec_highest]) num += heights[sec_highest] - heights[i];
        for(int i = max; i > min; i--) heights.erase(heights.begin()+i);
        if(highest == sec_highest) break;
    }
    cout << num;
    system("pause");
    return 0;
}