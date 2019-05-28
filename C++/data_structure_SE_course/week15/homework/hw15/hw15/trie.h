#include <string>
#include <set>

using namespace std;

class Trie
{
  private:
    set<string> inputs;

  public:
    Trie()
    {
        // TODO: Your code here.
        inputs.clear();
    }

    void insert(string word)
    {
        // TODO: Your code here.
        inputs.insert(word);
    }

    bool search(string word)
    {
        // TODO: Your code here.
        if(inputs.count(word)) return true;
        return false;
    }
};
