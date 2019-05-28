// Computing Introduction Course
// Chapter 12
// Exercise 8

#include <iostream>

using namespace std;

class Account
{
protected:
    static int order;
    double deposit;
    double ratio;

public:
    int account;
    Account(double d, double r) : account(++order), deposit(d), ratio(r) {}
    void changeRatio(double r) { ratio = r; }
    void saveMoney(double m) { deposit += m; }
    double showMoney() { return double(int(deposit * 100 + 0.5)) / 100; }
    double calcRatio()
    {
        double r = deposit * ratio;
        deposit += r;
        return r;
    }
    virtual double calcAllRatio() = 0;
};

int Account::order = 0;

class Account1 : public Account
{
public:
    Account1(double d, double r) : Account(d, r) { cout << "Generate 1 year account." << endl; }
    double calcAllRatio()
    {
        double r = 0;
        for (int i = 0; i < 1; i++)
            r += calcRatio();
        return r;
    }
};

class Account2 : public Account
{
public:
    Account2(double d, double r) : Account(d, r) { cout << "Generate 2 year account." << endl; }
    double calcAllRatio()
    {
        double r = 0;
        for (int i = 0; i < 2; i++)
            r += calcRatio();
        return r;
    }
};

class Account3 : public Account
{
public:
    Account3(double d, double r) : Account(d, r) { cout << "Generate 3 year account." << endl; }
    double calcAllRatio()
    {
        double r = 0;
        for (int i = 0; i < 3; i++)
            r += calcRatio();
        return r;
    }
};

class Account5 : public Account
{
public:
    Account5(double d, double r) : Account(d, r) { cout << "Generate 5 year account." << endl; }
    double calcAllRatio()
    {
        double r = 0;
        for (int i = 0; i < 5; i++)
            r += calcRatio();
        return r;
    }
};

int main()
{
    /*
    example input:
        10
    output:
        How many account:10
        Account 0:Generate 2 year account.
        Account 1:Generate 5 year account.
        Account 2:Generate 3 year account.
        Account 3:Generate 1 year account.
        Account 4:Generate 2 year account.
        Account 5:Generate 1 year account.
        Account 6:Generate 3 year account.
        Account 7:Generate 3 year account.
        Account 8:Generate 3 year account.
        Account 9:Generate 1 year account.
        Account 1:2.01
        Account 2:5.10101
        Account 3:3.0301
        Account 4:1
        Account 5:2.01
        Account 6:1
        Account 7:3.0301
        Account 8:3.0301
        Account 9:3.0301
        Account 10:1
    */
    int n;
    cout << "How many account:";
    cin >> n;
    Account *a[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Account " << i << ":";
        int r = rand() % 4;
        if (r == 0)
            a[i] = new Account1(100.0, 0.01);
        if (r == 1)
            a[i] = new Account2(100.0, 0.01);
        if (r == 2)
            a[i] = new Account3(100.0, 0.01);
        if (r == 3)
            a[i] = new Account5(100.0, 0.01);
    }
    for (int i = 0; i < n; i++)
    {
        cout << "Account " << a[i]->account << ":" << a[i]->calcAllRatio() << endl;
    }
    system("pause");
    return 0;
}
