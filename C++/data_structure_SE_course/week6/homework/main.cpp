#include <iostream>
#include <cstdlib> 
#include <cstdio>
#include <fstream>
#include <vector>
#include <ctime>

using namespace std;

double calculate(const double &d1, const double &d2, const int &way){
    switch(way){
        case 0:return d1 + d2;
        case 1:return d1 - d2;
        case 2:return d1 * d2;
        case 3:return d1 / d2;
    }
}

bool calculate_all(const vector<double> &number, const double &target){
    // for(int i = 0; i < number.size(); i++)cout << number[i] << '\t';
    // cout << endl;
    if(number.size() == 1){
        if(number[0] == target || -number[0] == target) return true;
        if(number[0] != 0 && 1/number[0] == target) return true;
        return false;
    }
    for(int i = 0; i < 4; i++){
        // cout << '/' << i << endl;
        int n = number.size();
        for(int j = 0; j < n - 1; j++){
            vector<double> tmpn(number.begin(),number.end());
            try{
                tmpn[j] = calculate(number[n - 1],number[j],i);
            }
            catch(...){
                continue;
            }
            tmpn.pop_back();
            if(calculate_all(tmpn,target)) return true;
        }
    }
    return false;
}
int main(void){

// main function here

    vector<double> number;
    vector<int> ways;
    double tmp = 0;
    int N = 0;

    cin >> N;
    cin >> tmp;
    const double target = tmp;
    for(int i = 0; i < N; i++){
        cin >> tmp;
        number.push_back(tmp);
    }
// // time start
//     double dur;
//     clock_t start,end;
//     start = clock();
    if(calculate_all(number,target)) cout << "True";
    else cout << "False";

// // time stop
//     end = clock();
//     dur = (double)(end - start);
//     printf("\nUseTime:%f",(dur / CLOCKS_PER_SEC));
//     cout << "\nProgram finished.";
//     cin >> dur;
    return 0;
}


