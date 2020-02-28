#include"dir.h"
#include<iostream>
#include<cctype>
#include <cstdlib>
#include<cstring>
#include<cstdio>
#include <cstddef>
using namespace std;




DIR::DIR(const int& v,const int& e)
{
        V = v;
        E = e;
        total_edges_weight = 0;
        vector<int> row;
        row.assign(V,-110);//配置一個 row 的大小
        m.assign(V,row);//配置2維
        w.assign(V,0);
        in.assign(V,0);
        out.assign(V,0);
        
        for (int i=0;i<V;++i) 
        {
            node.push_back(i);
        }
        cerr<< "1";

}

void DIR::read(FILE* fpin)
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

void DIR::solve(FILE* fpout)
{
    cerr<< "3-1";
    bool source_state = false;
    bool sink_state = false;
    cerr<< "3-2";
    fprintf(fpout,"            \n");/////core dump?
    cerr<< "3-3";
    while (!node.empty())
    {
        cerr<< "3-4";
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