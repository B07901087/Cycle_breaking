#ifndef _READ_FILE_H
#define _READ_FILE_H

#include <fstream>
#include <vector>
#include <list>
#include <utility>
using namespace std;
class ReadFile{

    public:
            ReadFile();
            void read_u(FILE* , vector< list< pair<int, int> > >& , const int& );
            void read_d(FILE* , vector< vector<int> >&  ,vector<int>& , vector<int>& , vector<int>& ,  const int& E);
    private:
            char ch;
            int integer;
            int state;
            bool minus;
            int E;
};

#endif