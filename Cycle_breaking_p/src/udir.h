#ifndef _UDIR_H
#define _UDIR_H

#include <fstream>
#include <vector>
#include <list>
#include <utility>
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> P;
class UDIR{

    public:
            UDIR(  const int& ,  const int&);
            void solve(FILE* );//Prim(FILE* fpout )
            
            void read(FILE* );//read_u(FILE* fpin, vector< list< pair<int, int> > >& adjacencyList , const int& E )
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
            priority_queue<P,vector<P>,greater<P> > Q;
            vector<bool> bool_black;
            vector<P> pre;
            vector< list< pair<int, int> > > adjacencyList;
            int total_edges_weight ;
            
};

#endif