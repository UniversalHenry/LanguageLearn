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
bool is_weekend(const long &createtime);
bool is_night(const long &createtime);

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
        int buy_num_weekend[2] = {0};
        int buy_num_night[2] = {0};
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

map<string,Buyer>::iterator the_buyer_tar;

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
            double m = the_buyer_tar->second.buy_num_night[0] * the_buyer_tar->second.buy_num_night[0]
                + the_buyer_tar->second.buy_num_night[1] * the_buyer_tar->second.buy_num_night[1]
                + the_buyer_tar->second.buy_num_weekend[0] * the_buyer_tar->second.buy_num_weekend[0]
                + the_buyer_tar->second.buy_num_weekend[1] * the_buyer_tar->second.buy_num_weekend[1];
                double m1 = b1->second.buy_num_night[0] * b1->second.buy_num_night[0]
                    + b1->second.buy_num_night[1] * b1->second.buy_num_night[1]
                    + b1->second.buy_num_weekend[0] * b1->second.buy_num_weekend[0]
                    + b1->second.buy_num_weekend[1] * b1->second.buy_num_weekend[1];
                double m2 = b2->second.buy_num_night[0] * b2->second.buy_num_night[0]
                    + b2->second.buy_num_night[1] * b2->second.buy_num_night[1]
                    + b2->second.buy_num_weekend[0] * b2->second.buy_num_weekend[0]
                    + b2->second.buy_num_weekend[1] * b2->second.buy_num_weekend[1];
            if(m > 0){
                double x1 = the_buyer_tar->second.buy_num_night[0] * b1->second.buy_num_night[0]
                    + the_buyer_tar->second.buy_num_night[1] * b1->second.buy_num_night[1]
                    + the_buyer_tar->second.buy_num_weekend[0] * b1->second.buy_num_weekend[0]
                    + the_buyer_tar->second.buy_num_weekend[1] * b1->second.buy_num_weekend[1];
                double x2 = the_buyer_tar->second.buy_num_night[0] * b2->second.buy_num_night[0]
                    + the_buyer_tar->second.buy_num_night[1] * b2->second.buy_num_night[1]
                    + the_buyer_tar->second.buy_num_weekend[0] * b2->second.buy_num_weekend[0]
                    + the_buyer_tar->second.buy_num_weekend[1] * b2->second.buy_num_weekend[1];
                x1 /= sqrt(m1 * m);
                x2 /= sqrt(m2 * m);
                if(x1 == x2)return(id<b.id);
                    else return(x1 < x2);
            }
            else{
                if(m1 == m2)return(id<b.id);
                    else return(m1 < m2);
            }
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
    cout << "Please input the buyer ID(\":q\" to exit):";
    string b_id;
    cin >> b_id;
    if(b_id == ":q")break;
    the_buyer_tar = buyers.find(b_id);
    if(the_buyer_tar == buyers.end())continue;
    {
        the_buyer = buyers.begin();
        while(the_buyer!=buyers.end()){
            n = the_buyer->second.orderid.size();
            for(int i=0; i<n; i++){
                the_order = orders.find(the_buyer->second.orderid[i]);
                the_buyer->second.buy_num++;
                if(is_weekend(the_order->second.createtime))the_buyer->second.buy_num_weekend[0]++;
                    else the_buyer->second.buy_num_weekend[1]++;
                if(is_night(the_order->second.createtime))the_buyer->second.buy_num_night[0]++;
                    else the_buyer->second.buy_num_night[1]++;
                the_good = goods.find(the_order->second.goodid);
                the_buyer->second.payment+=the_order->second.amount*the_good->second.price;
            }
            the_buyer++;
        }

        the_buyer = buyers.begin();
        Buyer_By_Pay buyerid_by_pay;
        while(the_buyer!=buyers.end()){
            buyerid_by_pay.id = the_buyer->second.buyerid;
            if(buyerid_by_pay.id == the_buyer_tar->second.buyerid){
                the_buyer++;continue;
            }
            buyers_by_pay.insert(buyerid_by_pay);
            the_buyer++;
        }
    }

    int print_num = 3;
    // buyer
    {   
        the_buyer = the_buyer_tar;
        n++;
        cout << "TargetBuyerID:" << the_buyer->first << endl;
        cout << "OrderWeekend:" << the_buyer->second.buy_num_weekend[0] << endl;
        cout << "OrderWorkday:" << the_buyer->second.buy_num_weekend[1] << endl;
        cout << "OrderNight:" << the_buyer->second.buy_num_night[0] << endl;
        cout << "OrderDay:" << the_buyer->second.buy_num_night[1] << endl;
        cout << "Type:";
        if(the_buyer->second.buy_num_night[0] < the_buyer->second.buy_num_night[1])cout << 'D';
            else cout << 'N';
        if(the_buyer->second.buy_num_weekend[0] < the_buyer->second.buy_num_weekend[1])cout << 'O';
            else cout << 'W';
        cout << endl;
        cout << "NumberOfOrders:" << the_buyer->second.buy_num << endl;
        cout << "****************************************************" << endl;

        set<Buyer_By_Pay>::iterator buyerid_by_pay;
        buyerid_by_pay = buyers_by_pay.end();
        n=0;
        while(buyerid_by_pay!=buyers_by_pay.begin()){
            buyerid_by_pay--;
            the_buyer = buyers.find(buyerid_by_pay->id);
            n++;
            cout << "SimilarBuyerID:" << the_buyer->first << endl;
            cout << "OrderWeekend:" << the_buyer->second.buy_num_weekend[0] << endl;
            cout << "OrderWorkday:" << the_buyer->second.buy_num_weekend[1] << endl;
            cout << "OrderNight:" << the_buyer->second.buy_num_night[0] << endl;
            cout << "OrderDay:" << the_buyer->second.buy_num_night[1] << endl;
            cout << "Type:";
            if(the_buyer->second.buy_num_night[0] < the_buyer->second.buy_num_night[1])cout << 'D';
                else cout << 'N';
            if(the_buyer->second.buy_num_weekend[0] < the_buyer->second.buy_num_weekend[1])cout << 'O';
                else cout << 'W';
            cout << endl;
            cout << "NumberOfOrders:" << the_buyer->second.buy_num << endl;
            cout << "****************************************************" << endl;
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
    if((p->tm_year+1900) == yy && p->tm_mon == (mm - 1) && p->tm_mday == dd)return true;
    return false;
}

bool is_weekend(const long &createtime){
    time_t timep = createtime;
    struct tm *p;
    p = gmtime(&timep);
    if(p->tm_wday == 0 || p->tm_wday == 6)return true;
    return false;
}

bool is_night(const long &createtime){
    time_t timep = createtime;
    struct tm *p;
    p = gmtime(&timep);
    if(p->tm_hour < 6 || p->tm_hour > 18)return true;
    return false;
}