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
// time start
    double dur;
    clock_t start,end;
    start = clock();

// try here
    
    char *wday[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
    time_t timep = 1477418957;
    struct tm *p;
   
    //time(&timep); /*获得time_t结构的时间，UTC时间*/
    cout << timep;
    p = gmtime(&timep); /*转换为struct tm结构的UTC时间*/
    printf("%d/%d/%d ", 1900 + p->tm_year, 1 + p->tm_mon, p->tm_mday);
    printf("%s %d:%d:%d\n", wday[p->tm_wday], p->tm_hour,
        p->tm_min, p->tm_sec);

    
// time stop
    end = clock();
    dur = (double)(end - start);
    printf("\nUseTime:%f",(dur / CLOCKS_PER_SEC));
	cout << "\nProgram finished.";
    cin >> dur;
    return 0;
}