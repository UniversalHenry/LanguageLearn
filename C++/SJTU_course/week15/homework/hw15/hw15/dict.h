#include <string>
#include <map>
#include <vector>

using namespace std;

class Dictionary
{
  private:
    multimap<int,string> inputs;

  public:
    Dictionary()
    {
        // TODO: Your code here.
        inputs.clear();
    }

    void insert(string word)
    {
        // TODO: Your code here.
        inputs.insert(make_pair(word.size(),word));
    }

    bool search(string word)
    {
        // TODO: Your code here.
        vector<int> pos;
        for(int i = 0; i < word.size(); i++){
            if(int(word[i]) - int('*') != 0)
                pos.push_back(i);
        }
        for(multimap<int,string>::iterator it = inputs.find(word.size()); it != inputs.end() && it->first == word.size(); it++){
            bool flag = true;
            for(int i = 0; i < pos.size(); i++){
                int n = pos[i];
                if(int(word[n]) - int(it->second[n]) != 0){
                    flag = false;
                    break;
                }
            }
            if(flag == true) return true;
        }
        return false;
    }
};
