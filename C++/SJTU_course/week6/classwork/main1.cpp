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

// function
string find_val(const string &content,const string &key);

// data
class Good{
    public:
        string goodid;
        string salerid;
        string good_name;
        string description;
        double price;
        int sold;
        vector<int> orderid;
        Good(const string &content):goodid(find_val(content,"goodid")),salerid(find_val(content,"salerid")),
            good_name(find_val(content,"good_name")),sold(0){stringstream ss;ss << find_val(content,"price");ss >> price;}
        void add_order(const int &order){orderid.push_back(order);}
};

class Buyer{
    public:
        string buyerid;
        string contactphone;
        string address;
        string buyername;
        int buy_num;
        double payment;
        vector<int> orderid;
        Buyer(const string &content):buyerid(find_val(content,"buyerid")),contactphone(find_val(content,"contactphone")),
            address,buy_num(0),payment(0)(find_val(content,"address")),buyername(find_val(content,"buyername")){};
        void add_order(const int &order){orderid.push_back(order);}
};

class Order{
    public:
        int orderid;
        int createtime;
        string buyerid;
        string goodid;
        string remark;
        bool done;
        int amount;
        Order(const string &content):buyerid(find_val(content,"buyerid")),goodid(find_val(content,"goodid")){
            stringstream ss;
            ss << find_val(content,"orderid");
            ss >> orderid;
            ss.str("");
            ss << find_val(content,"createtime");
            ss >> createtime;
            ss.str("");
            ss << find_val(content,"amount");
            ss >> amount;
            ss.str("");
            if(content.find("remark:")>=0){remark=find_val(content,"remark");}
            else{remark="";}
            if(find_val(content,"done").compare("true")==0){done=true;}
            else{done=false;}
        }
};

map<string,Good> goods;
map<string,Buyer> buyers;
map<int,Order> orders;

// file

class GoodFile{
        string dir;
    public:
        vector<string> name;
        ifstream file;
        bool open;
        string open_file_name;
        GoodFile(string d="data/good."):open_file_name(""),dir(d),open(0){};
        void add_file(const string &s){name.push_back(dir+s);}
        void open_file(const int &i){if(open)file.close();file.open(name.at(i).c_str());open_file_name=name.at(i);open=true;}
        void close_file(){if(open)file.close();open=false;open_file_name="";}
        ~GoodFile(){if(open)file.close();}
}good_file;

class BuyerFile{
        string dir;
    public:
        vector<string> name;
        ifstream file;
        bool open;
        string open_file_name;
        BuyerFile(string d="data/buyer."):open_file_name(""),dir(d),open(0){};
        void add_file(const string &s){name.push_back(dir+s);}
        void open_file(const int &i){if(open)file.close();file.open(name.at(i).c_str());open_file_name=name.at(i);open=true;}
        void close_file(){if(open)file.close();open=false;open_file_name="";}
        ~BuyerFile(){if(open)file.close();}
}buyer_file;

class OrderFile{
        string dir;
    public:
        vector<string> name;
        ifstream file;
        bool open;
        string open_file_name;
        OrderFile(string d="data/order."):open_file_name(""),dir(d),open(0){};
        void add_file(const string &s){name.push_back(dir+s);}
        void open_file(const int &i){if(open)file.close();file.open(name.at(i).c_str());open_file_name=name.at(i);open=true;}
        void close_file(){if(open)file.close();open=false;open_file_name="";}
        ~OrderFile(){if(open)file.close();}
}order_file;

int main(void){
// time start
    double dur;
    clock_t start,end;
    start = clock();

// file
    good_file.add_file("0.0");
    good_file.add_file("1.1");
    good_file.add_file("2.2");
    buyer_file.add_file("0.0");
    buyer_file.add_file("1.1");
    order_file.add_file("0.0");
    order_file.add_file("0.3");
    order_file.add_file("1.1");
    order_file.add_file("2.2");

// read in info
    int n;
    string input;
    // good
    n=good_file.name.size();
    for(int i=0; i<n;i++){
        good_file.open_file(i);
        while(getline(good_file.file,input)){
            Good tmp_good(input);
            goods.insert(make_pair(tmp_good.goodid,tmp_good));
        }
    }
    // buyer
    n=buyer_file.name.size();
    for(int i=0; i<n;i++){
        buyer_file.open_file(i);
        while(getline(buyer_file.file,input)){
            Buyer tmp_buyer(input);
            buyers.insert(make_pair(tmp_buyer.buyerid,tmp_buyer));
        }
    }
    // order
    n=order_file.name.size();
    for(int i=0; i<n;i++){
        order_file.open_file(i);
        while(getline(order_file.file,input)){
            Order tmp_order(input);
            orders.insert(make_pair(tmp_order.orderid,tmp_order));
            goods.find(tmp_order.goodid)->second.add_order(tmp_order.orderid);
            buyers.find(tmp_order.buyerid)->second.add_order(tmp_order.orderid);
        }
    }

// calculate result

// output result
    cout << goods.size() << endl << buyers.size() << endl << orders.size() << endl;
// time stop
    end = clock();
    dur = (double)(end - start);
    printf("\nUseTime:%f",(dur/CLOCKS_PER_SEC));
	cout << "\nProgram finished.";
	int test;
	cin >> test;
    return 0;
}

string find_val(const string &content,const string &key){
    stringstream ss;
    string s;
    ss << content.substr(content.find(key+":")+key.length()+1);
    ss >> s;
    return s;
}
