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
    float price;
    string order_id;
    string order_input;
    string buyer_input;
    string good_input;
    string buyer_name;
    string good_name;
    string tmps;
    stringstream tmpss;
    bool flag = false;
    cout << "Please input the order ID:";
    cin >> order_id;
    for(int i = 0;i < order_file_num;i++){
        ifstream order_file(order_file_name[i]);
        while(getline(order_file,order_input)){
            if(order_id.compare(order_input.substr(8,9))==0){
            // amount
                tmps = order_input.substr(order_input.find("amount:")+7,10);
                tmpss << tmps;
                tmpss >> amount;
                tmpss.str("");
            // buyer name
                string buyer_id = order_input.substr(order_input.find("buyerid:")+8,20);
                bool buyer_flag = false;
                for(int i = 0;i < buyer_file_num;i++){
                        ifstream buyer_file(buyer_file_name[i]);
                        while(getline(buyer_file,buyer_input)){
                            if(buyer_id.compare(buyer_input.substr(8,20))==0){
                                tmps = buyer_input.substr(buyer_input.find("buyername:")+10,50);
                                tmpss << tmps;
                                tmpss >> buyer_name;
                                tmpss.str("");
                                buyer_flag = true;
                                break;
                            }
                        }
                        buyer_file.close();
                        if(buyer_flag)break;
                    }
            // good name and price
                string good_id = order_input.substr(order_input.find("goodid:")+7,21);
                bool good_flag = false;
                for(int i = 0;i < good_file_num;i++){
                        ifstream good_file(good_file_name[i]);
                        while(getline(good_file,good_input)){
                            if(good_id.compare(good_input.substr(7,21))==0){
                                tmps = good_input.substr(good_input.find("good_name:")+10,50);
                                tmpss << tmps;
                                tmpss >> good_name;
                                tmpss.str("");
                                tmps = good_input.substr(good_input.find("price:")+6,50);
                                tmpss << tmps;
                                tmpss >> price;
                                tmpss.str("");
                                good_flag = true;
                                break;
                            }
                        }
                        good_file.close();
                        if(good_flag)break;
                    }

                flag = true;
                break;
            }
        }
        order_file.close();
        if(flag)break;
    }
    if(flag){
        // order id
        cout << "OrderID:" << order_id  << "\t";
        // buyer name
        cout << "BuyerName:" << buyer_name  << "\t";
        // good name
        cout << "GoodName:" << good_name  << "\t";
        // amount
        cout << "Amount:" << amount  << "\t";
        // price
        cout << "Price:" << price  << "\t";
        // price*amount
        cout << "Price*Amount:" << price*amount  << "\t";
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