#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_
#include <queue>
#include <vector>
#include <iostream>
#include <map>
#include <fstream>
using namespace std;

struct Bin{
	vector<unsigned char> con;
	int num = 0;
	bool operator< (const Bin& b) const{
		if(num == b.num){
			for(int i = 0; i < con.size(); i++){
				if(con[i] != b.con[i]) return con[i] < b.con[i];
				else if(i == con.size() - 1) return true;
			}
		}
		else return num < b.num;
	}
};

Bin add_bin(const Bin &b1, const Bin &b2);
Bin gen_bin(const vector<unsigned char> & str);
Bin gen_bin(const vector<unsigned char> & str, int i);
Bin read_bin(const Bin &b, int pos, int len);
ostream& operator<<(ostream& out, const Bin& b);
struct cmp
{bool operator()(const pair<int,int> &n1, const pair<int,int> &n2) 
{ return (n1.first < n2.first);}
};

class Huffman {
public:
	vector<unsigned char> encode(const vector<unsigned char> & str);
	vector<unsigned char> decode(const vector<unsigned char> & str);
	Huffman():Hfm_tree_top(0){};

private:
	map<unsigned char,int> Freq;
	priority_queue<pair<int,int>,vector<pair<int,int> >, cmp> Freq_index;
	map<int,vector<int> > Hfm_tree;
	int Hfm_tree_top;
	map<unsigned char,Bin> Hfm_index;
	map<Bin,unsigned char> Hfm_decode;

	int right_son_node(int i);
	int left_son_node(int i);
	void combine(pair<int,int> &n1,pair<int,int> &n2);

	int bin_decode(const Bin &bin);
	Bin bin_encode(int i);

	Bin gencode();
	Bin encode_content(const vector<unsigned char> & str);
	void gen_hfm_index(int top,Bin b);
	int loadcode(Bin & bin);
	vector<unsigned char> decode_content(const Bin & bin, int pointer);
};

Bin add_bin(const Bin &b1, const Bin &b2){
	Bin b;
	b.num = b1.num + b2.num;
	int l = b1.num % 8;
	if(l == 0)	{
		b.con = b1.con;
		b.con.insert(b.con.end(),b2.con.begin(),b2.con.end());
	}else{
		int r = 8 - l;
		int k = r;
		l = 1 << l;
		r = 1 << r;
		b.con = b1.con;
		b.con.pop_back();
		unsigned char c = int(b1.con[b1.num / 8]) / r * r +
			int(b2.con[0]) / l;
		b.con.push_back(c);
		while(k < b2.num){
			c = int(b2.con[k / 8]) * r % 256 +
			 	int(b2.con[k / 8 + 1]) / l;
			b.con.push_back(c);
			k += 8;
		}
	}
	while(b.con.size() > b.num / 8 + 2) b.con.pop_back();
	return b;
}

Bin gen_bin(const vector<unsigned char> & str){
	Bin b;
	for(int i = 0; i < str.size(); i++) b.con.push_back(str[i]);
	b.num = str.size() * sizeof(unsigned char);
	return b;
}

Bin gen_bin(const vector<unsigned char> & str, int i){
	Bin b;
	b.num = i;
	int s = (i - 1) / 8 + 1;
	for(int i = 0; i < s; i++) b.con.push_back(str[i]);
	return b;
}

Bin read_bin(const Bin &bin, int pos, int len){
	Bin b;
	b.num = len;
	int l = pos % 8;
	if(l == 0){
		b.con.insert(b.con.end(),bin.con.begin() + pos / 8,bin.con.begin() + len / 8 + pos / 8);
	}else{
		Bin tmpb1, tmpb2;
		tmpb1.num = 8 - l;
		tmpb1.con.push_back('x');
		tmpb2.num = len + l;
		tmpb2.con.insert(tmpb2.con.begin(), bin.con.begin() + pos / 8, bin.con.begin() + pos / 8 + len / 8);
		b = add_bin(tmpb1,tmpb2);
		b.num = len;
		b.con.insert(b.con.begin(), b.con.begin() + 1, b.con.end());
	}
	return b;
}

ostream& operator<<(ostream & out, const Bin & b){
	for(int i = 0; i < b.num; i++){
		unsigned char c = (1 << (7 - (i % 8))) % 256;
		if(b.con[i / 8] & c) out << "1";
		else out << "0";
	}
	return out;
}

int Huffman::right_son_node(int i){
	if(Hfm_tree.count(i) == 0) return 1000;
	if(Hfm_tree[i].size() <= 1) return 500;
	return Hfm_tree[i][1];
}

int Huffman::left_son_node(int i){
	if(Hfm_tree.count(i) == 0) return 1000;
	if(Hfm_tree[i].size() <= 0) return 500;
	return Hfm_tree[i][0];
}

int Huffman::bin_decode(const Bin &bin){
	int l = bin.num - 1;
	int p = bin.con[0];
	int index = (l << 8) + p;
	return index;
}

Bin Huffman::bin_encode(int i){
	Bin b;
	b.num = (i >> 8) + 1;
	unsigned char c = i % 256;
	b.con.push_back(c);
	return b;
}

void Huffman::combine(pair<int,int> &n1,pair<int,int> &n2){
	--Hfm_tree_top;
	Hfm_tree[Hfm_tree_top].push_back(n1.first);
	Hfm_tree[Hfm_tree_top].push_back(n2.first);
	n1.first += n2.first;
	n1.second = Hfm_tree_top;
	Freq_index.push(n1);
}

Bin Huffman::encode_content(const vector<unsigned char> & str){
	Hfm_index.clear();
	for(int i = 0; i < str.size(); i++){
		if(Freq.count(str[i])){
			Freq[str[i]]++;
		}else{
			Freq[str[i]] = 0;
		}
	}
	map<unsigned char, int>::iterator  it = Freq.begin();
	while(it != Freq.end()){
		Freq_index.push(make_pair(it->second,int(it->first)));
		it++;
	}
	while(Freq_index.size() > 1){
		pair<int,int> n1 = Freq_index.top();
		Freq_index.pop();
		pair<int,int> n2 = Freq_index.top();
		Freq_index.pop();
		if(n1.first < n2.first) combine(n1,n2);
		else combine(n2,n1);
	}
	Bin bout;
	gen_hfm_index(Hfm_tree_top,bout);
	for(int i = 0; i < str.size(); i++){
		bout = add_bin(bout,Hfm_index[str[i]]);
	}
	cout << "content:" << bout << endl; ////
	return bout;
}

void Huffman::gen_hfm_index(int top,Bin b){
	if(top >= 0){
		if(top < 256){
			unsigned char c = top;
			Hfm_index[c] = b;
		}
		return;
	}
	unsigned char c0 = 0;
	unsigned char c1 = 255;
	vector<unsigned char> s0,s1;
	s0.push_back(c0);
	Bin b0 = gen_bin(s0,1);
	s1.push_back(c1);
	Bin b1 = gen_bin(s1,1);
	gen_hfm_index(left_son_node(top),add_bin(b,b0));
	gen_hfm_index(left_son_node(top),add_bin(b,b1));
};

Bin Huffman::gencode(){
	Bin b;
	b.num = 0;
	unsigned char c = 0;
	b.con.push_back(c);
	b.num += 8;
	c = Hfm_index.size();
	b.con.push_back(c);
	b.num += 8;
	for(map<unsigned char, Bin>::iterator it = Hfm_index.begin(); it != Hfm_index.end(); it++){
		c = it->first;
		b.num += 8;
		b = add_bin(b, it->second);
	}
	cout << "gen_code:" << b << endl; ////
	return b;
}

int Huffman::loadcode(Bin & bin){
	Hfm_tree.clear();
	int rest = bin.con[0];
	int num = bin.con[1];
	int pointer = 16;
	bin.num -= rest;
	if(num == 0 && bin.num > 256 * 8) num = 256;
	for(int i = 0; i < num; i++){
		unsigned char c;
		Bin btmp;
		int len;
		btmp = read_bin(bin,pointer,8);
		c = btmp.con[0];
		pointer += 8;
		btmp = read_bin(bin,pointer,8);
		len = btmp.con[0];
		pointer += 8;
		btmp = read_bin(bin,pointer,len);
		Hfm_index[c] = btmp;
		pointer += len;
	}
	return pointer;
}

vector<unsigned char> Huffman::decode_content(const Bin & bin, int pointer){
	vector<unsigned char> output;
	while(pointer < bin.num){
		int read_len = 1;
		unsigned char c;
		while(true){
			Bin tmp_bin = read_bin(bin,pointer,read_len);
			if(Hfm_decode.count(tmp_bin)){
				c = Hfm_decode[tmp_bin];
				break;
			}
			read_len++;
			if(pointer + read_len >= bin.num) break;
		}
		output.push_back(c);
		pointer += read_len;
	}
	return output;
}

vector<unsigned char> Huffman::encode(const vector<unsigned char> & str){
	Bin bout;
	bout = encode_content(str);
	bout = add_bin(gencode(),bout);
	int rest = (8 - (bout.num % 8)) % 8;
	bout.con[0] = rest;
	int n = bout.num;
 	n /= 8;
  	if(bout.num % 8) n++;
	return bout.con;
}

vector<unsigned char> Huffman::decode(const vector<unsigned char> & str){
	Bin bin;
	for(int i = 0; i < str.size(); i++) bin.con.push_back(str[i]);
	bin.num = str.size() * 8;
	int pointer = loadcode(bin);
	return decode_content(bin, pointer);
}

#endif