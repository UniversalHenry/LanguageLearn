#include <cstdlib>
#include <vector>

using namespace std;

class Solution {
public:
    void gameOfLife(vector<vector<int> >& board) {
        if(board.size()==0 || board[0].size()==0) return;
        for(int i = 0; i < board.size(); i++) 
            for(int j = 0; j < board[i].size(); j++) 
                if(will_alive(board, i, j)) board[i][j] += 2;
        for(int i = 0; i < board.size(); i++) 
            for(int j = 0; j < board[i].size(); j++) 
                board[i][j] /= 2;
    }

private:
    bool will_alive(const vector<vector<int> > &board, int r, int c)
    {   
        int count = 0;
        for(int i = -1; i < 2; i++)
            if((r + i) >= 0 && (r + i) < board.size())
                for(int j = -1; j < 2; j++)
                    if((c + j) >= 0 && (c + j) < board[r].size())
                        count += board[r + i][c + j] % 2;
        if(board[r][c] % 2 == 0) return (count == 3);
        else return (count > 2 && count < 5);
    }
};