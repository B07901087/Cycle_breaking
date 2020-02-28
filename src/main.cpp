#include"read_file.h"
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<stdio.h>
#include <vector>
#include <list>

#include <bits/stdc++.h> 

using namespace std;
typedef pair<int,int> P;
//int c = 0;
///////新的

int total_edges_weight = 0;



void solve_dir(vector<int>& w,vector<int>& out,vector<int>& in, list<int>& node, const int& V,FILE* fpout, vector< vector<int> >& m)
{
    bool source_state = false;
    bool sink_state = false;
    
    fprintf(fpout,"            \n");
    
    while (!node.empty())
    {
        list<int>::iterator i; 
        list<int>::iterator it1;
        for (i = node.begin(); i != (node.end()); ++i) 
            {
                
                if (sink_state==true)//有砍sink
                {
                    i=node.begin();
                    sink_state=false;
                }
                
                if( ( out[(*i)]==0 ) && ( in[(*i)]!=0 ) )//sink
                {
                    
                    int thisnode=(*i);
                    for (int j=0; j<V ; ++j) 
                    {
                        if (m[j][thisnode]!=(-110))
                        {
                            w[j]-=m[j][thisnode];
                            out[j]-=1;
                            
                            m[j][thisnode]=(-110);

                        }
                    }
                    
                    w[thisnode]=(-214748364);
                    it1=node.erase(i);
                    in[thisnode]=0;
                    i=it1;
                    i--;
                    sink_state=true;
                    
                }
            }//for
        for (i = node.begin(); i != (node.end()); ++i) 
            {
                
                if (source_state==true)//有砍source
                {
                    i=node.begin();
                    source_state=false;
                }
                if( ( out[(*i)]!=0 ) && ( in[(*i)]==0 ) )//source
                {
                    
                    int thisnode=(*i);
                    for (int j=0; j<V ; ++j) 
                    {
                        if (m[thisnode][j]!=(-110))
                        {
                            w[j]+=m[thisnode][j];
                            in[j]-=1;
                            
                            m[thisnode][j]=(-110);
                            

                        }
                    }
                    
                    out[thisnode]=0;
                    w[thisnode]=(-214748364);
                    it1=node.erase(i);
                    i=it1;
                    i--;
                    source_state=true;
                    
                }
            }
        for (i = node.begin(); i != (node.end()); ++i)
            {    
                if( ( out[(*i)]==0 ) && ( in[(*i)]==0 ) )
                {
                    
                    it1=node.erase(i);
                    i=it1;
                    i--;
                    w[ (*i) ]=(-214748364);

                }
            }
        
                   
                    

            //for source sink
        int max= (-214748364);
        int max_index=(-1);
        for(int k=0; k<V ; ++k)
        {
            if (w[k]>max)
            {
                max=w[k];
                max_index=k;
            }
        }
        
        if (node.empty()) {break;}
        w[max_index]= (-214748364);
        if (max_index==(-1))
        {
            for ( i=node.begin(); i!=node.end(); ++i )
                {cerr<<"the node "<<(*i)<<" is not canceled";}
            exit(-1);
        }
        for (int j=0; j<V ; ++j) //max_index is sink
        {
            if (m[j][max_index]!= (-110))
            {
                
                total_edges_weight+=m[j][max_index];
                char str1 [100];
                sprintf (str1, "%d %d %d\n",j,max_index,m[j][max_index]);
                fputs(str1 ,fpout);

                w[j]-=m[j][max_index];
                out[j]-=1;
                m[j][max_index]=(-110);

            }
        }
        
        for (int z=0; z<V ; ++z) //max_index is source
        {
            if (m[max_index][z]!=(-110))
            {
                
                w[z]+=m[max_index][z];
                in[z]-=1;
                m[max_index][z]=(-110);

            }
        }
        
        for ( i=node.begin(); i!=node.end(); ++i )
        {
            if ( (*i) == max_index )
            {
                it1=node.erase(i);
                i=it1;
                break;   
            }
        }
        
    }//while
    
    fseek(fpout, 0, SEEK_SET);
    fprintf(fpout,"%d",total_edges_weight);
    
}



void Prim(priority_queue<P,vector<P>,greater<P> >& Q , vector<bool>& bool_black, vector<P>& pre, vector< list< pair<int, int> > >& adjacencyList ,FILE* fpout )
{
    
    //initialize at outside
    fprintf(fpout,"            \n");
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
}


int main(int argc, char *argv[]) {

    if (argc!=3) {
        cout <<"wrong number of arguments: "<< argc  << endl;
        return 0;
    }
    ReadFile ReadTool;
    
    FILE* fpin;
    FILE* fpout;
    fpin=fopen(argv[1], "r");
    fpout=fopen(argv[2], "w");
    char  graphtype;
    char buffer[100];
    
    std::ios::sync_with_stdio(false);
    
    fscanf(fpin,"%s",&graphtype);
    
    fscanf(fpin,"%s",&buffer);
   
    const int V=atoi(buffer);
    fscanf(fpin,"%s",&buffer);
    const int E=atoi(buffer);
    
    vector< list< pair<int, int> > > adjacencyList(V);
    int start,end, weight;
    if (graphtype=='u')
    {
        
        ReadTool.read_u(fpin, adjacencyList , E );
        

        priority_queue<P,vector<P>,greater<P> > Q;
        vector<bool> bool_black;
        bool_black.assign(V,false);
        vector<P> pre;
        pre.assign(V,make_pair(-1,1000));
        Prim( Q ,  bool_black,  pre,  adjacencyList,fpout);//
    }
    else if (graphtype == 'd')
    {
        vector< vector<int> > m;
        vector<int> row;
        row.assign(V,-110);//配置一個 row 的大小
        m.assign(V,row);//配置2維
        vector<int> w;w.assign(V,0);
        vector<int> in;in.assign(V,0);
        vector<int> out;out.assign(V,0);
        list<int> node;
        for (int i=0;i<V;++i) 
        {
            node.push_back(i);
        }
        ReadTool.read_d(fpin,  m , w,  in,  out,  E);          
        solve_dir(w,out,in,node,V,fpout,m);
    }
    else
    {cerr<<"unvalid graph type";}
    
    // cerr<<total_edges_weight;
    fclose(fpin);
    fclose(fpout);
    
    
    
    
    return 0;



}