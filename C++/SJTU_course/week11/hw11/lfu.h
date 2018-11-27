#include <unordered_map>
#include <list>

using namespace std;

class LFUCache {
public:
    LFUCache(int capacity) {
        // TODO: your code here
        cap = capacity;
    }
    
    int get(int key) {
        // TODO: your code here
        if (cache.find(key) == cache.end()) return -1;
        freq[cache[key].second].erase(iter[key]);
        ++cache[key].second;
        freq[cache[key].second].push_back(key);
        iter[key] = --freq[cache[key].second].end();
        if (freq[minFreq].size() == 0) ++minFreq;
        return cache[key].first;
    }
    
    void put(int key, int value) {
        // TODO: your code here
        if (cap <= 0) return;
        if (get(key) != -1) {
            cache[key].first = value;
            return;
        }
        if (cache.size() >= cap) {
            cache.erase(freq[minFreq].front());
            iter.erase(freq[minFreq].front());
            freq[minFreq].pop_front();
        }
        cache[key] = {value, 1};
        freq[1].push_back(key);
        iter[key] = --freq[1].end();
        minFreq = 1;
    }

private:
    int cap, minFreq;
    unordered_map<int, pair<int, int>> cache;
    unordered_map<int, list<int>> freq;
    unordered_map<int, list<int>::iterator> iter;
};
