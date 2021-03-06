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
const string wdayname[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

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
    /*
    // good amount
    {
        the_good = goods.begin();
        while(the_good!=goods.end()){
            n = the_good->second.orderid.size();
            for(int i=0; i<n; i++){
                the_order = orders.find(the_good->second.orderid[i]);
                if(the_order->second.done)the_good->second.sold+=the_order->second.amount;
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
                if(the_order->second.done){
                    the_buyer->second.buy_num+=the_order->second.amount;
                    the_good = goods.find(the_order->second.goodid);
                    the_buyer->second.payment+=the_order->second.amount*the_good->second.price;
                }
            }
            the_buyer++;
        }
    }
    */
    // buyer buy_num and payment by workday
    {
        the_buyer = buyers.begin();
        while(the_buyer!=buyers.end()){
            n = the_buyer->second.orderid.size();
            for(int i=0; i<n; i++){
                the_order = orders.find(the_buyer->second.orderid[i]);
                int wday = get_wday(the_order->second.createtime);
                the_buyer->second.buy_num_wday[wday] ++;
                the_good = goods.find(the_order->second.goodid);
                the_buyer->second.payment_wday[wday] += the_order->second.amount*the_good->second.price;
            }
            the_buyer++;
        }
    }

// output result
/*
int print_num = 100;
    // good
    {
        the_good = goods.begin();
        n=0;
        while(the_good!=goods.end()){
            n++;
            cout << "LINE::" << n << endl;
            cout << "GoodID:" << the_good->first << endl;
            cout << "Orders:" << the_good->second.orderid.size() << endl;
            cout << "Sold:" << the_good->second.sold << endl;
            cout << "****************************************************" << endl;
            the_good++;
            if(n>=print_num)break;
        }
    }
    // buyer
    {
        the_buyer = buyers.begin();
        n=0;
        while(the_buyer!=buyers.end()){
            n++;
            cout << "LINE::" << n << endl;
            cout << "BuyerID:" << the_buyer->first << endl;
            cout << "Orders:" << the_buyer->second.orderid.size() << endl;
            cout << "Payment:" << the_buyer->second.payment << endl;
            cout << "****************************************************" << endl;
            the_buyer++;
            if(n>=print_num)break;
        }
    }
    // best sell goods
    {   
        set<Good_By_Sold>::iterator goodid_by_sold;
        goodid_by_sold = goods_by_sold.end();
        n=0;
        while(goodid_by_sold!=goods_by_sold.begin()){
            goodid_by_sold--;
            the_good = goods.find(goodid_by_sold->id);
            n++;
            cout << "LINE::" << n << endl;
            cout << "GoodID:" << the_good->first << endl;
            cout << "Orders:" << the_good->second.orderid.size() << endl;
            cout << "Sold:" << the_good->second.sold << endl;
            cout << "****************************************************" << endl;
            if(n>=print_num)break;
        }
    }
*/
while(true){
    cout << "Please input the buyerID(\":q\" to exit):";
    string buyerid;
    cin >> buyerid;
    if(buyerid == ":q")break;
    the_buyer = buyers.find(buyerid);
    if(the_buyer == buyers.end())continue;
    for(int i = 0; i<7; i++){
        cout << wdayname[i] << ":\tNumber of orders:" 
            << the_buyer->second.buy_num_wday[i] <<"\tTotal amount:" 
            << the_buyer->second.payment_wday[i] <<"\tAverage amount of an order:"
            << the_buyer->second.payment_wday[i]/the_buyer->second.buy_num_wday[i] << endl;
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

int get_wday(const long &time){
    time_t timep=time;
    struct tm *p;
    p = gmtime(&timep);
    return p->tm_wday;
}