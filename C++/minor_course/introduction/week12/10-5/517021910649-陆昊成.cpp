// Computing Introduction Course
// Chapter 10
// Exercise 5

#include <iostream>

using namespace std;

class str
{
  private:
    char *ch;

  public:
    int len;
    str() : len(0), ch(0) {}
    void save(char *c);
    char *show() { return ch; }
    void add(str s);
};

void str::save(char *c)
{
    len = 0;
    while (c[len] != '\0')
        len++;
    if (ch != 0)
        delete ch;
    ch = new char[len + 1];
    for (int i = 0; i <= len; i++)
        ch[i] = c[i];
}

void str::add(str s)
{
    char *tmpch = new char[len + s.len + 1];
    for (int i = 0; i < len; i++)
        tmpch[i] = ch[i];
    for (int i = 0; i <= s.len; i++)
        tmpch[i + len] = s.ch[i];
    if (ch != 0)
        delete ch;
    ch = tmpch;
    len += s.len;
}

int main()
{
    /*
    example input:
        abc
        def
    output:
        --------------------------------------------
        Input string A:         abc
        String A:       abc
        String A length:        3
        --------------------------------------------
        Input string B:         def
        String B:       def
        String B length:        3
        --------------------------------------------
        String A+B:     abcdef
        String A+B length:      6
    */
    char cha[10000], chb[10000];
    cout << "--------------------------------------------" << endl;
    cout << "Input string A:\t";
    cin >> cha;
    str a;
    a.save(cha);
    cout << "String A:\t" << a.show() << endl;
    cout << "String A length:\t" << a.len << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Input string B:\t";
    cin >> chb;
    str b;
    b.save(chb);
    cout << "String B:\t" << b.show() << endl;
    cout << "String B length:\t" << b.len << endl;
    cout << "--------------------------------------------" << endl;
    a.add(b);
    cout << "String A+B:\t" << a.show() << endl;
    cout << "String A+B length:\t" << a.len << endl;
    system("pause");
    return 0;
}
