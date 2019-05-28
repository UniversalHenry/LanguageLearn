#include <iostream>
#include <stdlib.h> 
using namespace std;
int test;

int main(void){
    int num=0;
    cin >> num;
    int rec[num];
    bool flag = true;
    for(int i = 0; i < num; ++i){cin >> rec[i];}
    for(int i = 0; i < num; ++i){
        flag = true;
        for(int j = 0; j < num; ++j)if(i!=j && rec[i]==rec[j]){flag = false;break;}
        if(flag){cout << rec[i];break;}
    }
    cin >> test;
    return 0;
}