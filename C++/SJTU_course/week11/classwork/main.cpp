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
#include <algorithm>

using namespace std;

int main(void){

// try here
    ifstream data("circles.txt");
    vector<double> xs,ys,rs;
    while(true){
        double x,y,r;
        data >> x >> y >> r;
        if(data.eof()) break;
        xs.push_back(x);
        ys.push_back(y);
        rs.push_back(r);
    }
    
    int n;
    cout << "Input the precision:";
    cin >> n;
    // time start
    double dur;
    clock_t start,end;
    start = clock();
    double const dx = pow(10,-n);
    double s = 0;
    vector<double> x_m_r;
    vector<double> x_p_r;
    for(int i = 0; i < xs.size(); i++){
        x_m_r.push_back(xs[i] - rs[i]);
        x_p_r.push_back(xs[i] + rs[i]);
    }
    vector<double>::iterator px_min = min_element(x_m_r.begin(),x_m_r.end());
    vector<double>::iterator px_max = max_element(x_p_r.begin(),x_p_r.end());
    // cout << *px_max << *px_min;
    for(double x = *px_min; x < *px_max; x += dx){
        double y = 0;
        multimap<double,double> points;
        for(int i = 0; i < ys.size(); i++){
            if(x_m_r[i] < x && x_p_r[i] > x){
                // cout << x << endl;
                double y_low;
                double y_len = sqrt(rs[i] * rs[i] - (xs[i] - x) * (xs[i] - x));
                y_low = ys[i] - y_len;
                points.insert(make_pair(y_low,2 * y_len));
            }
        }
        if(points.empty())continue;

        multimap<double,double>::iterator the_point;
        the_point = points.begin();
        while(the_point != points.end()){
            multimap<double,double>::iterator the_point2;
            the_point2 = the_point;
            the_point2++;
            while(the_point2 != points.end()){
                double d = the_point2->first - the_point->first;
                if(d > the_point->second){
                    break;
                }
                else{
                    if(the_point->second < d + the_point2->second){
                        the_point->second = d + the_point2->second;
                    }
                    points.erase(the_point2);
                    the_point2 = the_point;
                    the_point2++;
                    if(the_point2 == points.end()) break;
                }
            }
            // cout << the_point->first << endl;
            the_point++;
        }
        the_point = points.begin();
        while(the_point != points.end()){
            y += the_point->second;
            the_point++;
        }
        s += y * dx;
    }
    cout << s;

// time stop
    end = clock();
    dur = (double)(end - start);
    cout << endl << "UseTime:" << (dur / CLOCKS_PER_SEC) << endl;
    system("pause");
    return 0;
}
