// Computing Introduction Course
// Chapter 10
// Exercise 4

#include <iostream>

using namespace std;

class SavingAccount
{
  private:
    static int order;
    double deposit;
    double ratio;

  public:
    int account;
    SavingAccount() : account(++order), deposit(0), ratio(0) {}
    void changeRatio(double r) { ratio = r; }
    void saveMoney(double m) { deposit += m; }
    double showMoney() { return double(int(deposit * 100 + 0.5)) / 100; }
    void calcRatio() { deposit += deposit * ratio; }
};

int SavingAccount::order = 0;

int main()
{
    /*
    example input:
        2
        100
        0.015
        100
        1000
        0.02
        500
    output:
        How many accounts do you want?
        2
        --------------------------------------------
        Generate account 1
        Please save money:        100
        Please input ratio:        0.015
        Money now:100
        Money after a month:101.5
        Please save money again:        100
        Money now:201.5
        Money after a month:204.52
        --------------------------------------------
        Generate account 2
        Please save money:        1000
        Please input ratio:        0.02
        Money now:1000
        Money after a month:1020
        Please save money again:        500
        Money now:1520
        Money after a month:1550.4
    */
    int n;
    cout << "How many accounts do you want?" << endl;
    cin >> n;
    SavingAccount ac[n];
    for (int i = 0; i < n; i++)
    {
        double m, r;
        cout << "--------------------------------------------" << endl;
        cout << "Generate account " << ac[i].account << endl;
        cout << "Please save money:";
        cin >> m;
        ac[i].saveMoney(m);
        cout << "Please input ratio:";
        cin >> r;
        ac[i].changeRatio(r);
        cout << "Money now:" << ac[i].showMoney() << endl;
        ac[i].calcRatio();
        cout << "Money after a month:" << ac[i].showMoney() << endl;
        cout << "Please save money again:";
        cin >> m;
        ac[i].saveMoney(m);
        cout << "Money now:" << ac[i].showMoney() << endl;
        ac[i].calcRatio();
        cout << "Money after a month:" << ac[i].showMoney() << endl;
    }
    system("pause");
    return 0;
}
