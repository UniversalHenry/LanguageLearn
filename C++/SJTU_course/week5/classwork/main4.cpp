#include <iostream>
#include <cstdlib> 
#include <cstdio>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
#include <set>
#include <ctime>
#include <cstring>

using namespace std;

// struct Goods{
//     string type;
//     string val;
// };
// class Custom{
//     public:
//         string id;
//         string phone;
//         string address;
//         string name;
//         vector <Goods> goods;
//         Custom(vector <Goods> g,string i="",string p="",string a="",string n=""):id(i),phone(p),address(a),name(n){goods.assign(g.begin(),g.end());};
        
// };

int main(void){

    // cout << "Input the customer ID:";
    // string custom_id;
    // cin >> custom_id;
    
    double dur;
    clock_t start,end;
    start = clock();

    char* order_file_name[]={"data/order.0.0","data/order.0.3","data/order.1.1","data/order.2.2"};
    int order_file_num = 4;
    char* buyer_file_name[]={"data/buyer.0.0","data/buyer.1.1"};
    int buyer_file_num = 2;
    char* good_file_name[]={"data/good.0.0","data/good.1.1","data/good.2.2"};
    int good_file_num = 3;
    // variable
    int amount;
    int sold=0;
    int num_order=0;
    string order_id;
    string buyer_id;
    string good_id;
    string order_input;
    string buyer_input;
    string good_input;
    string buyer_name;
    string good_name;
    string tmps;
    stringstream tmpss;
    cout << "Please input the good ID:";
    cin >> good_id;
    bool good_flag = false;
    for(int i = 0;i < good_file_num;i++){
        ifstream good_file(good_file_name[i]);
        while(getline(good_file,good_input)){
            if(good_id.compare(good_input.substr(7,good_id.length()))==0){
                tmps = good_input.substr(good_input.find("good_name:")+10,30);
                tmpss << tmps;
                tmpss >> good_name;
                tmpss.str("");
                for(int i = 0;i < order_file_num;i++){
                    ifstream order_file(order_file_name[i]);
                    while(getline(order_file,order_input)){
                        if(good_id.compare(order_input.substr(order_input.find("goodid:")+7,good_id.length()))==0){
                            num_order++;
                        // amount
                            tmps = order_input.substr(order_input.find("amount:")+7,10);
                            tmpss << tmps;
                            tmpss >> amount;
                            tmpss.str("");
                            sold+=amount;
                        }
                    }
                    order_file.close();
                }
                good_flag = true;
                break;
            }
        }
        good_file.close();
        if(good_flag)break;
    }

    if(good_flag){
        cout << "GoodID:" << good_id  << "\t";
        cout << "GoodName:" << good_name  << "\t";
        cout << "NumberOfOrders:" << num_order  << "\t";
        cout << "SoldNumber:" << sold  << "\t";
    }
    else{
        cout << "Not found";
    }

    end = clock();
    dur = (double)(end - start);
    printf("UseTime:%f\n",(dur/CLOCKS_PER_SEC));

	cout << "\nProgram finished.";
	int test;
	cin >> test;
    return 0;
}