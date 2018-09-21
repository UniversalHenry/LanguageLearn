#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cmath>
using namespace std;

int main(void)
{
  //initialization
  long M = 1, N = 1;
  cin >> M >> N;
  int rec = 0, tmprec = 0;
  const int t = N-M+1;
  bool flag[t];
  //compute prime between M & N
  if(M<=1e6 || t-1<100){
    const int n = int(sqrt(N))+1;
    bool tmp;
    for(int j = 0; j < t;j++)flag[j]=false;
    if(M%2==1){for(int j = 0; j < t;j+=2){tmp=true;for(int i = 3; i < n; i+=2){if((M+j)%i==0&&(M+j)/i>1){tmp = false;break;}}flag[j]=tmp;}}
    else{for(int j = 1; j < t;j+=2){tmp=true;for(int i = 3; i < n; i+=2){if((M+j)%i==0&&(M+j)/i>1){tmp = false;break;}}flag[j]=tmp;}}
    if(M==1){flag[0]=false;flag[1]=true;}
    if(M==2){flag[0]=true;}
  }else{
    const int n = int(sqrt(t))+1;
    const long n1 = int(sqrt(N))+1;
    bool prime[n];
    for(int i = 2; i < n; i++)prime[i]=true;
    for(int j = 0; j < t;j++)flag[j]=true;
    //compute basic prime
    for(int i = 2; i < n; i++){if(prime[i])for (int j = 2 * i; j < n; j += i)prime[j] = false;}
    //compute prime between M & N
    for(int j = 0; j < t;j++)for(int i = 2; i < n;i++)if(flag[j] && prime[i] && (j+M)%i ==0 && (j+M)/i >1){
      int k = j;
      while(true){
        flag[k]=false;
        k+=i;
        if(k>=t)break;
        }
    }
    bool tmp ;
    if(M%2==1){for(int j = 0; j < t;j+=2)if(flag[j]){tmp=true;for(long i = 3; i < n1; i+=2){if((M+j)%i==0){tmp = false;break;}}flag[j]=tmp;}}
    else{for(int j = 1; j < t;j+=2)if(flag[j]){tmp=true;for(long i = 3; i < n1; i+=2){if((M+j)%i==0){tmp = false;break;}}flag[j]=tmp;}}
  }

  //compute distance
  int i = 0;
  while(true){
    if (flag[i]){
      while (true){
        i++;tmprec++;
        if (flag[i] || i >= t)break;
      }
    }else{i++;}
    if(flag[t-1] && flag[0]){if (tmprec > rec) rec = tmprec;}
    else if(flag[t-1] && !flag[0]){if (tmprec!=t-1 && tmprec > rec) rec = tmprec;}
    else{if(i < t)if(tmprec > rec)rec = tmprec;}
    tmprec = 0;
    if (i >= t)break;
  }
  cout << rec;

  cout << "\nProgram finished.";
  int test;
  cin >> test;
  return 0;
}