#include <iostream>
#include <stdlib.h>
#include <string>
using namespace std;
int test;

int main(void)
{
    string s ="";
    string out ="";
    char c = '\0';
    bool flag = false;
    while (true){
        c=cin.get();
        if(c=='\n')break;
        if(c!=' '){s=s+c;flag=true;}
        if(c==' '&&flag){out=s+' '+out;s="";flag=false;}
    }
    if (out ==""){
        cout << "Invalid";
    }
    else{
        if(c!=' ')out=s+' '+out;
        out = out.substr(0,out.length()-1);
        cout << out;
    }

    cin >> test;
    return 0;
}