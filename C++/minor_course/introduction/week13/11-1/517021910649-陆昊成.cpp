// Computing Introduction Course
// Chapter 11
// Exercise 1

#include <iostream>

using namespace std;

class Time
{
  private:
    void reshape();

  public:
    int h, m, s;
    Time(int h0 = 0, int m0 = 0, int s0 = 0) : h(h0), m(m0), s(s0){};
    Time &operator+=(const Time &t);
    Time &operator+=(const int &ss);
    Time &operator-=(const Time &t);
    Time &operator-=(const int &ss);
    Time operator++();
    Time operator++(int);
    Time operator--();
    Time operator--(int);
    friend Time operator-(const Time &t1, const Time &t2);
    friend ostream &operator<<(ostream &os, Time &t);
    friend istream &operator>>(istream &is, Time &t);
};

void Time::reshape()
{
    m += s / 60;
    s %= 60;
    if (s < 0)
    {
        s += 60;
        m--;
    }
    h += m / 60;
    m %= 60;
    if (m < 0)
    {
        m += 60;
        h--;
    }
}

Time &Time::operator+=(const Time &t)
{
    h += t.h;
    m += t.m;
    s += t.s;
    reshape();
    return *this;
}

Time &Time::operator+=(const int &ss)
{
    s += ss;
    reshape();
    return *this;
}

Time &Time::operator-=(const Time &t)
{
    h -= t.h;
    m -= t.m;
    s -= t.s;
    reshape();
    return *this;
}

Time &Time::operator-=(const int &ss)
{
    s -= ss;
    reshape();
    return *this;
}

Time Time::operator++()
{
    s++;
    reshape();
    return *this;
}

Time Time::operator++(int)
{
    Time t = *this;
    s++;
    reshape();
    return t;
}

Time Time::operator--()
{
    s--;
    reshape();
    return *this;
}

Time Time::operator--(int)
{
    Time t = *this;
    s--;
    reshape();
    return t;
}

Time operator-(const Time &t1, const Time &t2)
{
    Time t;
    t.h = t1.h - t2.h;
    t.m = t1.m - t2.m;
    t.s = t1.s - t2.s;
    t.reshape();
    return t;
}

ostream &operator<<(ostream &os, Time &t)
{
    t.reshape();
    os << t.h << ":" << t.m << ":" << t.s;
}

istream &operator>>(istream &is, Time &t)
{
    cout << endl
         << "Input hour:";
    cin >> t.h;
    cout << "Input minute:";
    cin >> t.m;
    cout << "Input second:";
    cin >> t.s;
    t.reshape();
    cout << "The time is " << t << "." << endl;
}

int main()
{
    /*
    example input:
        1
        1
        1
        2
        2
        2
        1
        1
        100
        2
        2
        100
        3
        1
        4
        2
        5
        1
        5
        2
        6
    output:
        ----------------------------------------
        Input Time1:
        Input hour:1
        Input minute:1
        Input second:1
        The time is 1:1:1.
        ----------------------------------------
        Input Time2:
        Input hour:2
        Input minute:2
        Input second:2
        The time is 2:2:2.
        ----------------------------------------
        Operator +=(1),-=(2),++(3),--(4),-(5),QUIT(6) :
        1
        ----------------------------------------
        Time1 or Time2(input 1 or 2, else QUIT):1
        How many sec to += ?100
        Time1 is 1:2:41
        ----------------------------------------
        Operator +=(1),-=(2),++(3),--(4),-(5),QUIT(6) :
        2
        ----------------------------------------
        Time1 or Time2(input 1 or 2, else QUIT):2
        How many sec to -= ?100
        Time2 is 2:0:22
        ----------------------------------------
        Operator +=(1),-=(2),++(3),--(4),-(5),QUIT(6) :
        3
        ----------------------------------------
        Time1 or Time2(input 1 or 2, else QUIT):1
        Time1 was 1:2:41
        Time1 is 1:2:42
        ----------------------------------------
        Operator +=(1),-=(2),++(3),--(4),-(5),QUIT(6) :
        4
        ----------------------------------------
        Time1 or Time2(input 1 or 2, else QUIT):2
        Time2 was 2:0:22
        Time2 is 2:0:21
        ----------------------------------------
        Operator +=(1),-=(2),++(3),--(4),-(5),QUIT(6) :
        5
        ----------------------------------------
        Time1 - Time2 or Time2 - Time1(input 1 or 2, else QUIT):1
        Time1 is 1:2:42
        Time2 is 2:0:21
        Time1 - Time2 is -1:2:21
        ----------------------------------------
        Operator +=(1),-=(2),++(3),--(4),-(5),QUIT(6) :
        5
        ----------------------------------------
        Time1 - Time2 or Time2 - Time1(input 1 or 2, else QUIT):2
        Time1 is 1:2:42
        Time2 is 2:0:21
        Time2 - Time1 is 0:57:39
        ----------------------------------------
        Operator +=(1),-=(2),++(3),--(4),-(5),QUIT(6) :
        6
    */
    Time t1, t2;
    cout << "----------------------------------------" << endl
         << "Input Time1:";
    cin >> t1;
    cout << "----------------------------------------" << endl
         << "Input Time2:";
    cin >> t2;
    while (1)
    {
        string order;
        cout << "----------------------------------------" << endl
             << "Operator +=(1),-=(2),++(3),--(4),-(5),QUIT(6) :" << endl;
        cin >> order;
        if (order == "1")
        {
            string od;
            cout << "----------------------------------------" << endl
                 << "Time1 or Time2(input 1 or 2, else QUIT):";
            cin >> od;
            if (od == "1")
            {
                int s;
                cout << "How many sec to += ?";
                cin >> s;
                t1 += s;
                cout << "Time1 is " << t1 << endl;
            }
            else if (od == "2")
            {
                int s;
                cout << "How many sec to += ?";
                cin >> s;
                t2 += s;
                cout << "Time2 is " << t2 << endl;
            }
        }
        else if (order == "2")
        {
            string od;
            cout << "----------------------------------------" << endl
                 << "Time1 or Time2(input 1 or 2, else QUIT):";
            cin >> od;
            if (od == "1")
            {
                int s;
                cout << "How many sec to -= ?";
                cin >> s;
                t1 -= s;
                cout << "Time1 is " << t1 << endl;
            }
            else if (od == "2")
            {
                int s;
                cout << "How many sec to -= ?";
                cin >> s;
                t2 -= s;
                cout << "Time2 is " << t2 << endl;
            }
        }
        else if (order == "3")
        {
            string od;
            cout << "----------------------------------------" << endl
                 << "Time1 or Time2(input 1 or 2, else QUIT):";
            cin >> od;
            if (od == "1")
            {
                cout << "Time1 was " << t1 << endl;
                t1++;
                cout << "Time1 is " << t1 << endl;
            }
            else if (od == "2")
            {
                cout << "Time2 was " << t2 << endl;
                t2++;
                cout << "Time2 is " << t2 << endl;
            }
        }
        else if (order == "4")
        {
            string od;
            cout << "----------------------------------------" << endl
                 << "Time1 or Time2(input 1 or 2, else QUIT):";
            cin >> od;
            if (od == "1")
            {
                cout << "Time1 was " << t1 << endl;
                t1--;
                cout << "Time1 is " << t1 << endl;
            }
            else if (od == "2")
            {
                cout << "Time2 was " << t2 << endl;
                t2--;
                cout << "Time2 is " << t2 << endl;
            }
        }
        else if (order == "5")
        {
            string od;
            cout << "----------------------------------------" << endl
                 << "Time1 - Time2 or Time2 - Time1(input 1 or 2, else QUIT):";
            cin >> od;
            if (od == "1")
            {
                cout << "Time1 is " << t1 << endl;
                cout << "Time2 is " << t2 << endl;
                Time t = t1 - t2;
                cout << "Time1 - Time2 is " << t << endl;
            }
            else if (od == "2")
            {
                cout << "Time1 is " << t1 << endl;
                cout << "Time2 is " << t2 << endl;
                Time t = t2 - t1;
                cout << "Time2 - Time1 is " << t << endl;
            }
        }
        else if (order == "6")
            break;
    }
    system("pause");
    return 0;
}
