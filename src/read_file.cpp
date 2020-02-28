#include "read_file.h"
#include<cctype>
#include<iostream>
using namespace std;
ReadFile::ReadFile() {}
void ReadFile::read_u(FILE* fpin, vector< list< pair<int, int> > >& adjacencyList , const int& E ) 
{
    int start = 0;
    int end = 0;
    int weight = 0;
    for (int i = 1; i <= E; ++i) {
            integer=0;
            state=0;
            minus=false;
        while( (ch=fgetc(fpin)) !=EOF){
            
            if(ch=='\n') 
            {
                if (state==0)
                {
                    // if (start==0) {cerr<<"only one component";}
                }
                else if(state==2)
                {
                    if (minus==true)
                    {weight=-integer;}
                    else 
                    {weight=integer;}
                    minus=false;
                    integer=0;
                    state=0;
                    break;
                }
                else 
                {
                    cerr<<"wrong";
                }
            }
            else if(isdigit(ch)) integer = integer*10 + (ch & 0x0f);
            else if(ch==' ') 
            {
                if (state==0) {start=integer; integer=0;state+=1;}
                else if (state==1){end=integer; integer=0;state+=1;}
                else {cerr<<"state wrong";}       
            }
            else if(ch=='-')
            {
                
                minus=true;
            }
            }
            
        state=0;
        

        // Adding Edge to the undirected graph
        adjacencyList[start].push_back(make_pair(end, -weight));
        adjacencyList[end].push_back(make_pair(start, -weight));
        }
}

void ReadFile::read_d(FILE* fpin, vector< vector<int> >& m ,vector<int>& w, vector<int>& in, vector<int>& out, const int& E)
{
    int start = 0;
    int end = 0;
    int weight = 0;
    for (int i = 1; i <= E; ++i) 
        {
            integer=0;
            state=0;
            minus=false;
            while( (ch=fgetc(fpin)) !=EOF)
            {
            
                if(ch=='\n') 
                {
                    if (state==0)
                    {
                        
                    }
                    else if(state==2)
                    {
                        if (minus==true)
                        {weight=-integer;}
                        else 
                        {weight=integer;}
                        minus=false;
                        integer=0;
                        state=0;
                        break;
                    }
                    else 
                    {
                        cerr<<"wrong";
                    }
                }
                else if(isdigit(ch)) integer = integer*10 + (ch & 0x0f);
                else if(ch==' ')  
                {
                    if (state==0) {start=integer; integer=0;state+=1;}
                    else if (state==1){end=integer; integer=0;state+=1;}
                    else {cerr<<"state wrong";}       
                }
                else if(ch=='-')
                {
                    minus=true;
                }
            }    
        state=0;
        m[start][end]=weight;
        w[start]+=weight;
        w[end]-=weight;
        out[start]+=1;
        in[end]+=1;
        }
}