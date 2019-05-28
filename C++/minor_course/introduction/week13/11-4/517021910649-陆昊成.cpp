// Computing Introduction Course
// Chapter 11
// Exercise 4

#include <iostream>
#include <string.h>
#include <string>
#include <stdio.h>

using namespace std;

class String
{
    friend bool operator==(const String &, const String &);
    friend bool operator!=(const String &, const String &);
    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator>=(const String &, const String &);
    friend ostream &operator<<(ostream &os, const String &s);
    friend istream &operator>>(istream &os, String &s);

  public:
    String()
    {
        pstr_ = new char[1];
        pstr_[0] = '\0';
    }

    String(const char *s)
    {
        pstr_ = new char[strlen(s) + 1];
        strcpy(pstr_, s);
    }

    String(const String &rhs)
    {
        pstr_ = new char[strlen(rhs.pstr_) + 1];
        strcpy(pstr_, rhs.pstr_);
    }

    String &operator=(const String &rhs)
    {
        if (this != &rhs)
        {
            delete[] pstr_;
            pstr_ = new char[strlen(rhs.pstr_) + 1];
            strcpy(pstr_, rhs.pstr_);
        }
        return *this;
    }

    String &operator=(const char *s)
    {
        pstr_ = new char[strlen(s) + 1];
        strcpy(pstr_, s);
        return *this;
    }

    String &operator+=(const String &rhs)
    {
        char *tmp;
        tmp = new char[strlen(pstr_) + strlen(rhs.pstr_) + 1];
        strcpy(tmp, pstr_);
        strcat(tmp, rhs.pstr_);
        delete[] pstr_;
        pstr_ = tmp;
        return *this;
    }
    String &operator+=(const char *pstr)
    {
        char *tmp;
        tmp = new char[strlen(pstr_) + strlen(pstr) + 1];
        strcpy(tmp, pstr_);
        strcat(tmp, pstr);
        delete[] pstr_;
        pstr_ = tmp;
        return *this;
    }

    char &operator[](size_t index)
    {
        static char sNULL = '\0';
        if (index < strlen(pstr_) && index > 0)
        {
            return pstr_[index];
        }
        else
        {
            cout << "ERROR" << endl;
            return sNULL;
        }
    }

    const char &operator[](size_t index) const
    {
        static char sNULL = '\0';
        if (index < strlen(pstr_) && index > 0)
        {
            return pstr_[index];
        }
        else
        {
            cout << "ERROR" << endl;
            return sNULL;
        }
    }
    size_t size() const
    {
        return strlen(pstr_);
    }
    const char *c_str() const
    {
        return pstr_;
    }
    ~String()
    {
        delete[] pstr_;
    }

  private:
    char *pstr_;
};
// ==
bool operator==(const String &lhs, const String &rhs)
{
    if (strcmp(lhs.pstr_, rhs.pstr_) == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
// !=
bool operator!=(const String &lhs, const String &rhs)
{
    if (strcmp(lhs.pstr_, rhs.pstr_) == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}
// <
bool operator<(const String &lhs, const String &rhs)
{
    if (strcmp(lhs.pstr_, rhs.pstr_) < 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
// >
bool operator>(const String &lhs, const String &rhs)
{
    if (strcmp(lhs.pstr_, rhs.pstr_) > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
// <=
bool operator<=(const String &lhs, const String &rhs)
{
    if (strcmp(lhs.pstr_, rhs.pstr_) <= 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
// >=
bool operator>=(const String &lhs, const String &rhs)
{
    if (strcmp(lhs.pstr_, rhs.pstr_) >= 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
// <<
ostream &operator<<(ostream &ofs, const String &rhs)
{
    ofs << rhs.pstr_;
    return ofs;
}
// >>
istream &operator>>(istream &ifs, String &rhs)
{
    char tmp[1024];
    ifs >> tmp;
    rhs.pstr_ = tmp;
    return ifs;
}
// +
String operator+(const String &lhs, const String &rhs)
{
    String str(lhs);
    str += rhs;
    return str;
}
String operator+(const String &lhs, const char *s)
{
    String str(lhs);
    str += s;
    return str;
}
String operator+(const char *s, const String &rhs)
{
    String str(rhs);
    str += s;
    return s;
}

int main()
{
    /*
    example input:
        123
    output:
        s1:
        s2:hello
        s3:hello
        s4:hello
        s5:hello
        s6:helloworld
        s8:helloworld
        s8[3]:A
        s8:helAoworld
        hello
        equal
        unequal
        left larger
        s13:hello
        cin >> s14:123
        s14:123
        s17:helloworld
    */
    String s1;
    cout << "s1:" << s1 << endl;
    String s2 = "hello";
    cout << "s2:" << s2 << endl;
    String s3 = s2;
    cout << "s3:" << s3 << endl;
    String s4 = "world";
    s4 = s2;
    cout << "s4:" << s4 << endl;
    String s5;
    s5 = "hello";
    cout << "s5:" << s5 << endl;
    String s6 = "hello"; // +=
    String s7 = "world";
    s6 += s7;
    cout << "s6:" << s6 << endl;
    String s8 = "hello"; // ++
    s8 += "world";
    cout << "s8:" << s8 << endl;
    s8[3] = 'A';
    cout << "s8[3]:" << s8[3] << endl; // []
    cout << "s8:" << s8 << endl;
    String s9 = "hello"; // c_str
    const char *s;
    s = s9.c_str();
    cout << s << endl;
    String s10 = "hello";
    if (s9 == s10) // ==
    {
        cout << "equal" << endl;
    }
    String s11 = "world";
    if (s10 != s11) // !=
    {
        cout << "unequal" << endl;
    }
    String s12 = "i am the max string"; // <

    if (s11 < s12)
    {
        cout << "right larger" << endl;
    }
    else
    {
        cout << "left larger" << endl;
    }
    String s13 = "hello"; // <<
    cout << "s13:" << s13 << endl;
    String s14; // >>
    cout << "cin >> s14:";
    cin >> s14;
    cout << "s14:" << s14 << endl;
    String s15 = "hello"; // +
    String s16 = "world";
    String s17 = s15 + s16;
    cout << "s17:" << s17 << endl;
    system("pause");
    return 0;
}