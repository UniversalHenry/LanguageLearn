// Computing Introduction Course
// Chapter 11
// Exercise 5

#include <iostream>

using namespace std;

class Row
{
    int y;
    double *data = NULL;

  public:
    Row(int y0) : y(y0) { data = new double[y + 1]; }
    ~Row() { delete data; }
    double &operator[](int j)
    {
        if (j > y)
            j = y;
        return data[j];
    }
};

class Matrix
{
    int x;
    int y;
    Row **data = NULL;

  public:
    Matrix(int x0, int y0) : x(x0), y(y0)
    {
        data = new Row *[x + 1];
        for (int i = 0; i <= x; i++)
            data[i] = new Row(y);
    }
    ~Matrix()
    {
        for (int i = 0; i <= x; i++)
            delete data[i];
        delete data;
    }
    Row &operator[](int i)
    {
        if (i > x)
            i = x;
        return *data[i];
    }
    double operator()(int i, int j)
    {
        return (*data[i])[j];
    }
};

int main()
{
    /*
    example input:
        3 3
        1 2 3
        4 5 6
        7 8 9
        1
        1
        1
        1
    output:
        -------------------------------
        Input size:3 3
        Input data:
        1 2 3
        4 5 6
        7 8 9
        -------------------------------
        Show data with M(x,y) (0-2,0-2):1
        1
        Data is 5
        -------------------------------
        Show data with M[x][y] (0-2,0-2):1
        1
        Data is 5
    */
    int x, y;
    cout << "-------------------------------" << endl
         << "Input size:";
    cin >> x >> y;
    Matrix M(x, y);
    cout << "Input data:" << endl;
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++)
        {
            cin >> M[i][j];
        }
    int m, n;
    cout << "-------------------------------" << endl
         << "Show data with M(x,y) (0-" << x - 1 << ",0-" << y - 1 << "):";
    cin >> m >> n;
    if (m >= 0 && m < x && n >= 0 && n < y)
        cout << "Data is " << M(m, n) << endl;
    cout << "-------------------------------" << endl
         << "Show data with M[x][y] (0-" << x - 1 << ",0-" << y - 1 << "):";
    cin >> m >> n;
    if (m >= 0 && m < x && n >= 0 && n < y)
        cout << "Data is " << M[m][n] << endl;
    system("pause");
    return 0;
}
