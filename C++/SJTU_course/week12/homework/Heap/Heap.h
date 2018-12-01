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
      unordered_map<int,pair<int,int>> elements_index;

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
        vector element_ = {element};
        elements[0] = element_;
    }
    else{
        auto it = --elements.end();
        level = it->first;
        p = it->second.size();
        if(p == (1 << level)){
            vector element_ = {element};
            elements[++level] = element_;
            p = 0;
        }
        else{
            it->second.push_back();
        }
    }
    for(auto it = --elements.end(); it != elements.begin(); it--){
        int p_ = p >> 1;
        auto it_ = it;
        it_--;
        level = it->first;
        if(cmp(it->second[p],it_->second[p_])){
            elements_index[it_->second[p_]] = make_pair(level, p);
            swap(it->second[p],it_->second[p_]);
        }
        else break;
        p = p_;
    }
    elements_index[element] = make_pair(level, p);
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
    if(elements.empty()) return false;
    int val = *(--(--elements.end())->second.end());
    (--elements.end())->second.erase((--(--elements.end())->second.end()));
    if(((--elements.end())->second).size() == 0) elements.erase(--elements.end());
    int val = *(--(--elements.end())->second.end());
    int l = elements_index[element]->second.first;
    int p = elements_index[element]->second.second;
    elements_index.erase(element);
    elements_index[val] = make_pair(l,p);
    auto it = elements.find(l);
    if(elements.count(l - 1) && cmp(val, elements[l - 1].second[p >> 1])){
        int level = l;
        for(; it != elements.begin(); it--){
            int p_ = p >> 1;
            auto it_ = it;
            it_--;
            level = it->first;
            if(cmp(it->second[p],it_->second[p_])){
                elements_index[it_->second[p_]] = make_pair(level, p);
                swap(it->second[p],it_->second[p_]);
            }
            else break;
            p = p_;
        }
        elements_index[val] = make_pair(level, p);
    }
    else if(elements.count(l + 1)){
        int level = l;
        for(; it != elements.end(); it++){
            int p_ = p << 1;
            auto it_ = it;
            it_++;
            if(it_ == elements.end()) break;
            level = it->first;
            if(cmp(it->second[p],it_->second[p_])){
                elements_index[it_->second[p_]] = make_pair(level, p);
                swap(it->second[p],it_->second[p_]);
                p = p_;
            }
            else if(cmp(it->second[p],it_->second[++p_])){
                elements_index[it_->second[p_]] = make_pair(level, p);
                swap(it->second[p],it_->second[p_]);
                p = p_;
            }
            else break;
        }
        elements_index[val] = make_pair(level, p);
    }
}

template<class Compare>
int Heap<Compare>::pop()
{
    // you code here
    if(elements.empty()) return NULL;
    int p = --((--elements.end())->second.size());
    elements_index.erase(elements.begin()->second[0]);
    elements.begin()->second[0] = (--elements.end())->second[p];
    (--elements.end())->second.erase(&((--elements.end())->second[p]));
    int level = --((--elements.end())->first);
    if(p == 0) elements.erase(--elements.end());
    vector<int> p_;
    for(int i = 0; i < level; i++){
        p >>= 1;
        p_.push_back(p);
    }
    int l = level;
    for(auto it = elements.begin(); it != elements.end(); it++){
        level--;
        auto it_ = it;
        it_++;
        if(it_ == elements.end()) break;
        elements_index[it_->second[p_[level - 1]]] = make_pair(l - level -1, p_[level]);
        swap(it->second[p_[level]],it_->second[p_[level - 1]]);
    }
    elements_index[it_->second[p_[level - 1]]] = make_pair(l - level, p_[level - 1]);
}

template<class Compare>
int Heap<Compare>::top()
{
    // you code here
    if(elements.empty()) return NULL;
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

#endif
