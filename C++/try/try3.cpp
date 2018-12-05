#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

using namespace std;

int main() {
    char filename[] = "exciting";
    // ofstream file("exciting",ios::binary);
    char *buffer;
    long size;
    ifstream in (filename, ios::in|ios::binary|ios::ate);
    size = in.tellg();
    in.seekg (0, ios::beg);
    buffer = new char [size];
    in.read(buffer, size);
    in.close();

    cout << buffer;

    delete[] buffer;
    system("pause");
    return 0;
}
