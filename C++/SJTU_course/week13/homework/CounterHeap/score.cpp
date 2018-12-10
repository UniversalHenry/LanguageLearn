#include "Heap.h"
#include "CounterHeap.h"

int main()
{
    int total_score = 100;
    int heap_score = 0;
    int counterHeap_score = 0;
    vector<int> init_elements = {4, 7, 3, 5, 9, 21, 33, 6, 10, 16};
    vector<int> new_elements = {5, 1, 45};

    // homework 12

    // maxHeap init test
    Heap<greater<int>> maxHeap(init_elements);
    if(maxHeap.size()==10&&maxHeap.top()==33)
    {
        printf("%-24s%s\n","MaxHeap Create", "Pass");
        heap_score+=10;
    }
    else
    {
        printf("%-24s%s\n","MaxHeap Create", "Failed");
    }

    // maxHeap singleInsert test
    maxHeap.insert(21);
    maxHeap.insert(43);
    if(maxHeap.size()==12&&maxHeap.top()==43)
    {
        printf("%-24s%s\n","MaxHeap SingleInsert", "Pass");
        heap_score+=10;
    }
    else
    {
        printf("%-24s%s\n","MaxHeap SingleInsert", "Failed");
    }

    // maxHeap multiInsert test
    maxHeap.insert(new_elements);
    if(maxHeap.size()==15&&maxHeap.top()==45)
    {
        printf("%-24s%s\n","MaxHeap MultiInsert", "Pass");
        heap_score+=10;
    }
    else
    {
        printf("%-24s%s\n","MaxHeap MultiInsert", "Failed");
    }
    
    // maxHeap pop test
    if(maxHeap.pop()==45&&maxHeap.pop()==43&&maxHeap.pop()==33&&maxHeap.size()==12&&maxHeap.top()==21)
    {
        printf("%-24s%s\n","MaxHeap Pop", "Pass");
        heap_score+=10;
    }
    else
    {
        printf("%-24s%s\n","MaxHeap Pop", "Failed");
    }

    // maxHeap erase test
    maxHeap.erase(16);
    if(maxHeap.size()==11&&maxHeap.pop()==21&&maxHeap.pop()==21&&maxHeap.top()==10)
    {
        printf("%-24s%s\n","MaxHeap Erase", "Pass");
        heap_score+=10;
    }
    else
    {
        printf("%-24s%s\n","MaxHeap Erase", "Failed");
    }

    // minHeap init test
    Heap<less<int>> minHeap(init_elements);
    if(minHeap.size()==10&&minHeap.top()==3)
    {
        printf("%-24s%s\n","MinHeap Create", "Pass");
        heap_score+=10;
    }
    else
    {
        printf("%-24s%s\n","MinHeap Create", "Failed");
    }

    // minHeap singleInsert test
    minHeap.insert(21);
    minHeap.insert(2);
    if(minHeap.size()==12&&minHeap.top()==2)
    {
        printf("%-24s%s\n","MinHeap SingleInsert", "Pass");
        heap_score+=10;
    }
    else
    {
        printf("%-24s%s\n","MinHeap SingleInsert", "Failed");
    }

    // minHeap multiInsert test
    minHeap.insert(new_elements);
    if(minHeap.size()==15&&minHeap.top()==1)
    {
        printf("%-24s%s\n","MinHeap MultiInsert", "Pass");
        heap_score+=10;
    }
    else
    {
        printf("%-24s%s\n","MinHeap MultiInsert", "Failed");
    }
    
    // minHeap pop test
    if(minHeap.pop()==1&&minHeap.pop()==2&&minHeap.pop()==3&&minHeap.size()==12&&minHeap.top()==4)
    {
        printf("%-24s%s\n","MinHeap Pop", "Pass");
        heap_score+=10;
    }
    else
    {
        printf("%-24s%s\n","MinHeap Pop", "Failed");
    }

    // minHeap erase test
    minHeap.erase(5);
    if(minHeap.size()==11&&minHeap.pop()==4&&minHeap.pop()==5&&minHeap.top()==6)
    {
        printf("%-24s%s\n","MinHeap Erase", "Pass");
        heap_score+=10;
    }
    else
    {
        printf("%-24s%s\n","MinHeap Erase", "Failed");
    }

    printf("%-24s%d/%d\n","Heap Total Score", heap_score, total_score);

    // homework 13

    // counterHeap02 init test
    CounterHeap counterHeap02(0.2, init_elements);
    if (counterHeap02.size() == 10 && counterHeap02.target() == 4)
    {
        printf("%-30s%s\n","counterHeap02 Create", "Pass");
        counterHeap_score+=20;
    }
    else
    {
        printf("%-30s%s\n","counterHeap02 Create", "Failed");
    }

    // counterHeap02 singleInsert test
    counterHeap02.insert(21);
    counterHeap02.insert(43);
    if(counterHeap02.size()==12&&counterHeap02.target()==5)
    {
        printf("%-30s%s\n","counterHeap02 SingleInsert", "Pass");
        counterHeap_score+=10;
    }
    else
    {
        printf("%-30s%s\n","counterHeap02 SingleInsert", "Failed");
    }

    // counterHeap02 multiInsert test
    counterHeap02.insert(new_elements);
    if(counterHeap02.size()==15&&counterHeap02.target()==4)
    {
        printf("%-30s%s\n","counterHeap02 MultiInsert", "Pass");
        counterHeap_score+=10;
    }
    else
    {
        printf("%-30s%s\n","counterHeap02 MultiInsert", "Failed");
    }

    // counterHeap02 erase test
    counterHeap02.erase(1);
    counterHeap02.erase(3);
    counterHeap02.erase(16);
    counterHeap02.erase(21);
    counterHeap02.erase(43);
    if(counterHeap02.size()==10&&counterHeap02.target()==5)
    {
        printf("%-30s%s\n","counterHeap02 Erase", "Pass");
        counterHeap_score+=10;
    }
    else
    {
        printf("%-30s%s\n","counterHeap02 Erase", "Failed");
    }

    // counterHeap07 init test
    CounterHeap counterHeap07(0.7, init_elements);
    if(counterHeap07.size()==10&&counterHeap07.target()==10)
    {
        printf("%-30s%s\n","counterHeap07 Create", "Pass");
        counterHeap_score+=20;
    }
    else
    {
        printf("%-30s%s\n","counterHeap07 Create", "Failed");
    }

    // counterHeap07 singleInsert test
    counterHeap07.insert(21);
    counterHeap07.insert(2);
    if(counterHeap07.size()==12&&counterHeap07.target()==16)
    {
        printf("%-30s%s\n","counterHeap07 SingleInsert", "Pass");
        counterHeap_score+=10;
    }
    else
    {
        printf("%-30s%s\n","counterHeap07 SingleInsert", "Failed");
    }

    // counterHeap07 multiInsert test
    counterHeap07.insert(new_elements);
    if(counterHeap07.size()==15&&counterHeap07.target()==16)
    {
        printf("%-30s%s\n","counterHeap07 MultiInsert", "Pass");
        counterHeap_score+=10;
    }
    else
    {
        printf("%-30s%s\n","counterHeap07 MultiInsert", "Failed");
    }

    // counterHeap07 erase test
    counterHeap07.erase(16);
    counterHeap07.erase(33);
    counterHeap07.erase(21);
    counterHeap07.erase(21);
    counterHeap07.erase(45);
    if(counterHeap07.size()==10&&counterHeap07.target()==6)
    {
        printf("%-30s%s\n","counterHeap07 Erase", "Pass");
        counterHeap_score+=10;
    }
    else
    {
        printf("%-30s%s\n","counterHeap07 Erase", "Failed");
    }

    printf("%-30s%d/%d\n","CounterHeap Total Score", counterHeap_score, total_score);
    return 0;
}
