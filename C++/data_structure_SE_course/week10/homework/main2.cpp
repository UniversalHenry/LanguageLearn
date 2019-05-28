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
    while(true){
        stringstream ss;
        ss << s;
        ss >> height;
        heights.push_back(height);
        ss >> s;
        if(s.empty() || s[0] != ',') break;
        else s = s.substr(1);
    }
    for(int i = 0; i < heights.size(); i++){
        int width = 0;
        for(int j = i; j < heights.size(); j++){
            if(heights[j] >= heights[i]) width++;
            else break;
        }
        for(int j = i; j >= 0; j--){
            if(heights[j] >= heights[i]) width++;
            else break;
        }
        width--;
        int tmp = width * heights[i];
        if(tmp > num) num = tmp;
    }
    cout << num;
    system("pause");
    return 0;
}