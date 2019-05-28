#include <iostream>
#include <sstream>
#include <iterator>
#include <vector>
#include <set>
#include <map>
#include <queue>
 
//------------------------------------------------------------------------------
using namespace std;
 
//------------------------------------------------------------------------------
struct node
{
    int val;
    unsigned char neighbors;
};
//------------------------------------------------------------------------------
class Solver
{
private:
    //member variables
    vector<vector<int> > data;
    vector<vector<int> > ans_data;
    map<int,pair<int,int> > known_val;
    queue<pair<int, vector<vector<int> > > > bfs_all;
    void readin_puzzle(vector<string>& puzz, int max_wid);
    bool is_valid_point(pair<int,int>,int);
    void go_next_point(int,pair<int,int>,vector<vector<int> >,
        queue<pair<pair<int,int>, vector<vector<int> > > > & bfs);
    bool go_next_node(int,pair<int,int>,vector<vector<int> >);
    void convert_to_ans(vector<string>&);
    //member functions
public:
    //constructors & deconstructors
    Solver()
    {

    }
 
    //member functions
    bool solve( vector<string>& puzz, int max_wid )
    {
        readin_puzzle(puzz,max_wid);
        auto node = known_val.begin();
        if(!go_next_node(node->first,node->second,data))return false;
        while(node != known_val.end()){
            // cout << node->first << endl; //***
            
            auto status = bfs_all.front();
            // cout << node->first << endl; //***
            if(status.first == (--known_val.end())->first)break;
            while(status.first <= node->first){
                status = bfs_all.front();
                bfs_all.pop();
                if(!go_next_node(node->first,node->second,status.second)) break;
            }
            node++;
        }
        if(bfs_all.empty()) return false;
        while(bfs_all.size() > 1) bfs_all.pop();
        ans_data = bfs_all.front().second;
        convert_to_ans(puzz);
        return true;
    }
};

struct puzzle
{
    int width;
    vector<string> data;
};

void printPuzzle(puzzle p)
{
    int c = 0;
    for( vector<string>::iterator i = p.data.begin(); i != p.data.end(); i++ )
    {
        if( ( *i ) != "*" && ( *i ) != "." )
        {
            if( atoi( ( *i ).c_str() ) < 10 ) cout << "0";
            cout << ( *i ) << " ";
        }
        else 
            cout << "   ";
        if( ++c >= p.width ) 
        { 
            cout << endl; c = 0; 
        }
    }
    cout << endl << endl;

}
//------------------------------------------------------------------------------
int main( int argc, char* argv[] )
{
    struct puzzle puzzles[3];

    istringstream iss1( "32 . . . 37 * * * . 34 . . 38 * * * . 25 . . 12 . * * 29 . 20 . 40 . * * . 28 . 19 . 10 1 * * * 15 . . . . * * * * * . . . 3 * * * * * * . 4" ); 
    copy( istream_iterator<string>( iss1 ), istream_iterator<string>(), back_inserter<vector<string> >( puzzles[0].data ) );
    puzzles[0].width = 8;

    istringstream iss2(". 53 . 59 . 67 66 . . 52 . . 57 . . 68 72 . . . 56 . 64 * * * * 49 . . . * * 17 . * . 10 . * . 16 . . 22 . 46 . * . 2 . . 24 . 44 . . 4 1 . . 25 . . 7 6 . 34 . . 31 42 40 . . . . . 29 .");
    copy( istream_iterator<string>( iss2 ), istream_iterator<string>(), back_inserter<vector<string> >( puzzles[1].data ) );
    puzzles[1].width = 9;
    
    istringstream iss3("56 . . . . 62 . . 67 . 55 . 53 . . 65 . . 9 . 52 . . 48 . . 69 . 6 . * * * 47 . . 5 . . * * * 72 . 42 . . 13 * * * . . 41 . 3 . 18 . . 38 . . 2 . . 22 23 . . . 32 1 20 . . 25 . 35 . .");
    copy( istream_iterator<string>( iss3 ), istream_iterator<string>(), back_inserter<vector<string> >( puzzles[2].data ) );
    puzzles[2].width = 9;

    int puzzleIndex = 0;

    if(argc > 1)
    {
        puzzleIndex = atoi(argv[1]);
    }

    cout<<"The original puzzle:"<<endl;

    printPuzzle(puzzles[puzzleIndex]);

    Solver s; 
    bool bFound = s.solve( puzzles[puzzleIndex].data, puzzles[puzzleIndex].width );
 
    if(bFound)
    {
        cout<<"The answer: "<<endl;
        printPuzzle(puzzles[puzzleIndex]);
    }
    else
    {
        cout<<"No answer."<<endl;
    }
    system("pause");
    return 1;
}

void Solver::readin_puzzle(vector<string>& puzz, int max_wid){
    for(int i = 0; i < max_wid; i++){
        vector<int> tmp;
        for(int j = 0; j < max_wid; j++){
            tmp.push_back(-1);
        }
        data.push_back(tmp);
    }
    int c = 0;
    int r = 0;
    for( vector<string>::iterator i = puzz.begin(); i != puzz.end(); i++ )
    {
        if( ( *i ) != "*" && ( *i ) != "." )
        {
            int val = atoi( ( *i ).c_str() );
            data[r][c] = val;
            known_val.insert(make_pair(val,make_pair(r,c)));
        }
        else if((*i) == "."){
            data[r][c] = 0;
        }
        if( ++c >= max_wid ) 
        { 
            r++; c = 0; 
        }
        if(r >= max_wid) break;
    }
}

bool Solver::is_valid_point(pair<int,int> p ,int m){
    return (p.first > -1 && p.second > -1) && (p.first < m && p.second < m);
}

void Solver::go_next_point(int node,pair<int,int> pos,vector<vector<int> > dt,
    queue<pair<pair<int,int>, vector<vector<int> > > > & bfs){
        // cout << node << endl; //***
    int nxt_node = node + 1;
    for(int r = -1; r < 2; r++)
        for(int c = -1; c < 2; c++){
            if(c == 0 && r == 0) continue;
            auto nxt_pos = pos;
            nxt_pos.first += r;
            nxt_pos.second += c;
            if(is_valid_point(nxt_pos,dt.size()) && 
                (dt[nxt_pos.first][nxt_pos.second] == 0 ||
                dt[nxt_pos.first][nxt_pos.second] == nxt_node)){
                    // cout << node << endl; //***
                    auto tmp_data = dt;
                    tmp_data[nxt_pos.first][nxt_pos.second] = nxt_node;
                    bfs.push(make_pair(nxt_pos,tmp_data));
                }
            }
}

bool Solver::go_next_node(int node,pair<int,int> pos,vector<vector<int> > dt){
    auto nxt_node = known_val.find(node);
    ++nxt_node;
    if(nxt_node == known_val.end()) return false;
    int step = nxt_node->first - node;
    queue<pair<pair<int,int>, vector<vector<int> > > > local_bfs;
    go_next_point(node,pos,dt,local_bfs);
    for(int i = 1; i < step; i++){
        queue<pair<pair<int,int>, vector<vector<int> > > > tmp_bfs;
        while(!local_bfs.empty()){
            auto status = local_bfs.front();
            local_bfs.pop();
            go_next_point(node + i,status.first,status.second,tmp_bfs);
            // cout << node + i << endl; //***
        }
        local_bfs = tmp_bfs;
    }
    while(!local_bfs.empty()){
        if(nxt_node->first == (--known_val.end())->first)break;  //***
        auto status = local_bfs.front();
        local_bfs.pop();
        if(status.first == nxt_node->second){
            bfs_all.push(make_pair(nxt_node->first,status.second));
        }
    }
    if(nxt_node->first == (--known_val.end())->first) return false;  //***
    return true;
}

void Solver::convert_to_ans(vector<string>& puzz){
    puzz.clear();
    for(int r = 0; r < ans_data.size();r++){
        for(int c = 0; c < ans_data.size();c++){
            stringstream ss;
            string s;
            if(ans_data[r][c] > 0){
                ss << ans_data[r][c];
                ss >> s;
                puzz.push_back(s);
            }
            if(ans_data[r][c] == 0){
                puzz.push_back(".");
            }
            if(ans_data[r][c] == -1){
                puzz.push_back("*");
            }
        }
    }
}