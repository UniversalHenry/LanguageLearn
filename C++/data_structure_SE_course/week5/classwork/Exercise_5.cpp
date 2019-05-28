#include<iostream>
#include<string>
#include<vector>
#include<sstream>
#include<map>
#include<fstream>
#include<ctime>
#include<algorithm>

using namespace std;

void split(const string &s, vector<string> &sv, const char flag);

class Buyer{
    public:
        string buyerid;
        string contactphone;
        string address;
        string buyername;
        vector<string> orderIds;

        Buyer(){};

        Buyer(string line)
        {
            vector<string> parts;
            split(line, parts, '\t');
            for (int i = 0; i < parts.size();i++)
            {
                if(parts[i].find("buyerid")==0)
                {
                    buyerid = parts[i].substr(parts[i].find_first_of(':')+1);
                }
                else if(parts[i].find("contactphone")==0)
                {
                    contactphone = parts[i].substr(parts[i].find_first_of(':')+1);
                }
                else if(parts[i].find("address")==0)
                {
                    address = parts[i].substr(parts[i].find_first_of(':')+1);
                }
                else if(parts[i].find("buyername")==0)
                {
                    buyername = parts[i].substr(parts[i].find_first_of(':')+1);
                }
            }
        }
    };

    class Good{
        public:
        string goodid;
        string salerid;
        string good_name;
        string description;
        double price;
        vector<string> orderIds;

        Good(){};
        Good(string line){
            vector<string> parts;
            split(line, parts, '\t');
            for (int i = 0; i < parts.size();i++)
            {
                if(parts[i].find("goodid")==0)
                {
                    goodid = parts[i].substr(parts[i].find_first_of(':')+1);
                }
                else if(parts[i].find("salerid")==0)
                {
                    salerid = parts[i].substr(parts[i].find_first_of(':')+1);
                }
                else if(parts[i].find("good_name")==0)
                {
                    good_name = parts[i].substr(parts[i].find_first_of(':')+1);
                }
                else if(parts[i].find("description")==0)
                {
                    description = parts[i].substr(parts[i].find_first_of(':')+1);
                }
                else if(parts[i].find("price")==0)
                {
                    price = atof(parts[i].substr(parts[i].find_first_of(':')+1).c_str());
                }
            }
        }
};

class Order{
    public:
        string orderid;
        uint32_t createtime;
        string buyerid;
        string goodid;
        uint32_t amount;
        bool done;

        Order(){};
        Order(string line){
            vector<string> parts;
            split(line, parts, '\t');
            for (int i = 0; i < parts.size();i++)
            {
                if(parts[i].find("goodid")==0)
                {
                    goodid = parts[i].substr(parts[i].find_first_of(':')+1);
                }
                else if(parts[i].find("orderid")==0)
                {
                    orderid = parts[i].substr(parts[i].find_first_of(':')+1);
                }
                else if(parts[i].find("buyerid")==0)
                {
                    buyerid = parts[i].substr(parts[i].find_first_of(':')+1);
                }
                else if(parts[i].find("createtime")==0)
                {
                    createtime = strtoul(parts[i].substr(parts[i].find_first_of(':')+1).c_str(),NULL,10);
                }
                else if(parts[i].find("amount")==0)
                {
                    amount = strtoul(parts[i].substr(parts[i].find_first_of(':')+1).c_str(),NULL,10);
                }
                else if(parts[i].find("done")==0)
                {
                    string tempString = parts[i].substr(parts[i].find_first_of(':')+1);
                    if(tempString == "true")
                    {
                        done = true;
                    }
                    else{
                        done = false;
                    }
                }
            }
        }
};

void split(const string& s,vector<string>& sv,const char flag) {
    sv.clear();
    istringstream iss(s);
    string temp;

    while (getline(iss, temp, flag)) {
        sv.push_back(temp);
    }
    return;
}

void getInfo(map<string, Buyer>& buyers, map<string, Good>& goods, map<string, Order>& orders){
    vector<string> buyerFiles;
    buyerFiles.push_back("lesson/data/buyer.0.0");
    buyerFiles.push_back("lesson/data/buyer.1.1");
    vector<string> goodFiles;
    goodFiles.push_back("lesson/data/good.0.0");
    goodFiles.push_back("lesson/data/good.1.1");
    goodFiles.push_back("lesson/data/good.2.2");
    vector<string> orderFiles;
    orderFiles.push_back("lesson/data/order.0.0");
    orderFiles.push_back("lesson/data/order.0.3");
    orderFiles.push_back("lesson/data/order.1.1");
    orderFiles.push_back("lesson/data/order.2.2");
    // orderFiles.push_back("lesson/data/order.small");

    for (int i = 0; i < buyerFiles.size();i++){
        fstream file;
        file.open(buyerFiles[i], ios::in);
        if(file.is_open())
        {
            while(!file.eof())
            {
                string line = "";
                getline(file, line);
                Buyer buyer(line);
                buyers.insert(make_pair(buyer.buyerid, buyer));
            }
            cout << "finish " + buyerFiles[i] + "\n";
        }
        else{
            cout << "file not exist: " + buyerFiles[i] + "\n";
        }
    }
    
    for (int i = 0; i < goodFiles.size();i++){
        fstream file;
        file.open(goodFiles[i], ios::in);
        if(file.is_open())
        {
            while(!file.eof())
            {
                string line = "";
                getline(file, line);
                Good good(line);
                goods.insert(make_pair(good.goodid, good));
            }
            cout << "finish " + goodFiles[i] + "\n";
        }
        else{
            cout << "file not exist: " + goodFiles[i] + "\n";
        }
    }
    
    for (int i = 0; i < orderFiles.size();i++){
        fstream file;
        file.open(orderFiles[i], ios::in);
        if(file.is_open())
        {
            while(!file.eof())
            {
                string line = "";
                getline(file, line);
                Order order(line);
                orders.insert(make_pair(order.orderid, order));
                buyers[order.buyerid].orderIds.push_back(order.orderid);
                goods[order.goodid].orderIds.push_back(order.orderid);
            }
            cout << "finish " + orderFiles[i] + "\n";
        }
        else{
            cout << "file not exist: " + orderFiles[i] + "\n";
        }
    }
}

template<class T1>
struct compareByValue
{
    bool operator()(const T1 &lhs, const T1 &rhs)
    {
        return lhs.second>=rhs.second;
    }
};

int main()
{
    map<string, Buyer> buyers;
    map<string, Good> goods;
    map<string, Order> orders;
    getInfo(buyers, goods, orders);
    while (true)
    {
        int func = 0;
        cout << "Please enter 1 or 2 to choose the function you want.\n";
        cin >> func;
        if(func == 1)
        {
            cout << "Please enter buyerid\n";
            string buyerid;
            cin >> buyerid;
            if (buyers.count(buyerid) == 0)
            {
                cout << "no such buyer\n";
            }
            else{
                Buyer buyer = buyers[buyerid];
                vector<int> orderCounts(7,0);
                vector<double> totalAmount(7,0.0);
                for (int i = 0; i < buyer.orderIds.size(); i++)
                {
                    Order order = orders[buyer.orderIds[i]];
                    time_t time(order.createtime);
                    tm *gmtm = gmtime(&time);
                    orderCounts[gmtm->tm_wday]++;
                    totalAmount[gmtm->tm_wday] += (double)order.amount * goods[order.goodid].price;
                }
                for (int i = 0; i < 7;i++){
                    printf("ordercount:%d\ttotalAmount:%f\tAverage:%f\n", orderCounts[i], totalAmount[i], totalAmount[i] / orderCounts[i]);
                }
            }
        }
        else if (func==2)
        {
            map<string, double> targetBuyers;
            map<string, int> targetGoods;
            cout << "Please enter the date you want as: xxxx xx xx\n";
            int year, month, day;
            cin >> year >> month >> day;
            --month;
            year -= 1900;
            for (auto it = orders.begin(); it != orders.end();it++)
            {
                time_t time(it->second.createtime);
                tm *gmtm = gmtime(&time);
                // cout << gmtm->tm_year << " " << gmtm->tm_mon << " " << gmtm->tm_mday << endl;
                if(gmtm->tm_year == year && gmtm->tm_mon == month && gmtm->tm_mday == day)
                {
                    if(targetBuyers.count(it->second.buyerid)==0)
                    {
                        targetBuyers.insert(make_pair(it->second.buyerid, goods[it->second.goodid].price * it->second.amount));
                    }
                    else
                    {
                        targetBuyers[it->second.buyerid] += goods[it->second.goodid].price * it->second.amount;
                    }
                    if(targetGoods.count(it->second.goodid)==0)
                    {
                        targetGoods.insert(make_pair(it->second.goodid, it->second.amount));
                    }
                    else
                    {
                        targetGoods[it->second.goodid] += it->second.amount;
                    }
                }
            }
            vector<pair<string, double>> targetBuyersV(targetBuyers.begin(), targetBuyers.end());
            sort(targetBuyersV.begin(), targetBuyersV.end(), compareByValue<pair<string, double>>());
            vector<pair<string, int>> targetGoodsV(targetGoods.begin(), targetGoods.end());
            sort(targetGoodsV.begin(), targetGoodsV.end(), compareByValue<pair<string, int>>());
            if(targetGoodsV.empty()){
                cout << "No order at that day!\n";
            }
            else{
                cout << "Most popular Goods\tQuantity\tGood_name\n";
                for (int i = 0; i < 3 && i < targetGoodsV.size();i++)
                {
                    cout << targetGoodsV[i].first << "\t" << targetGoodsV[i].second << "\t\t" << goods[targetGoodsV[i].first].good_name << endl;
                }
                cout << "Richest buyer\t\tAmount\t\tBuyer_name\n";
                for (int i = 0; i < 3 && i< targetBuyers.size();i++)
                {
                    cout << targetBuyersV[i].first << "\t" << targetBuyersV[i].second << "\t\t" << buyers[targetBuyersV[i].first].buyername << endl;
                }
            }
        }
        else
        {
            cout << "Error function.\n";
        }
    }
    system("pause");
}
