#ifndef _DIR_H
#define _DIR_H

#include <fstream>
#include <vector>
#include <list>
#include <utility>
using namespace std;
class DIR{

    public:
            DIR( const int& , const int&);
            void solve(FILE* );
            
            void read(FILE* );//ReadTool.read_d(fpin,  m , w,  in,  out,  E);
    private:
            char ch;
            int integer;
            int state;
            bool minus;
            int E;
            int V;
            vector< vector<int> > m;
            vector<int> w;
            vector<int> in;
            vector<int> out;
            list<int> node;
            int total_edges_weight;
            
};

#endif