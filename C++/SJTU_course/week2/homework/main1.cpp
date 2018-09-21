#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;

int main(void) {
  long M = 1, N = 1;
  cin >> M >> N;
  long rec = 0, tmprec = 0;
  
  if(N<1e7){
  bool flag[N + 1];
    for(long i = 0; i<=N;i++)flag[i]=true;
    for (long i = 2; i < sqrt(N) + 1; i++)
      if (flag[i])
        for (long j = 2 * i; j <= N; j += i)
          flag[j] = false;
    for (long i = M;;) {
      if (flag[i]) {
        while (true) {
          i++;
          tmprec++;
          if (flag[i] || i >= N)
            break;
        }
      } else {
        i++;
      }
      if (flag[N]) {
        if (tmprec > rec && tmprec > 1)
          rec = tmprec;
      } else {
        if (i < N)
          if (tmprec > rec && tmprec > 1)
            rec = tmprec;
      }
      tmprec = 0;
      if (i >= N)
        break;
    }}
    else{
    	bool flag1[sqrt(N)/1e7+1][1e7];
    	bool flag[
    	for(long i = 0; i<sqrt(N);i++)flag[i/1e7][i%1e7]=true;
    for (long i = 2; i < sqrt(N) + 1; i++)
      if (flag[i/1e7][i%!e7)
        for (long j = 2 * i; j <= N; j += i)
          flag[j] = false;
    for (long i = M;;) {
      if (flag[i]) {
        while (true) {
          i++;
          tmprec++;
          if (flag[i] || i >= N)
            break;
        }
      } else {
        i++;
      }
      if (flag[N]) {
        if (tmprec > rec && tmprec > 1)
          rec = tmprec;
      } else {
        if (i < N)
          if (tmprec > rec && tmprec > 1)
            rec = tmprec;
      }
      tmprec = 0;
      if (i >= N)
        break;
    }
    } 
    
    cout << rec;

    cout << "Program finished.";
    int test;
    cin >> test;
    return 0;
  }