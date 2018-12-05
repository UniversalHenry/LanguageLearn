#ifndef _HUFFMAN_H_
#define _HUFFMAN_H_
#include <queue>
#include <vector>
#include <iostream>
#include <map>
#include <fstream>
using namespace std;

struct Bin{
	string str = "";
	int num = 0;
};

Bin add_bin(const Bin &b1, const Bin &b2);
Bin gen_bin(const string & str);
Bin gen_bin(const string & str, int i);
Bin read_bin(const Bin &b, int pos, int len);
ostream& operator<<(ostream& out, const Bin& b);
struct cmp
{bool operator()(const pair<int,vector<char> > &n1, const pair<int,vector<char> > &n2) 
{ return (n1.first < n2.first);}
};

class Huffman {
public:
	string encode(const string & str);
	string decode(const string & str);

private:
	map<char,int> Freq;
	priority_queue<pair<int,vector<char> >,vector<pair<int,vector<char> > >, cmp> Freq_index;
	map<int,char> Hfm_tree;
	map<char,int> Hfm_index;

	int right_son_node(int i);
	int left_son_node(int i);
	void combine(pair<int,vector<char> > &n1,pair<int,vector<char> > &n2);

	int bin_decode(const Bin &bin);
	Bin bin_encode(int i);

	Bin gencode(int rest);
	Bin encode_content(const string & str);
	int loadcode(Bin & bin);
	string decode_content(const Bin & bin, int pointer);
};

Bin add_bin(const Bin &b1, const Bin &b2){
	Bin b;
	b.num = b1.num + b2.num;
	int l = b1.num % 8;
	if(l == 0)	{
		b.str = b1.str + b2.str;
	}else{
		int r = 8 - l;
		int k = r;
		l = 1 << l;
		r = 1 << r;
		b.str = b1.str.substr(0,b1.num / 8);
		char c = (int(b1.str[b1.num / 8]) + 256) % 256 / r * r +
			(int(b2.str[0]) + 256) % 256 / l;
		b.str += c;
		while(k < b2.num){
			c = (int(b2.str[k / 8]) + 256) % 256 * r % 256 +
			 	(int(b2.str[k / 8 + 1])+ 256 ) % 256 / l;
			b.str += c;
			k += 8;
		}
	}
	b.str = b.str.substr(0, b.num / 8 + 2);
	return b;
}

Bin gen_bin(const string & str){
	Bin b;
	b.str = str;
	b.num = str.size() * sizeof(char);
	return b;
}

Bin gen_bin(const string & str, int i){
	Bin b;
	b.num = i;
	b.str = str;
	return b;
}

Bin read_bin(const Bin &bin, int pos, int len){
	Bin b;
	b.num = len;
	int l = pos % 8;
	if(l == 0){
		b.str = bin.str.substr(pos / 8, len / 8 + 1);
	}else{
		Bin tmpb1, tmpb2;
		tmpb1.num = 8 - l;
		tmpb1.str = "x";
		tmpb2.num = len + l;
		tmpb2.str = bin.str.substr(pos / 8, len / 8 + 1);
		b = add_bin(tmpb1,tmpb2);
		b.num = len;
		b.str = b.str.substr(1);
	}
	return b;
}

ostream& operator<<(ostream & out, const Bin & b){
	for(int i = 0; i < b.num; i++){
		char c = (1 << (7 - (i % 8))) % 256;
		if(b.str[i / 8] & c) out << "1";
		else out << "0";
	}
	return out;
}

int Huffman::right_son_node(int i){
	int l = (i >> 8) + 1;
	int p = (i % 256) << 1;
	return ((l << 8) + p + 1);
}

int Huffman::left_son_node(int i){
	int l = (i >> 8) + 1;
	int p = (i % 256) << 1;
	return ((l << 8) + p);
}

int Huffman::bin_decode(const Bin &bin){
	int l = bin.num - 1;
	int p = bin.str[0];
	int index = (l << 8) + p;
	return index;
}

Bin Huffman::bin_encode(int i){
	Bin b;
	b.num = i >> 8 + 1;
	char c = i % 256;
	b.str += c;
	return b;
}

void Huffman::combine(pair<int,vector<char> > &n1,pair<int,vector<char> > &n2){
	for(int i = 0; i < n1.second.size(); i++){
		if(Hfm_index.count(n1.second[i])) Hfm_index[n1.second[i]] = left_son_node(Hfm_index[n1.second[i]]);
		else Hfm_index[n1.second[i]] = 0;
	}
	for(int i = 0; i < n2.second.size(); i++){
		if(Hfm_index.count(n2.second[i])) Hfm_index[n2.second[i]] = right_son_node(Hfm_index[n2.second[i]]);
		else Hfm_index[n2.second[i]] = 0;
	}
	n1.first += n2.first;
	n1.second.insert(n1.second.end(),n2.second.begin(),n2.second.end());
	Freq_index.push(n1);
}

Bin Huffman::encode_content(const string & str){
	Hfm_index.clear();
	for(int i = 0; i < str.size(); i++){
		if(Freq.count(str[i])){
			Freq[str[i]]++;
		}else{
			Freq[str[i]] = 0;
		}
	}
	map<char, int>::iterator  it = Freq.begin();
	while(it != Freq.end()){
		vector<char> ch;
		ch.push_back(it->first);
		Freq_index.push(make_pair(it->second,ch));
		it++;
	}
	while(Freq_index.size() > 1){
		pair<int,vector<char> > n1 = Freq_index.top();
		Freq_index.pop();
		pair<int,vector<char> > n2 = Freq_index.top();
		Freq_index.pop();
		if(n1.first < n2.first) combine(n1,n2);
		else combine(n2,n1);
	}
	Bin bout;
	for(int i = 0; i < str.size(); i++){
		bout = add_bin(bout,bin_encode(Hfm_index[str[i]]));
	}
	return bout;
}

Bin Huffman::gencode(int rest){
	Bin b;
	b.num = (3 * Hfm_index.size() + 2) * 8;
	char c = rest;
	b.str += c;
	c = Hfm_index.size();
	b.str += c;
	for(map<char, int>::iterator it = Hfm_index.begin(); it != Hfm_index.end(); it++){
		c = it->first;
		b.str += c;
		c = it->second >> 8;
		b.str += c;
		c = it->second % 256;
	}
	return b;
}

int Huffman::loadcode(Bin & bin){
	Hfm_tree.clear();
	int rest = bin.str[0];
	int num = bin.str[1];
	int pointer = (num * 3 + 2) * 8;
	bin.num -= rest;
	for(int i = 0; i < num; i++){
		char c = bin.str[i * 3 + 1];
		int l = bin.str[i * 3 + 2];
		int p = bin.str[i * 3 + 3];
		Hfm_tree[(l << 8) + p] = c;
	}
	return pointer;
}

string Huffman::decode_content(const Bin & bin, int pointer){
	string output;
	while(pointer < bin.num){
		int read_len = 1;
		char c;
		while(true){
			Bin tmp_bin = read_bin(bin,pointer,read_len);
			int index = bin_decode(tmp_bin);
			if(Hfm_tree.count(index)){
				c = Hfm_tree[index];
				break;
			}
			read_len++;
			if(pointer + read_len >= bin.num) break;
		}
		output += c;
		pointer += read_len;
	}
	return output;
}

string Huffman::encode(const string & str){
	Bin bout;
	bout = encode_content(str);
	int rest = (8 - (bout.num % 8)) % 8;
	bout = add_bin(gencode(rest),bout);
	int n = bout.num;
 	n /= 8;
  	if(bout.num % 8) n++;
	return bout.str;
}

string Huffman::decode(const string & str){
	Bin bin;
	bin.str = str;
	bin.num = str.size() * 8;
	int pointer = loadcode(bin);
	return decode_content(bin, pointer);
}

#endif