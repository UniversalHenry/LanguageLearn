#include <unordered_map>
#include <list>

using namespace std;

class LRUCache
{
  public:
    LRUCache(int capacity)
    {
        // TODO: your code here
        cap = capacity;
    }

    int get(int key) {
        // TODO: your code here
        auto the_cache = cache.find(key);
        if (the_cache == cache.end()) return -1;
        record.push_front(*(the_cache->second));
        record.erase(the_cache->second);
        the_cache->second = record.begin();
        return the_cache->second->second;
    }
    
    void put(int key, int value) {
        // TODO: your code here
        auto the_cache = cache.find(key);
        if (the_cache != cache.end()) record.erase(the_cache->second);
        record.push_front(make_pair(key, value));
        cache[key] = record.begin();
        if (cache.size() > cap) {
            int k = record.rbegin()->first;
            record.pop_back();
            cache.erase(k);
        }
    }

  private:
    int cap;
    list<pair<int,int> > record;
    unordered_map<int,list<pair<int,int> >::iterator> cache;
};
