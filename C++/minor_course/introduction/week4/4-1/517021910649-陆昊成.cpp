// Computing Introduction Course 
// Chapter 4
// Exercise 1

#include <iostream>

using namespace std;

int main()
{   
    for(int x=1;x<10;x++){
        for(int y=1;y<10;y++){
            for(int z=0;z<10;z++){
                if(100*x+10*y+z+100*y+11*z==532 && x!=y && y!=z && z!=x){
                    cout << "x=" << x << "\ty=" << y << "\tz=" << z << endl;
                }
            }
        }
    }
    
    system("pause");
	return 0;
}
