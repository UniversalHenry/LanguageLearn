// Computing Introduction Course
// Chapter 10
// Exercise 9

#include <iostream>
#include <map>
#include <cstring>

using namespace std;

class Dict
{
  private:
    map<string, string> d;

  public:
    void add(string en, string ch)
    {
        d.insert(make_pair(en, ch));
    }
    string find(string en);
    bool erase(string en);
    void listAll();
};

string Dict::find(string en)
{
    if (d.count(en))
        return d.find(en)->second;
    else
        return "#ERR INFO#";
}

bool Dict::erase(string en)
{
    if (d.count(en))
    {
        d.erase(d.find(en));
        return true;
    }
    else
        return false;
}

void Dict::listAll()
{
    int i = 0;
    for (map<string, string>::iterator x = d.begin(); x != d.end(); x++)
    {
        i++;
        cout << "------------------------" << endl;
        cout << "WORD " << i << ":" << endl;
        cout << "[EN]" << x->first << endl
             << "[CH]" << x->second << endl;
    }
    if (i == 0)
        cout << "------------------------" << endl
             << "No word!" << endl;
}

int main()
{
    /*
    example input:
        1
        en1
        ch1
        1
        en2
        ch2
        1
        en3
        ch3
        4
        3
        en1
        2
        en1
        2
        en1
        4
        3
        en1
        2
        en2
        4
        2
        en3
        4
        5
    output:
        ----------------------------------------------------------
        Input order(ADD(1),ERASE(2),FIND(3),LIST(4),QUIT(5)):1
        ----------------------------------------------------------
        Input English(input #Q to  quit):en1
        Input Chinses(input #Q to  quit):ch1
        Successfully added!
        ----------------------------------------------------------
        Input order(ADD(1),ERASE(2),FIND(3),LIST(4),QUIT(5)):1
        ----------------------------------------------------------
        Input English(input #Q to  quit):en2
        Input Chinses(input #Q to  quit):ch2
        Successfully added!
        ----------------------------------------------------------
        Input order(ADD(1),ERASE(2),FIND(3),LIST(4),QUIT(5)):1
        ----------------------------------------------------------
        Input English(input #Q to  quit):en3
        Input Chinses(input #Q to  quit):ch3
        Successfully added!
        ----------------------------------------------------------
        Input order(ADD(1),ERASE(2),FIND(3),LIST(4),QUIT(5)):4
        ------------------------
        WORD 1:
        [EN]en1
        [CH]ch1
        ------------------------
        WORD 2:
        [EN]en2
        [CH]ch2
        ------------------------
        WORD 3:
        [EN]en3
        [CH]ch3
        ----------------------------------------------------------
        Input order(ADD(1),ERASE(2),FIND(3),LIST(4),QUIT(5)):3
        ----------------------------------------------------------
        Input English to find Chinese(input #Q to  quit):en1
        English:en1
        Chinese:ch1
        ----------------------------------------------------------
        Input order(ADD(1),ERASE(2),FIND(3),LIST(4),QUIT(5)):2
        ----------------------------------------------------------
        Input English to erase(input #Q to  quit):en1
        Successfully erased!
        ----------------------------------------------------------
        Input order(ADD(1),ERASE(2),FIND(3),LIST(4),QUIT(5)):2
        ----------------------------------------------------------
        Input English to erase(input #Q to  quit):en1
        No such word!
        ----------------------------------------------------------
        Input order(ADD(1),ERASE(2),FIND(3),LIST(4),QUIT(5)):4
        ------------------------
        WORD 1:
        [EN]en2
        [CH]ch2
        ------------------------
        WORD 2:
        [EN]en3
        [CH]ch3
        ----------------------------------------------------------
        Input order(ADD(1),ERASE(2),FIND(3),LIST(4),QUIT(5)):3
        ----------------------------------------------------------
        Input English to find Chinese(input #Q to  quit):en1
        No such word!
        ----------------------------------------------------------
        Input order(ADD(1),ERASE(2),FIND(3),LIST(4),QUIT(5)):2
        ----------------------------------------------------------
        Input English to erase(input #Q to  quit):en2
        Successfully erased!
        ----------------------------------------------------------
        Input order(ADD(1),ERASE(2),FIND(3),LIST(4),QUIT(5)):4
        ------------------------
        WORD 1:
        [EN]en3
        [CH]ch3
        ----------------------------------------------------------
        Input order(ADD(1),ERASE(2),FIND(3),LIST(4),QUIT(5)):2
        ----------------------------------------------------------
        Input English to erase(input #Q to  quit):en3
        Successfully erased!
        ----------------------------------------------------------
        Input order(ADD(1),ERASE(2),FIND(3),LIST(4),QUIT(5)):4
        ------------------------
        No word!
        ----------------------------------------------------------
        Input order(ADD(1),ERASE(2),FIND(3),LIST(4),QUIT(5)):5
    */
    Dict myDict;
    while (1)
    {
        int order = 0;
        cout << "----------------------------------------------------------" << endl;
        cout << "Input order(ADD(1),ERASE(2),FIND(3),LIST(4),QUIT(5)):";
        cin >> order;
        if (order == 1)
        {
            string en, ch;
            cout << "----------------------------------------------------------" << endl;
            cout << "Input English(input #Q to  quit):";
            cin >> en;
            if (en == "#Q")
                continue;
            cout << "Input Chinses(input #Q to  quit):";
            cin >> ch;
            if (ch == "#Q")
                continue;
            myDict.add(en, ch);
            cout << "Successfully added!" << endl;
        }
        else if (order == 2)
        {
            string en;
            cout << "----------------------------------------------------------" << endl;
            cout << "Input English to erase(input #Q to  quit):";
            cin >> en;
            if (en == "#Q")
                continue;
            if (myDict.erase(en))
                cout << "Successfully erased!" << endl;
            else
                cout << "No such word!" << endl;
        }
        else if (order == 3)
        {
            string en;
            cout << "----------------------------------------------------------" << endl;
            cout << "Input English to find Chinese(input #Q to  quit):";
            cin >> en;
            if (en == "#Q")
                continue;
            string ch = myDict.find(en);
            if (ch == "#ERR INFO#")
                cout << "No such word!" << endl;
            else
                cout << "English:" << en << endl
                     << "Chinese:" << ch << endl;
        }
        else if (order == 4)
        {
            myDict.listAll();
        }
        else if (order == 5)
            break;
    }
    system("pause");
    return 0;
}
