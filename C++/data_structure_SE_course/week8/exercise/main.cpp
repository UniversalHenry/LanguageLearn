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


int default3(int c ,const int a = 30);

int main(void){
// time start
    double dur;
    clock_t start,end;
    start = clock();

// try here
    map<double,double> expression[2];
    int n[2];
    for(int i = 0; i < 2; i++){
        double c,e;
        std::cin >> n[i];
        for(int j = 0; j < n[i]; j++){
            cin >> c >> e;
            expression[i].insert(make_pair(e,c));
        }
    }
    map<double,double>::iterator term[2];
    term[1] = expression[1].begin();
    while(term[1] != expression[1].end()){
        term[0] = expression[0].find(term[1]->first);
        if(term[0] == expression[0].end()){ 
            expression[0].insert(*term[1]); 
        }
        else{ 
            term[0]->second += term[1]->second; 
        }
        term[1]++;
    }

    term[0] = expression[0].begin();
    if(term[0]->second > 0){
        if(term[0]->first == 0)std::cout << term[0]->second;
        else if(term[0]->first == 1)std::cout << term[0]->second << "x";
        else std::cout << term[0]->second << "x^" << term[0]->first;
    }
    if(term[0]->second < 0){
        if(term[0]->first == 0)std::cout << term[0]->second;
        else if(term[0]->first == 1)std::cout << term[0]->second << "x";
        else std::cout << term[0]->second << "x^" << term[0]->first;
    }
    term[0]++;
    while(term[0] != expression[0].end()){
        if(term[0]->second > 0){
            if(term[0]->first == 0)std::cout << "+" << term[0]->second;
            else if(term[0]->first == 1)std::cout << "+" << term[0]->second << "x";
            else std::cout << "+" << term[0]->second << "x^" << term[0]->first;
        }
        if(term[0]->second < 0){
            if(term[0]->first == 0)std::cout << term[0]->second;
            else if(term[0]->first == 1)std::cout << term[0]->second << "x";
            else std::cout << term[0]->second << "x^" << term[0]->first;
        }
        term[0]++;
    }

// try here
    
    
// time stop
    end = clock();
    dur = (double)(end - start);
    std::cout << endl << "UseTime:" << (dur / CLOCKS_PER_SEC) << endl;
    std::system("pause");
    return 0;
}