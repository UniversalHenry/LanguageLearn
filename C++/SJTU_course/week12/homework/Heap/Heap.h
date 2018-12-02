/*
 * File Heap.h
 * -----------
 * You should finish your homework in this file
 */

#ifndef _heap_h
#define _heap_h

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>

using namespace std;

/*
 * Class Heap
 * ----------
 * This is the class you should implement.
 * It is a template class, Compare can be greater<int>, less<int> and so on.
 * When you define a Heap like Heap<greater<int>>, it should be a maxHeap (who's top this the max element)
 * When you define a Heap like Heap<less<int>>, it should be a minHeap (who's top this the min element)
 * So, when you want to compare two element while implement the member function, you shoud use the member variable cmp, rather than <,<=,>,>=
 */ 
template<class Compare>
class Heap
{
    private:
      // use elements to store the element
      map<int,vector<int>> elements;
      // use elements_index to store the position of elements
      unordered_multimap<int,pair<int,int>> elements_index;
      
      /*
       * Method: update(int val, int l1, int p1, int l2, int p2)
       * Usage: void update(int val, int l1, int p1, int l2, int p2)
       * ------------------------
       * update the elements index
       */
      void index_update(int val, int l1, int p1, int l2, int p2);

      /*
       * Method: index_erase(int val, int l, int p)
       * Usage: void index_erase(int val, int l, int p)
       * ------------------------
       * erase the elements index
       */
      void index_erase(int val, int l, int p);

      // cmp is a comparer that can help you to compare two element's priority
      // Usage:
      // cmp(element_1, element_2)
      // if element_1's priority is higher than element_2, it will return true, otherwise, return false
      // Example:
      // when you define a Heap like Heap<greater<int>>, it means Compare is greater<int>, and cmp is a instance of greater<int>
      // So, cmp(1,2) and cmp(1,1) will return false and cmp(2,1) will return true
      // when you define a Heap like Heap<less<int>>, it means Compare is less<int>, and cmp is a instance of less<int>
      // So, cmp(2,1) and cmp(1,1) will return false and cmp(1,2) will return true
      // By this way, you can implement minHeap and maxHeap using one class
      Compare cmp;

      // the Top element's index, can make the code more readable
      // It's up to you whether to use it
      // pair<int,int> topIndex = make_pair(0,0);

      // Some help function, can improve the code structure
      // It's up to you whether to use them
      // pair<int,int> getParentIndex(pair<int,int> index);
      // pair<int,int> getLeftIndex(pair<int,int> index);
      // pair<int,int> getRightIndex(pair<int,int> index);
      // bool isInRange(pair<int,int> index);
      // bool isTop(pair<int,int> index);
      // void swap(pair<int,int> index_1, pair<int,int> index_2);
      // pair<int,int> findIndex(int element);
      // void shift_up(pair<int,int> index);
      // void shift_down(pair<int,int> index);

    public:
      /*
       * Constructor: Heap()
       * Usage: Heap<greater<int>> maxHeap
       */
      Heap();

      /*
       * Constructor: Heap(vector<int> init_elements)
       * Usage: Heap<greater<int>> maxHeap(init_elements)
       * ------------------------------------------------
       * You should implement this Method with O(mlog(n)) time complexity (m = init_elements.size(), n = elements.size())
       */
      Heap(vector<int> init_elements);

      /*
       * Destructor: ~Heap()
       * Usage: usually implicit
       */
      ~Heap();

      /*
       * Method: insert(int element)
       * Usage: maxHeap.insert(1)
       * ------------------------
       * Add the new element in to the end of elements and shift_up this element
       * You should implement this Method with O(log(n)) time complexity (n = elements.size())
       */
      void insert(int element);

      /*
       * Method: insert(vector<int> new_elements)
       * Usage: maxHeap.insert(new_elements)
       * ------------------------
       * Add the new element in to the end of elements and shift_up this element one by one
       * You should implement this Method with O(mlog(n)) time complexity (m = new_elements.size(), n = elements.size())
       */
      void insert(vector<int> new_elements);

      /*
       * Method: erase(int element)
       * Usage: maxHeap.erase(1)
       * ------------------------
       * Swap this element with the elements's last element, delete the last element, and shift_down the swapped element
       * You should implement this Method with O(log(n)) time complexity (n = elements.size())
       */
      bool erase(int element);

      /*
       * Method: pop()
       * Usage: maxHeap.pop()
       * ------------------------
       * Swap the top element with the elements's last element, delete and return the last element, and shift_down the swapped element
       * You should implement this Method with O(log(n)) time complexity (n = elements.size())
       */
      int pop();

      /*
       * Method: top()
       * Usage: maxHeap.top()
       * ------------------------
       * return the top element
       * You should implement this Method with O(log(1)) time complexity
       */
      int top();

      /*
       * Method: size()
       * Usage: maxHeap.size()
       * ------------------------
       * return the number of element in the Heap
       * You should implement this Method with O(log(1)) time complexity
       */
      int size();

};

template<class Compare>
Heap<Compare>::Heap()
{
    // you code here
}

template<class Compare>
Heap<Compare>::~Heap()
{
    // you code here
}

template<class Compare>
Heap<Compare>::Heap(vector<int> init_elements)
{
    // you code here
    for(int i = 0; i < init_elements.size(); i++){
        insert(init_elements[i]);
    }
}

template<class Compare>
void Heap<Compare>::insert(int element)
{
    // you code here
    int level = 0;
    int p = 0;
    if(elements.empty()){
        vector<int> element_ = {element};
        elements[0] = element_;
    }
    else{
        auto it = --elements.end();
        level = it->first;
        p = it->second.size();
        if(p == (1 << level)){
            vector<int> element_ = {element};
            elements[++level] = element_;
            p = 0;
        }
        else{
            it->second.push_back(element);
        }
    }
    int l_r = level;
    int p_r = p;
    elements_index.insert(make_pair(element,make_pair(level,p)));
    for(auto it = --elements.end(); it != elements.begin(); it--){
        int p_ = p >> 1;
        auto it_ = it;
        it_--;
        if(cmp(it->second[p],it_->second[p_])){
            index_update(it_->second[p_], it_->first, p_, level, p);
            swap(it->second[p],it_->second[p_]);
            level = it_->first;
            p = p_;
        }
        else break;
    }
    index_update(element,l_r,p_r,level,p);
}

template<class Compare>
void Heap<Compare>::insert(vector<int> new_elements)
{
    // you code here
    for(int i = 0; i < new_elements.size(); i++){
        insert(new_elements[i]);
    }
}

template<class Compare>
bool Heap<Compare>::erase(int element)
{
    // you code here
    for(auto tmp = elements.begin(); tmp != elements.end(); tmp++){
        cout << tmp->first << ": ";
        if(!tmp->second.empty())
            for(int t = 0; t < tmp->second.size(); t++){
                cout << tmp->second[t] << " ";
        }
        cout << endl;
    } ////
    cout << endl;

    for(auto tmp = elements_index.begin(); tmp != elements_index.end(); tmp++){
        cout << tmp->first << ":\t" << tmp->second.first << "\t" << tmp->second.second << endl; 
    } ////
    cout << endl;

    if(elements.empty()) return false;
    // int val = *(--(--elements.end())->second.end());
    // (--elements.end())->second.erase((--(--elements.end())->second.end()));
    // if(((--elements.end())->second).size() == 0) elements.erase(--elements.end());
    // int l = elements_index[element].first;
    // int p = elements_index[element].second;
    // elements_index.erase(element);
    // elements_index[val] = make_pair(l,p);
    // auto it = elements.find(l);
    // if(elements.count(l - 1) && cmp(val, elements[l - 1][p >> 1])){
    //     int level = l;
    //     for(; it != elements.begin(); it--){
    //         int p_ = p >> 1;
    //         auto it_ = it;
    //         it_--;
    //         level = it->first;
    //         if(cmp(it->second[p],it_->second[p_])){
    //             elements_index[it_->second[p_]] = make_pair(level, p);
    //             swap(it->second[p],it_->second[p_]);
    //         }
    //         else break;
    //         p = p_;
    //     }
    //     elements_index[val] = make_pair(level, p);
    // }
    // else if(elements.count(l + 1)){
    //     int level = l;
    //     for(; it != elements.end(); it++){
    //         int p_ = p << 1;
    //         auto it_ = it;
    //         it_++;
    //         if(it_ == elements.end()) break;
    //         level = it->first;
    //         if(cmp(it->second[p],it_->second[p_])){
    //             elements_index[it_->second[p_]] = make_pair(level, p);
    //             swap(it->second[p],it_->second[p_]);
    //             p = p_;
    //         }
    //         else if(cmp(it->second[p],it_->second[++p_])){
    //             elements_index[it_->second[p_]] = make_pair(level, p);
    //             swap(it->second[p],it_->second[p_]);
    //             p = p_;
    //         }
    //         else break;
    //     }
    //     elements_index[val] = make_pair(level, p);
    // }
}

template<class Compare>
int Heap<Compare>::pop()
{
    // you code here
    if(elements.empty()) return 0;
    int val = elements.begin()->second[0];
    auto last = --elements.end();
    int p = (last->second.size()) - 1;
    index_erase(val,0,0);
    elements.begin()->second[0] = last->second[p];
    index_update(last->second[p],last->first,p,0,0);
    last->second.erase(--(last->second.end()));
    if(p == 0) elements.erase(last);
    p = 0;
    for(auto it = elements.begin(); it != elements.end(); it++){
        auto it_ = it;
        it_++;
        int p_ = p << 1;
        if(it_ == elements.end() || it_->second.size() < p_ + 1){
            index_update(it->second[p],0,0,it->first,p);
            break;
        }
        if(it_->second.size() == p_ + 1 || cmp(it_->second[p_], it_->second[p_ + 1])){
            if(cmp(it_->second[p_], it->second[p])){
                index_update(it_->second[p_],it_->first, p_,it->first, p);
                swap(it_->second[p_], it->second[p]);
                p = p_;
            }
            else{
                index_update(it->second[p],0,0,it->first,p);
                break;
            }
        }else{
            p_++;
            if(cmp(it_->second[p_], it->second[p])){
                index_update(it_->second[p_],it_->first, p_,it->first, p);
                swap(it_->second[p_], it->second[p]);
                p = p_;
            }
            else{
                index_update(it->second[p],0,0,it->first,p);
                break;
            }
        }
    }
    return val;
}

template<class Compare>
int Heap<Compare>::top()
{
    // you code here
    if(elements.empty()) return 0;
    return elements.begin()->second[0];
}

template<class Compare>
int Heap<Compare>::size()
{
    // you code here
    if(elements.empty())return 0;
    auto it = --elements.end();
    return ((1 << it->first) - 1 + it->second.size());
}

template<class Compare>
void Heap<Compare>::index_update(int val, int l1, int p1, int l2, int p2){
    bool flag = true;
    auto it = elements_index.find(val);
    while(it != elements_index.end() && it->first == val){
        if(it->second.first == l1 && it->second.second == p1){
            it->second.first = l2;
            it->second.second = p2;
            flag = false;
        }
        it++;
    }
    if(flag) cout << "update wrong" << endl;
}

template<class Compare>
void Heap<Compare>::index_erase(int val, int l, int p){
    bool flag = true;
    auto it = elements_index.find(val);
    while(it != elements_index.end() && it->first == val){
        if(it->second.first == l && it->second.second == p){
            elements_index.erase(it);
            flag = false;
        }
        it++;
    }
    if(flag) cout << "erase wrong" << endl;
}


#endif
