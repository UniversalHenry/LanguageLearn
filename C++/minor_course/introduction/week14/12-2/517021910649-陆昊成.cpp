// Computing Introduction Course
// Chapter 12
// Exercise 2

#include <iostream>

using namespace std;

class MyIntArray
{
protected:
    int size;
    int *p;

public:
    MyIntArray(int s = 1) : size(s), p(0)
    {
        if (size <= 0)
            size = 1;
        p = new int[size];
        for (int i = 0; i < size; i++)
            p[i] = 0;
    };
    ~MyIntArray() { delete[] p; }
    int &operator[](int n)
    {
        if (n >= size)
        {
            cout << endl
                 << "Bounds Error!" << endl;
            return p[size - 1];
        }
        else if (n < 0)
        {
            cout << endl
                 << "Bounds Error!" << endl;
            return p[0];
        }
        else
            return p[n];
    }
};

class MyDynamicIntArray : public MyIntArray
{
public:
    MyDynamicIntArray(int s = 1) : MyIntArray(s){};
    void operator()(int n)
    {
        if (n <= 0)
            n = 1;
        int *p_ = new int[n];
        int s = n < size ? n : size;
        for (int i = 0; i < s; i++)
            p_[i] = p[i];
        for (int i = s; i < n; i++)
            p_[i] = 0;
        size = n;
        delete[] p;
        p = p_;
    }
};

int main()
{
    /*
    example input:
        
    output:

        Bounds Error!
        0 1 2 3 4 5 6 7 8 10
        Bounds Error!
        10 0 1 2 3 4 5 6 7 8 10 0 0 0 0 0 0 0 0 0 0
        Bounds Error!
        0 0 1 2 3 4
        Bounds Error!
        4
    */
    MyDynamicIntArray da(10);
    for (int i = 0; i < 11; i++)
        da[i] = i;
    for (int i = 0; i < 11; i++)
        cout << da[i] << " ";
    da(20);
    for (int i = 0; i < 21; i++)
        cout << da[i] << " ";
    da(5);
    for (int i = 0; i < 6; i++)
        cout << da[i] << " ";
    cout << endl;
    system("pause");
    return 0;
}