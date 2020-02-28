#include"dir.h"
#include"udir.h"
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<stdio.h>
#include <vector>
#include <list>

#include <bits/stdc++.h> 

using namespace std;







int main(int argc, char *argv[]) {

    if (argc!=3) {
        cout <<"wrong number of arguments: "<< argc  << endl;
        return 0;
    }
    
    
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
    
    
    
    if (graphtype=='u')
    {
        UDIR udir(V,E);
        udir.read(fpin);
        udir.solve(fpout);//
    }
    else if (graphtype == 'd')
    {
        DIR dir(V,E);
        dir.read(fpin);          
        dir.solve(fpout);
    }
    else
    {cerr<<"unvalid graph type";}
    
    // cerr<<total_edges_weight;
    fclose(fpin);
    fclose(fpout);
    
    
    
    
    return 0;



}