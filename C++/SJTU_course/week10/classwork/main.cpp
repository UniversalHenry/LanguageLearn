#include <iostream>
#include <cstdlib> 
#include <cstdio>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
#include <set>
#include <map>
#include <ctime>
#include <cstring>

using namespace std;

class Matrix{
private:
    bool read_row_first;
    vector<vector<int> > values_;
public:
    Matrix();
    Matrix(const int &row, const int &col, const vector<int> &v);
    Matrix(const Matrix &m);
    int values(int c, int r) const;
    int r_size() const;
    int c_size() const;
    Matrix trans(bool change_self = true);
    Matrix& operator=(const Matrix& m);
    Matrix operator+(const Matrix& m);
    Matrix operator-(const Matrix& m);
    Matrix operator*(const Matrix& m);
    int &operator()(const int &r, const int &c);
    friend ostream &operator<<( ostream &output,const Matrix &m);
};

int main(void){
// time start
    double dur;
    clock_t start,end;
    start = clock();

// try here
    try{
        vector<int> v1 = {1,2,3,4,5,6};
        vector<int> v2 = {1,2,3,4,5,6};
        Matrix m1(3, 2, v1);
        Matrix m2(3, 2, v2);
        Matrix m = m1;
        m(1,1) = 0;
        cout << "m:" << endl << m;
        cout << "m1+m2:" << endl << m1 + m2;
        cout << "m1-m2:" << endl << m1 - m2;
        cout << "m1\':" << endl << m1.trans();
        cout << "m1*m2:" << endl << m1 * m2;
    }
    catch(runtime_error &e){
        cerr << endl << e.what();
    }
    
// time stop
    end = clock();
    dur = (double)(end - start);
    cout << endl << "UseTime:" << (dur / CLOCKS_PER_SEC) << endl;
    system("pause");
    return 0;
}

Matrix::Matrix(){
    read_row_first = true;
    values_.push_back({0});
}

Matrix::Matrix(const int &row, const int &col, const vector<int> &v){
    if(v.empty() || v.size() != row*col) throw runtime_error("Input Matrix Error!");
    else{
        read_row_first = true;
        for(int r = 0; r < row; r++){
            vector<int> tmpv;
            for(int c = 0; c < col; c++) tmpv.push_back(v[r * col + c]);
            values_.push_back(tmpv);
        }
    }
}

Matrix::Matrix(const Matrix &m){
    if (this != &m) {
        read_row_first = m.read_row_first;
        values_ = m.values_;
    }
}

int Matrix::values(int r, int c) const{
    if(c < 0 || r < 0 ) throw runtime_error("Input Index Error!");
    else if(read_row_first){
        if(r >= values_.size() || c >= values_[0].size()) throw runtime_error("Input Index Error!");
        return values_[r][c];
    }
    else{
        if(c >= values_.size() || r >= values_[0].size()) throw runtime_error("Input Index Error!");
        return values_[c][r];
    }
}

int Matrix::r_size() const{
    if(read_row_first) return values_.size();
    else return values_[0].size();
}
int Matrix::c_size() const{
    if(!read_row_first) return values_.size();
    else return values_[0].size();
}

Matrix Matrix::trans(bool change_self){
    if(change_self){
        read_row_first = (!read_row_first);
        return *this;
    }
    else{
        read_row_first = (!read_row_first);
        Matrix m_ = *this;
        read_row_first = (!read_row_first);
        return m_;
    }
}

Matrix& Matrix::operator=(const Matrix& m){
    if (this != &m) {
        read_row_first = m.read_row_first;
        values_ = m.values_;
    }
    return *this;
}

Matrix Matrix::operator+(const Matrix& m){
    vector<int> m_v_;
    if(this->c_size() != m.c_size() || this->r_size() != m.r_size())
        throw runtime_error("Plus Matrix Error!");
    for(int r = 0; r < this->r_size(); r++)
        for(int c = 0; c < this->c_size(); c++)
            m_v_.push_back(this->values(r,c) + m.values(r,c));
    Matrix m_(this->r_size(),this->c_size(),m_v_);
    return m_;
}

Matrix Matrix::operator-(const Matrix& m){
    vector<int> m_v_;
    if(this->c_size() != m.c_size() || this->r_size() != m.r_size())
        throw runtime_error("Minus Matrix Error!");
    for(int r = 0; r < this->r_size(); r++)
        for(int c = 0; c < this->c_size(); c++)
            m_v_.push_back(this->values(r,c) - m.values(r,c));
    Matrix m_(this->r_size(),this->c_size(),m_v_);
    return m_;
}

Matrix Matrix::operator*(const Matrix& m){
    vector<int> m_v_;
    if(this->c_size() != m.r_size())
        throw runtime_error("Multiply Matrix Error!");
    for(int r1 = 0; r1 < this->r_size(); r1++)
        for(int c2 = 0; c2 < m.c_size(); c2++){
            int v = 0;
            for(int r2 = 0; r2 < this->c_size(); r2++)
                for(int c1 = 0; c1 < m.r_size(); c1++)
                    v += this->values(r1,c1) * m.values(r2,c2);
            m_v_.push_back(v);
        }
    Matrix m_(this->r_size(),m.c_size(),m_v_);
    return m_;
}

int &Matrix::operator()(const int &r, const int &c){
    this->values(r,c);
    if(read_row_first)return this->values_[r][c];
    else return this->values_[c][r];
}

ostream & operator<<( ostream &output,const Matrix &m){
    for(int r = 0; r < m.r_size(); r++){
        for(int c = 0; c < m.c_size(); c++)output << m.values(r,c) << '\t';
        output << endl;
    }
    return output;
}