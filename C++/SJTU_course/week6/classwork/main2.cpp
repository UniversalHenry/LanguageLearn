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
#include <memory>

using namespace std;

// function
string find_val(const string &content,const string &key);
template <class T> bool good_sold_less(const T& gid1,const T& gid2);
int get_wday(const long &time);
bool is_validtime(const string &date);
bool is_happen(const long &createtime,const string &date);

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
        int buy_num_wday[7] = {0};
        int payment_wday[7] = {0};
        int buy_num;
        double payment;
        vector<int> orderid;
        Buyer(const string &content):buyerid(find_val(content,"buyerid")),contactphone(find_val(content,"contactphone")),
            address(find_val(content,"address")),buy_num(0),payment(0),buyername(find_val(content,"buyername")){};
        void add_order(const int &order){orderid.push_back(order);}
};

class Order{
    public:
        int orderid;
        long createtime;
        string buyerid;
        string goodid;
        string remark;
        bool done;
        int amount;
        Order(const string &content):buyerid(find_val(content,"buyerid")),goodid(find_val(content,"goodid")){
            stringstream ss;
            ss << find_val(content,"orderid");ss >> orderid;ss.clear();ss.str("");
            ss << find_val(content,"createtime");ss >> createtime;ss.clear();ss.str("");
            ss << find_val(content,"amount");ss >> amount;ss.clear();ss.str("");
            if(content.find("remark:")>=0){remark=find_val(content,"remark");}
            else{remark="";}
            if(find_val(content,"done").compare("true")==0){done=true;}
            else{done=false;}
        }
};

map<string,Good> goods;
map<string,Buyer> buyers;
map<int,Order> orders;

struct Good_By_Sold{
    public:
    string id;
        bool operator< (const Good_By_Sold& g) const {
            map<string,Good>::iterator g1,g2;
            g1 = goods.find(id);
            g2 = goods.find(g.id);
            if(g1->second.sold==g2->second.sold)return(id<g.id);
            else return((g1->second.sold)<(g2->second.sold)); 
        }
};

struct Buyer_By_Pay{
    public:
    string id;
        bool operator< (const Buyer_By_Pay& b) const {
            map<string,Buyer>::iterator b1,b2;
            b1 = buyers.find(id);
            b2 = buyers.find(b.id);
            if(b1->second.payment==b2->second.payment)return(id<b.id);
            else return((b1->second.payment)<(b2->second.payment)); 
        }
};

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

map<string,Buyer>::iterator the_buyer;
map<string,Good>::iterator the_good;
map<int,Order>::iterator the_order;

set<Good_By_Sold> goods_by_sold;
set<Buyer_By_Pay> buyers_by_pay;

while(true){
    cout << "Please input the date(\":q\" to exit):";
    string date;
    cin >> date;
    if(date == ":q")break;
    if(!is_validtime(date))continue;
    // good amount
    {
        the_good = goods.begin();
        while(the_good!=goods.end()){
            n = the_good->second.orderid.size();
            for(int i=0; i<n; i++){
                the_order = orders.find(the_good->second.orderid[i]);
                if(!is_happen(the_order->second.createtime,date))continue;
                the_good->second.sold += the_order->second.amount;
            }
            the_good++;
        }

        the_good = goods.begin();
        Good_By_Sold goodid_by_sold;
        while(the_good!=goods.end()){
            goodid_by_sold.id = the_good->second.goodid;
            goods_by_sold.insert(goodid_by_sold);
            the_good++;
        }
    }
    // buyer buy_num and payment
    {
        the_buyer = buyers.begin();
        while(the_buyer!=buyers.end()){
            n = the_buyer->second.orderid.size();
            for(int i=0; i<n; i++){
                the_order = orders.find(the_buyer->second.orderid[i]);
                if(!is_happen(the_order->second.createtime,date))continue;
                the_buyer->second.buy_num+=the_order->second.amount;
                the_good = goods.find(the_order->second.goodid);
                the_buyer->second.payment+=the_order->second.amount*the_good->second.price;
            }
            the_buyer++;
        }

        the_buyer = buyers.begin();
        Buyer_By_Pay buyerid_by_pay;
        while(the_buyer!=buyers.end()){
            buyerid_by_pay.id = the_buyer->second.buyerid;
            buyers_by_pay.insert(buyerid_by_pay);
            the_buyer++;
        }
    }

    int print_num = 3;
    // good
    {   
        set<Good_By_Sold>::iterator goodid_by_sold;
        goodid_by_sold = goods_by_sold.begin();
        n=0;
        while(goodid_by_sold!=goods_by_sold.end()){
            the_good = goods.find(goodid_by_sold->id);
            n++;
            cout << "ORDER::" << n << endl;
            cout << "GoodID:" << the_good->first << endl;
            cout << "Sold:" << the_good->second.sold << endl;
            cout << "****************************************************" << endl;
            goodid_by_sold++;
            if(n>=print_num)break;
        }
    }
    // buyer
    {   
        set<Buyer_By_Pay>::iterator buyerid_by_pay;
        buyerid_by_pay = buyers_by_pay.begin();
        n=0;
        while(buyerid_by_pay!=buyers_by_pay.end()){
            the_buyer = buyers.find(buyerid_by_pay->id);
            n++;
            cout << "ORDER::" << n << endl;
            cout << "BuyerID:" << the_buyer->first << endl;
            cout << "Pay:" << the_buyer->second.payment << endl;
            cout << "NumberOfOrders:" << the_buyer->second.buy_num << endl;
            cout << "****************************************************" << endl;
            buyerid_by_pay++;
            if(n>=print_num)break;
        }
    }
}



// time stop
    end = clock();
    dur = (double)(end - start);
    printf("\nUseTime:%f",(dur/CLOCKS_PER_SEC));
	cout << "\nProgram finished.";
	getchar();
    return 0;
}

string find_val(const string &content,const string &key){
    stringstream ss;
    string s;
    ss << content.substr(content.find(key+":")+key.length()+1);
    ss >> s;
    return s;
}

bool is_validtime(const string &date){
    if(date.size()!=8)return false;
    stringstream ss;
    ss << date;
    long d;
    ss >> d;
    if(d/10000 > 2018 || d /10000 <2010)return false;
    return true;
}

bool is_happen(const long &createtime,const string &date){
    time_t timep = createtime;
    struct tm *p;
    p = gmtime(&timep);
    stringstream ss;
    ss << date;
    int d;
    ss >> d;
    int yy = d / 10000;
    int mm = (d % 10000)/100;
    int dd = d % 100;
    if(p->tm_year == yy && p->tm_mon == (mm - 1) && p->tm_mday == dd)return true;
    return false;
}