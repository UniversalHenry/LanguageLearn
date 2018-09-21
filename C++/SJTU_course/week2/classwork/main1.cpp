#include <iostream>
#include <stdlib.h> 
#include <stdio.h>
using namespace std;

struct dot{
    float x;
    float y;
};

class shape{
    public:
    int num_dot;
    dot *shape_dot;
    shape(int n){
        num_dot = n;
        shape_dot = new dot[n];
    }
    ~shape(){
        delete shape_dot;
    }
};

bool is_convex_dot(const dot & a, const dot & b,const dot & c){
    float A = b.y - a.y;        //y2-y1
    float B = a.x - b.x;        //x1-x2
    float C = b.x*a.y - a.x*b.y;    // x2*y1-x1*y2
    float D = A*c.x + B*c.y +C;      //D=A*xp+B*yp+C
    return D >= 0;
}

bool is_convex_shape(const shape Shape){
    int n = Shape.num_dot;
    bool flag = true;
    for(int i=0;i<Shape.num_dot;i++){
        flag = is_convex_dot(Shape.shape_dot[i%n],Shape.shape_dot[(i+1)%n],Shape.shape_dot[(i+2)%n]);
        if(!flag)break;
    }
    return flag;
}

int num_dot = 11;
shape Shape(num_dot);
float p[] = {0,3,3,3,3,2,5,4,5,2,4,2,4,1,5,1,6,5,6,1,3,0};

int main(void){
    Shape.num_dot = num_dot;
    Shape.shape_dot = new dot [num_dot];

    for(int i=0;i<num_dot;i++){Shape.shape_dot[i].x=p[2*i];}
    for(int i=0;i<num_dot;i++){Shape.shape_dot[i].y=p[2*i+1];}

    cout << is_convex_shape(Shape) << "\n";

    cout << "Program finished.";
    int test;
    cin >> test;
    return 0;
}