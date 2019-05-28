// shakespear.cpp: 定义控制台应用程序的入口点。
//

#include <iostream>
#include <fstream>
#include <string>
#include <cassert>

using namespace std;

int main()
{
	ifstream out;
	string str, target, tmp[20];
	bool flag = false;
	cin >> target;
	int line = 0;
	int num = 0;
	int tmplen[20];
	int length = 0;
	int position1 = 0, position2 = 0;
	int j = 0, k = 0;
	int targetlength = target.length();
	out.open("C:\\Users\\Administrator\\Desktop\\GitHub\\LanguageLearn\\C++\\SJTU_course\\week1\\classwork\\shakespeare.txt", ios::in);
	while (getline(out, str))
	{
		line++;
		length = str.length();
		for (int i = 0; i < 20; ++i)
		{
			tmp[i] = " ";
			tmplen[i] = 0;
		}
		k = 0;
		for (int i = 0; i < length; ++i)
		{
			if ((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122))
			{
				position1 = i;
				for (i; i < length; ++i)
				{
					if (!((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122)))
					{
						position2 = i - 1;
						break;
					}
				}
				for (j = 0; j < position2 - position1 + 1; ++j)
					tmp[k][j] = str[position1 + j];
				tmplen[k] = position2 - position1 + 1;
				++k;
			}
		}
		for (int i = 0; i < k; ++i)
		{
			flag = true;
			for (j = 0; j < targetlength; ++j)
			{
				if (target[j] != tmp[i][j])
				{
					flag = false;
					break;
				}
			}
			if (flag)
			{
				if (i != 0)
				{
					cout << line << ",";
					for (j = 0; j < tmplen[i - 1]; ++j)
						cout << tmp[i - 1][j];
					cout << "," << target << ",";
				}
				else
					cout << line << ","
						 << "no previous word," << target << ",";
				if (i == (k - 1))
					cout << "no next word" << endl;
				else
				{
					for (j = 0; j < tmplen[i + 1]; ++j)
						cout << tmp[i + 1][j];
					cout << endl;
				}
				num++;
			}
		}
	}
	cout << "出现次数:" << num << endl;
	return 0;
}
