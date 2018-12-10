#include "CounterHeap.h"

CounterHeap::CounterHeap(double percent)
{
    // you code here
    percentage = percent;
}

CounterHeap::CounterHeap(double percent, vector<int> init_elements)
{
    // you code here
    percentage = percent;
    insert(init_elements);
}

CounterHeap::~CounterHeap()
{
    // you code here
}

int CounterHeap::getBreakPoint()
{
    return ceil((minHeap.size() + maxHeap.size()) * percentage);
}

void CounterHeap::insert(int element)
{
    // you code here
    if(element > minHeap.top()) minHeap.insert(element);
    else maxHeap.insert(element);
    if(maxHeap.size() > getBreakPoint()) minHeap.insert(maxHeap.pop());
    else if(maxHeap.size() < getBreakPoint()) maxHeap.insert(minHeap.pop());
}

void CounterHeap::insert(vector<int> new_elements)
{
    // you code here
    for(int i = 0; i < new_elements.size(); i++) insert(new_elements[i]); 
}

bool CounterHeap::erase(int val)
{
    // you code here
    bool flag = true;
    if(maxHeap.top() >= val) flag = maxHeap.erase(val);
    else flag = minHeap.erase(val);
    if(maxHeap.size() > getBreakPoint()) minHeap.insert(maxHeap.pop());
    else if(maxHeap.size() < getBreakPoint()) maxHeap.insert(minHeap.pop());
    return flag;
}

int CounterHeap::target()
{
    // you code here
    if(size() != 0) return maxHeap.top();
    return 0;
}

int CounterHeap::size()
{
    // you code here
    return (maxHeap.size() + minHeap.size());
}