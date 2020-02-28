#include "udir.h"
#include<cctype>
#include<iostream>
#include<cstring>
#include<stdio.h>
#include<cstdlib>
#include<cstdio>
#include <cstddef>
#include <bits/stdc++.h> 
using namespace std;


UDIR::UDIR(const int& v,const int& e)
{
    total_edges_weight = 0;
    V = v;
    E = e;
    
    bool_black.assign(V,false);
    pre.assign(V,make_pair(-1,1000));
    vector< list< pair<int, int> > > a(V);
    adjacencyList = a;
}
void UDIR::read(FILE* fpin ) 
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
        
        UDIR::adjacencyList[start].push_back(make_pair(end, -weight));
        UDIR::adjacencyList[end].push_back(make_pair(start, -weight));
        
        }
    
}

void UDIR::solve( FILE* fpout )
{
    if (fpout == NULL)
    cerr << "no file write";
    if (fpout == nullptr)
    cerr << "no file write";
    //initialize at outside
    cerr<< "輸出前" ;
    
    fputc('\n', fpout);///why 一碰到output函數就爆
    cerr << "輸出後";
    fputc('\n', fpout);///why?
    
    Q.push(make_pair(0,0));
    while(!Q.empty())
    {
        
        P u = Q.top();
        
        Q.pop();
        if (bool_black[u.second]==true)
        {
            continue;
        }
        else
        {
            bool_black[u.second] = true;
            //can do MST here

            list< pair<int, int> >::iterator itr = adjacencyList[u.second].begin();
            while (itr != adjacencyList[u.second].end()) 
            {
                
                if ( bool_black[ (*itr).first] == true )
                {
                    //cout<<"連到black node"<<endl;
                    ++itr;
                    continue;
                }
                else
                {
                    if (pre[(*itr).first].second >= (*itr).second )//weight<=key
                    {
                        
                        if ( pre[(*itr).first].first!= -1)//old edge eliminated and add to answer if the edge exists
                        {
                            
                            char str1 [100];
                            sprintf (str1, "%d %d %d\n", pre[(*itr).first].first , (*itr).first , -pre[(*itr).first].second );
                            fputs(str1 ,fpout);
                            
                            total_edges_weight +=(-pre[(*itr).first].second) ;
                        }

                        pre[(*itr).first].first=u.second;//node_pi=u
                        pre[(*itr).first].second=(*itr).second;//node_key=weight
                        Q.push(make_pair((*itr).second,(*itr).first));
                        
                    }
                    else//weight > key
                    {
                       
                        char str1 [100];
                        sprintf (str1, "%d %d %d\n", u.second , (*itr).first , -(*itr).second );
                        fputs(str1 ,fpout);
                        total_edges_weight += (-(*itr).second);
                    }
                }
                
                ++itr;
            }
        }
    }
    //Q ended(empty)
    
    
    fseek(fpout, 0, SEEK_SET);
    fprintf(fpout,"%d",total_edges_weight);

    cerr << "3";
}