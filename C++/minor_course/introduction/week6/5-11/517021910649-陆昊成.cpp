// Computing Introduction Course
// Chapter 5
// Exercise 11

#include <iostream>

using namespace std;

void printMap(int a[3][3])
{
    cout << "   0 1 2 c";
    for (int i = 0; i < 3; i++)
    {
        cout << endl
             << "  ------- " << endl;
        cout << i << " |";
        for (int j = 0; j < 3; j++)
        {
            if (a[i][j] == 0)
                cout << ' ';
            if (a[i][j] == 1)
                cout << 'O';
            if (a[i][j] == 2)
                cout << 'X';
            cout << '|';
        }
    }
    cout << endl
         << "r ------- " << endl;
}

bool checkMap(int a[3][3], int i)
{
    int a_[3][3];
    for (int r = 0; r < 3; r++)
    {
        for (int c = 0; c < 3; c++)
        {
            a_[r][c] = (a[r][c] == i);
        }
    }
    if (a_[0][0] + a_[0][1] + a_[0][2] == 3)
        return true;
    if (a_[1][0] + a_[1][1] + a_[1][2] == 3)
        return true;
    if (a_[2][0] + a_[2][1] + a_[2][2] == 3)
        return true;
    if (a_[0][0] + a_[1][0] + a_[2][0] == 3)
        return true;
    if (a_[0][1] + a_[1][1] + a_[2][1] == 3)
        return true;
    if (a_[0][2] + a_[1][2] + a_[2][2] == 3)
        return true;
    if (a_[0][0] + a_[1][1] + a_[2][2] == 3)
        return true;
    if (a_[2][0] + a_[1][1] + a_[0][2] == 3)
        return true;
    return false;
}

int main()
{
    int a[3][3];
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            a[i][j] = 0;
        }
    }
    printMap(a);
    for (int i = 0; i < 9; i++)
    {
        int r, c;
        while (true)
        {
            cout << "Player 1 is O, player 2 is X." << endl;
            cout << "Player " << i % 2 + 1 << " input r & c:";
            cin >> r >> c;
            if (r < 3 && c < 3 && r >= 0 && c >= 0 && a[r][c] == 0)
                break;
            cout << "Invilid input !" << endl;
            printMap(a);
        }
        a[r][c] = i % 2 + 1;
        printMap(a);
        if (checkMap(a, i % 2 + 1))
        {
            cout << "Player " << i % 2 + 1 << " win!" << endl;
            break;
        }
    }
    if (!checkMap(a, 1) && !checkMap(a, 2))
        cout << "Nobody wins!" << endl;
    system("pause");
    return 0;
}
