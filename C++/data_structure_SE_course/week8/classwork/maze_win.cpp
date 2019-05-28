#include <time.h>
#include <iostream>
#include <string>
#include <random>
#include <stack>
#include <queue>
#include <windows.h>
#include <algorithm>
#include <set>

#define DENSITY 60
// #define RED     4
// #define GREEN   2
// #define YELLOW  6
// #define WHITE   7
// #define PURPLE  13

#define RED     204
#define GREEN   170
#define YELLOW  238
#define WHITE   17
#define PURPLE  221

#define WHITE_END   7

using namespace std;

class Point
{
    public:
        int X;
        int Y;
    
    Point (){

    }

    Point(int x, int y)
    {
        X = x;
        Y = y;
    }

    Point& operator= (const Point& point)
    {
        if (this == &point)
        {
            return *this;
        }

        X = point.X;
        Y = point.Y;

        return *this;
    }

    bool operator == (const Point& point) const
    {
        if (X == point.X && Y == point.Y)
        {
            return true;
        } else 
        {
            return false;
        }
    }

    bool operator != (const Point& point) const
    {
        return (X != point.X || Y != point.Y);
    }

    void gen(int x, int y){
        X = x;
        Y = y;
    }
};

vector<vector<int> > generate(int width, int height)
{
    mt19937 rng;
    rng.seed(time(nullptr));

    default_random_engine fixed;
    uniform_int_distribution<int> distribution(0, 99);

    vector<vector<int> > maze(height, vector<int>(width));
    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
            maze[i][j] = distribution(rng) < DENSITY ? 1 : 0;
        }
    }
    return maze;
}

void printMaze(vector<vector<int> > &maze)
{
    HANDLE hOut;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    for(int i = 0; i < maze.size(); i++)
    {
        for(int j = 0; j < maze[i].size(); j++)
        {
            if (maze[i][j] == 1)
            {
                SetConsoleTextAttribute(hOut, GREEN);
                cout<<"  ";
            }
            else if(maze[i][j] == 2)
            {
                SetConsoleTextAttribute(hOut, WHITE);
                cout<<"  ";
            }
            else if(maze[i][j] == 3)
            {
                SetConsoleTextAttribute(hOut, RED);
                cout<<"  ";
            }
            else if(maze[i][j] == 5)
            {
                SetConsoleTextAttribute(hOut, PURPLE);
                cout<<"  ";
            }
            else
            {
                SetConsoleTextAttribute(hOut, YELLOW);
                cout<<"  ";
            }
        }
        cout<<endl;
    }
    cout << endl;
    SetConsoleTextAttribute(hOut, WHITE_END);
}

Point take_action(const Point & p, const int & i){
    Point p_(-1,-1);
    switch(i){
        case 0: p_.gen(p.X + 1, p.Y); return p_;
        case 1: p_.gen(p.X + 1, p.Y + 1); return p_;
        case 2: p_.gen(p.X, p.Y + 1); return p_;
        case 3: p_.gen(p.X - 1, p.Y + 1); return p_;
        case 4: p_.gen(p.X - 1, p.Y ); return p_;
        case 5: p_.gen(p.X - 1, p.Y - 1); return p_;
        case 6: p_.gen(p.X, p.Y - 1); return p_;
        case 7: p_.gen(p.X + 1, p.Y - 1); return p_;
    }
}

bool is_valid_action(const Point & p, const int & i, const vector<Point> &way, const vector<vector<int> > &maze){
    Point p_(-1,-1);
    switch(i){
        case 0: p_.gen(p.X + 1, p.Y); break;
        case 1: p_.gen(p.X + 1, p.Y + 1); break;
        case 2: p_.gen(p.X, p.Y + 1); break;
        case 3: p_.gen(p.X - 1, p.Y + 1); break;
        case 4: p_.gen(p.X - 1, p.Y ); break;
        case 5: p_.gen(p.X - 1, p.Y - 1); break;
        case 6: p_.gen(p.X, p.Y - 1); break;
        case 7: p_.gen(p.X + 1, p.Y - 1); break;
    } 
    if(p_.X < 0) return false;
    if(p_.X >= maze[0].size()) return false;
    if(p_.Y < 0) return false;
    if(p_.Y >= maze.size()) return false;
    if(find(way.begin(),way.end(),p_) == way.end() && maze[p_.Y][p_.X] == 1)  return true;
    return false;
}

bool solve(vector<vector<int> > &maze, Point start, Point end)
{
    vector<Point> way_now;
    vector<Point> ans_way;
    way_now.push_back(start);
    queue<vector<Point>> search;
    search.push(way_now);
    vector<Point> p_exist;
    p_exist.push_back(start);
    while(true){
        way_now = search.front();
        search.pop();
        vector<Point> way_next;
        Point point_now = way_now.back();
        Point point_next;
        bool flag = false;
        for(int i = 0; i < 8; i++){
            point_next = take_action(point_now, i);
            if(is_valid_action(point_now, i, way_now, maze) && find(p_exist.begin(),p_exist.end(),point_next) == p_exist.end()){
                p_exist.push_back(point_next);
                way_next = way_now;
                way_next.push_back(point_next);
                if(point_next == end){ ans_way = way_next; flag = true; break;}
                search.push(way_next);
            }
        }
        if(flag) break;
        if(search.empty()) break;
    }
    if(ans_way.empty())return false;
    else{
        vector<Point>::iterator the_point;
        the_point = ans_way.begin();
        while(the_point != ans_way.end()){
            maze[the_point->Y][the_point->X] = 3;
            the_point++;
        }
    }
    return true;
}

int main()
{
    while(true){
        int width;
        int height;

        cout<<"Please input the width:";
        cin>>width;
        cout<<"Please input the height:";
        cin>>height;

        vector<vector<int> > maze = generate(width, height);
        printMaze(maze);
        int start_x, start_y, end_x, end_y;
        cout << "Please input the start point:";
        cin >> start_x >> start_y;
        cout << "Please input the end point:";
        cin >> end_x >> end_y;
        Point start(start_x, start_y);
        Point end(end_x, end_y);

        solve(maze, start, end);
        printMaze(maze);

        system("pause");
    }
    return 0;
}
