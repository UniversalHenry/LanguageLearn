// Computing Introduction Course
// Chapter 10
// Exercise 8

#include <iostream>
#include <list>

using namespace std;

class Joseph
{
  private:
    int num, val;

  public:
    Joseph(int n, int v = 2) : num(n), val(v){};
    void simulate();
};

void Joseph::simulate()
{
    if (num > 1 && val > 1)
    {
        list<int> ls;
        cout << "All numbers:";
        for (int i = 0; i < num; i++)
        {
            ls.push_back(i);
            cout << i << " ";
        }
        cout << endl;
        int loop = 0;
        list<int>::iterator p = ls.begin();
        while (loop < num)
        {
            for (int i = 0; i < val - 1; i++)
            {
                p++;
                if (p == ls.end())
                    p = ls.begin();
            }
            loop++;
            cout << "--------------------------------------------" << endl;
            cout << "Loop:" << loop << endl;
            cout << "Erase number:" << *p << endl;
            p = ls.erase(p);
            if (p == ls.end())
                p = ls.begin();
            cout << "Left number(s):";
            for (list<int>::iterator x = ls.begin(); x != ls.end(); x++)
                cout << *x << " ";
            cout << endl;
        }
    }
    else
        cout << "Wrong input!" << endl;
}

int main()
{
    /*
    example input:
        10
        3
    output:
        Input number:10
        Input interval:3
        All numbers:0 1 2 3 4 5 6 7 8 9
        --------------------------------------------
        Loop:1
        Erase number:2
        Left number(s):0 1 3 4 5 6 7 8 9
        --------------------------------------------
        Loop:2
        Erase number:5
        Left number(s):0 1 3 4 6 7 8 9
        --------------------------------------------
        Loop:3
        Erase number:8
        Left number(s):0 1 3 4 6 7 9
        --------------------------------------------
        Loop:4
        Erase number:1
        Left number(s):0 3 4 6 7 9
        --------------------------------------------
        Loop:5
        Erase number:6
        Left number(s):0 3 4 7 9
        --------------------------------------------
        Loop:6
        Erase number:0
        Left number(s):3 4 7 9
        --------------------------------------------
        Loop:7
        Erase number:7
        Left number(s):3 4 9
        --------------------------------------------
        Loop:8
        Erase number:4
        Left number(s):3 9
        --------------------------------------------
        Loop:9
        Erase number:9
        Left number(s):3
        --------------------------------------------
        Loop:10
        Erase number:3
        Left number(s):
    */
    int n, v;
    cout << "Input number:";
    cin >> n;
    cout << "Input interval:";
    cin >> v;
    Joseph obj(n, v);
    obj.simulate();
    system("pause");
    return 0;
}
