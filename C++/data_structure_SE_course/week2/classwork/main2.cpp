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

bool is_convex_shape(const shape &Shape){
    int n = Shape.num_dot;
    bool flag = true;
    for(int i=0;i<Shape.num_dot;i++){
        flag = is_convex_dot(Shape.shape_dot[i%n],Shape.shape_dot[(i+1)%n],Shape.shape_dot[(i+2)%n]);
        if(!flag)break;
    }
    return flag;
}

int find_err_dot(const shape &Shape){
    int n = Shape.num_dot;
    bool flag = true;
    int rec = -1;
    for(int i=0;i<Shape.num_dot;i++){
        flag = is_convex_dot(Shape.shape_dot[i%n],Shape.shape_dot[(i+1)%n],Shape.shape_dot[(i+2)%n]);
        if(!flag){rec = i;break;}
    }
    if(!flag)
    {
        for(int i=rec;i<Shape.num_dot;i++){
            flag = is_convex_dot(Shape.shape_dot[i%n],Shape.shape_dot[(i+1)%n],Shape.shape_dot[(i+2)%n]);
            if(flag){rec = i;break;}
        }
    }
    return (rec+1)%n;
}
//在这改动数据
int num_dot = 11;
shape Shape(num_dot);
float p[] = {0,3,3,3,3,2,5,4,5,2,4,2,4,1,5,1,6,5,6,1,3,0};

int main(void){
    //数据
    Shape.num_dot = num_dot;
    Shape.shape_dot = new dot [num_dot];

    for(int i=0;i<num_dot;i++){Shape.shape_dot[i].x=p[2*i];}
    for(int i=0;i<num_dot;i++){Shape.shape_dot[i].y=p[2*i+1];}
    //切图
    shape final_Shape(num_dot);
    final_Shape.num_dot = num_dot;
    final_Shape.shape_dot = new dot [num_dot];
    for(int i=0;i<num_dot;i++){final_Shape.shape_dot[i].x=p[2*i];}
    for(int i=0;i<num_dot;i++){final_Shape.shape_dot[i].y=p[2*i+1];}

    dot line_rec[num_dot*2];
    int err_dot[num_dot];
    int err_dot_num =0;
    while(true){
        if(is_convex_shape(final_Shape))break;
        err_dot[err_dot_num]=find_err_dot(final_Shape);
        line_rec[err_dot_num*2]=final_Shape.shape_dot[(err_dot[err_dot_num]+final_Shape.num_dot-1)%final_Shape.num_dot];
        line_rec[err_dot_num*2 + 1]=final_Shape.shape_dot[(err_dot[err_dot_num]+final_Shape.num_dot+1)%final_Shape.num_dot];
        for(int i=err_dot[err_dot_num];i<final_Shape.num_dot;i++){
            final_Shape.shape_dot[i].x=final_Shape.shape_dot[i+1].x;
            final_Shape.shape_dot[i].y=final_Shape.shape_dot[i+1].y;
        }
        final_Shape.num_dot--;
        err_dot_num++;
    }

    //输出
    if(is_convex_shape(Shape)){cout << "Is convex.\n";}
    else{
        for(int i=0;i<err_dot_num;i++){
            cout << "(" << line_rec[i*2].x << "," << line_rec[i*2].y << ")";
            cout << "\t(" << line_rec[i*2+1].x << "," << line_rec[i*2+1].y<< ")\n";
        }
    }
    cout << "Program finished.";
    int test;
    cin >> test;
    return 0;
}