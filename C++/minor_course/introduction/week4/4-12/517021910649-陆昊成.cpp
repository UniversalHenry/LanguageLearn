// Computing Introduction Course 
// Chapter 4
// Exercise 12

#include <iostream>
#include <cstring>

using namespace std;

int main()
{   
    int a=0,b=0,s=0,o=0;
    while(true){
        char c;
        cin.get(c);
        if(c<='Z'&&c>='A')c+='a'-'A';
        if(c=='.'){
            o++;
            break;
        }
        else if(c=='a'||c=='e'||c=='i'||c=='o'||c=='u')a++;
        else if(c<='z'&&c>='a')b++;
        else if(c==' ')s++;
        else o++;
    }
    cout << "Vowels:\t\t" << a <<endl;
    cout << "Consonants:\t" << b << endl;
    cout << "Spaces:\t\t" << s << endl;
    cout << "Other symbols:\t" << o <<endl;
    system("pause");
	return 0;
}
