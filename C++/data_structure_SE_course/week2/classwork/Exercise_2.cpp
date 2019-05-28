
/*
** 作者: 王贇超
** 输入: 多个多边形
** 输出: 多边形类型, 最小切割次数, 切线的两个端点
** 切割限制: 只能用原始图形的对角线进行切割
*/
#include<fstream>
#include<iostream>
#include<stdlib.h>
#include<map>
#include<vector>
#include<sstream>
#include<stdio.h>
#include<algorithm>

using namespace std;

int getCross(pair<pair<int, int>, pair<int, int>> begin, pair<pair<int, int>, pair<int, int>> end)
{
    return (begin.second.first - begin.first.first) * (end.second.second - end.first.second) - (begin.second.second - begin.first.second) * (end.second.first - end.first.first);
}
bool IsConcave(vector<pair<int, int>>& poly, vector<pair<int, int>>& cavePoint)
{
    if(poly.size()<4)
    {
        return false;
    }
    int pos = 0;
    int neg = 0;
    vector<pair<int, int>> posPoint;
    vector<pair<int, int>> negPoint;
    vector<pair<pair<int, int>,pair<int,int>>> edges;
    {
        pair<int, int> begin = poly[poly.size() - 1];
        for (int i = 0; i < poly.size();i++)
        {
            pair<int, int> end = poly[i];
            edges.push_back(make_pair(begin, end));
            begin = end;
        }
    }
    {
        pair<pair<int, int>, pair<int, int>> begin = edges[edges.size() - 1];
        for (int i = 0; i < edges.size();i++)
        {
            pair<pair<int, int>, pair<int, int>> end = edges[i];
            int cross = getCross(begin, end);
            // printf("<(%d,%d),(%d,%d)> <(%d,%d),(%d,%d)> %d", begin.first.first, begin.first.second, begin.second.first, begin.second.second, end.first.first, end.first.second, end.second.first, end.second.second, cross);
            if(cross > 0)
            {
                pos++;
                posPoint.push_back(begin.second);
            }
            else if(cross < 0)
            {
                neg++;
                negPoint.push_back(begin.second);
            }
            begin = end;
        }
    }
    if(pos!=0 && neg!=0)
    {
        if (pos > neg)
        {
            cavePoint = negPoint;
        }
        else
        {
            cavePoint = posPoint;
        }
        return true;
    }
    else
    {
        return false;
    }
}

bool IsIntersect(pair<pair<int, int>, pair<int, int>> line1, pair<pair<int, int>, pair<int, int>> line2)
{
    if (line1.first == line2.first)
    {
        if(line1.second == line2.second)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (line1.first == line2.second)
    {
        if(line1.second == line2.first)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (line1.second == line2.first)
    {
        if(line1.first == line2.second)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if (line1.second == line2.second)
    {
        if(line1.first == line2.first)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    if ( max(line1.first.first, line1.second.first)<min(line2.first.first, line2.second.first) )  
    {  
        return false;  
    }  
    if ( max(line1.first.second, line1.second.second)<min(line2.first.second, line2.second.second) )  
    {  
        return false;  
    }  
    if ( max(line2.first.first, line2.second.first)<min(line1.first.first, line1.second.first) )  
    {  
        return false;  
    }  
    if ( max(line2.first.second, line2.second.second)<min(line1.first.second, line1.second.second) )  
    {  
        return false;  
    }
    if (getCross(make_pair(line2.first,line1.second),make_pair(line1.second,line1.first)) * getCross(make_pair(line1.second,line2.second),make_pair(line2.second,line1.first)) < 0)
    {
        return false;
    }
    if (getCross(make_pair(line1.first,line2.second),make_pair(line2.second,line2.first)) * getCross(make_pair(line2.second,line1.second),make_pair(line1.second,line2.first)) < 0)
    {
        return false;
    } 
    return true;  
}

void cutPoly(vector<pair<int, int>>& poly, vector<pair<int, int>>& poly1, vector<pair<int, int>>& poly2, pair<pair<int, int>,pair<int,int>> cut)
{
    bool tag = true;
    for (int j = 0; j < poly.size();j++)
    {
        if(poly[j] == cut.first || poly[j] == cut.second)
        {
            poly1.push_back(poly[j]);
            poly2.push_back(poly[j]);
            if(tag)
            {
                tag = false;
            }
            else
            {
                tag = true;
            }
            
        }
        else
        {
            if(tag)
            {
                poly1.push_back(poly[j]);
            }
            else
            {
                poly2.push_back(poly[j]);
            } 
        }
    }
}
bool isInsidePoly(vector<pair<pair<int, int>,pair<int,int>>> edges, pair<double, double> mid)
{
    int time = 0;
    for (int i = 0; i < edges.size();i++)
    {
        if((edges[i].first.first <= mid.first && edges[i].second.first <= mid.first) || (edges[i].first.first > mid.first && edges[i].second.first > mid.first))
        {

        }
        else
        {
            if(edges[i].second.first != edges[i].first.first)
            {
                double y = (double)(edges[i].second.second - edges[i].first.second) / (double)(edges[i].second.first - edges[i].first.first) * (double)(mid.first - edges[i].first.first) + (double)edges[i].first.second;
                if(y>mid.second)
                {
                    time++;
                }
            }
        }
    }
    if(time%2 == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int getMinCut(vector<pair<int, int>>& poly, vector<pair<pair<int, int>,pair<int,int>>>& ansCuts)
{
    vector<pair<int, int>> cavePoint;
    if (!IsConcave(poly,cavePoint))
    {
        return 0;
    }
    vector<pair<pair<int, int>,pair<int,int>>> edges;
    {
        pair<int, int> begin = poly[poly.size() - 1];
        for (int i = 0; i < poly.size();i++)
        {
            pair<int, int> end = poly[i];
            edges.push_back(make_pair(begin, end));
            begin = end;
        }
    }
    vector<pair<pair<int, int>, pair<int, int>>> cuts;
    {
        for(int i = 0; i<poly.size();i++)
        {
            for (int j = i+1; j < poly.size();j++)
            {
                cuts.push_back(make_pair(poly[i], poly[j]));
            }
        }
    }
    vector<pair<pair<int, int>, pair<int, int>>> validCuts;
    for (int i = 0; i < cuts.size();i++)
    {
        bool valid = true;
        for (int j = 0; j < edges.size();j++)
        {
            if(IsIntersect(cuts[i],edges[j]))
            {
                valid = false;
                break;
            }
        }
        if(valid)
        {
            double midx = ((double)cuts[i].first.first + (double)cuts[i].second.first) / 2;
            double midy = ((double)cuts[i].first.second + (double)cuts[i].second.second) / 2;
            if(isInsidePoly(edges, make_pair(midx, midy)))
            {
                validCuts.push_back(cuts[i]);
            }
        }
    }
    vector<int> ans;
    for (int i = 0; i < validCuts.size();i++)
    {
        vector<pair<int, int>> poly1;
        vector<pair<int, int>> poly2;
        cutPoly(poly, poly1, poly2, validCuts[i]);
        vector<pair<pair<int, int>, pair<int, int>>> tempCuts;
        ans.push_back(getMinCut(poly1, tempCuts) + getMinCut(poly2, tempCuts) + 1);
    }
    int min = INT_MAX;
    int index = -1;
    for (int i = 0; i < ans.size();i++)
    {
        if(ans[i]<min)
        {
            min = ans[i];
            index = i;
        }
    }
    ansCuts.push_back(validCuts[index]);
    {
        vector<pair<int, int>> poly1;
        vector<pair<int, int>> poly2;
        cutPoly(poly, poly1, poly2, validCuts[index]);
        getMinCut(poly1, ansCuts);
        getMinCut(poly2, ansCuts);
    }
    return min;
}

int main()
{
    fstream file;
    file.open("lesson/polys.txt", ios::in);
    vector<vector<pair<int, int>>> polys;
    if(file.is_open())
    {
        while(!file.eof())
        {
            string line = "";
            getline(file, line);
            stringstream ss(line);
            polys.push_back(vector<pair<int, int>>());
            while (!ss.eof())
            {
                int a = 0;
                int b = 0;
                char temp;
                ss >> a;
                ss >> temp;
                ss >> b;
                polys[polys.size() - 1].push_back(pair<int, int>(a, b));
            }
        }
    }
    vector<bool> ans;
    for (int i = 0; i < polys.size();i++)
    {
        vector < pair<int, int>> cavePoint;
        if(IsConcave(polys[i], cavePoint))
        {
            vector<pair<pair<int, int>, pair<int, int>>> cuts;
            int min = getMinCut(polys[i], cuts);
            printf("Concave cut:%d", min);
            for (int j = 0; j < cuts.size();j++)
            {
                printf("<(%d,%d),(%d,%d)> ", cuts[j].first.first, cuts[j].first.second, cuts[j].second.first, cuts[j].second.second);
            }
            cout << endl;
        }
        else
        {
            cout << "Convex\n";
        }
    }
    cout << "ProgramFinished";
    int test;
    cin >> test;
}