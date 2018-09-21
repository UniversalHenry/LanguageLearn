#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;

int main(void)
{
  long M = 1, N = 1;
  cin >> M >> N;
  long rec = 0, tmprec = 0;

  if (N < 1e6)
  {
    bool flag[N + 1];
    for (long i = 0; i <= N; i++)flag[i] = true;
    for (long i = 2; i < sqrt(N) + 1; i++)if (flag[i])for (long j = 2 * i; j <= N; j += i)flag[j] = false;
    for (long i = M;;){
      if (flag[i]){
        while (true){
          i++;tmprec++;
          if (flag[i] || i >= N)break;
        }
      }
      else{i++;}
      if (flag[N]){if(tmprec > rec && tmprec > 1)rec = tmprec;}
      else{if (i < N)if (tmprec > rec && tmprec > 1)rec = tmprec;}
      tmprec = 0;
      if (i >= N)break;
    }
  }
  else
  {
    const long c = 1e6;
    const long n = long(sqrt(N));
    bool *prime[n / c + 1 ];
    for(long i = 0;i <n / c + 1;i++)prime[i]=new bool[c];
    bool flag[N-M+1];
    for(long i = 0; i < n; i++)prime[i/c][i%c]=true;
    for(long i = 2; i < n; i++){if(prime[i/c][i%c])for (long j = 2 * i; j < n; j += i)prime[j/c][j%c] = false;}

    for(long j = 0; j < N-M+1;j++){
      for(long i = 2; i < n; i++){
        if (prime[i/c][i%c]){if((M+j)%i==0){flag[j]=false;break;}}
      }
    }

    for (long i = 0;;){
      if (flag[i]){
        while (true){
          i++;tmprec++;
          if (flag[i] || i >= N-M+1)break;
        }
      }
      else{i++;}
      if(flag[N-M+1]){if (tmprec > rec && tmprec > 1)rec = tmprec;}
      else{if (i < N-M+1)if (tmprec > rec && tmprec > 1)rec = tmprec;}
      tmprec = 0;
      if (i >= N-M+1)break;
    }
  }

  cout << rec;

  cout << "Program finished.";
  int test;
  cin >> test;
  return 0;
}