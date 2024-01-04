//
// Created by DELL on 2024/1/3.
//

#include "alg.h"
#include "../structure/Graph.h"
#include <iostream>
#include <queue>
#include <set>
#include <map>
#include <unordered_set>
#include <algorithm>

using namespace std;
void init_query(Graph &graph){

    return ;
}

struct cmps {
    bool operator()(int n1,int n2) {
        return n1>n2;
    }
};

void get_info(Graph &graph,unordered_set<int> &kernel,map<int,unordered_set<int>> &comm, set<pair<int,int>> &single){
    map<int,int> mm;
    vector<int> temp_comm;
    for(int i = 0;i<graph.count_v;++i){
        mm[i] = graph.degree[i];
    }
    //inti kernel
    while(!mm.empty()){
       int max_degree_id = 0;
       for(auto i : mm){
           if(i.second> mm[max_degree_id]){
               max_degree_id = i.first;
           }
       }
       if(mm[max_degree_id] <= 1) break;
       mm.erase(max_degree_id);
       kernel.insert(max_degree_id);
       for(auto i: graph.adj[max_degree_id]){
           if(mm.count(i)<=0) continue;
           if(--mm[i]<=0){
               mm.erase(i);
               temp_comm.push_back(i);
           }
       }
    }
    // single check
    if(!mm.empty()){
        for(auto i: mm){
            vector<int> count;
            for(auto nei: graph.adj[i.first]){
                if(kernel.count(nei)>0){
                    count.push_back(nei);
                }
            }
            if(count.size()>1) {
                comm.insert(pair<int,unordered_set<int>>(i.first,unordered_set<int>(count.begin(),count.end())));
            }else{
                for(auto t: mm){
                    if(graph.adj[i.first].count(t.first)>0){
                        if(single.count({t.first,i.first})==0){
                            single.insert(pair<int,int>(i.first,t.first));
                        }
                    }
                }

            }
        }
    }
    //init comm
    for(auto i: temp_comm){
        vector<int> count;
        for(auto nei : graph.adj[i]){
            if(kernel.count(nei)>0){
                count.push_back(nei);
            }
        }
        if(count.size()>1){
            comm.insert(pair<int,unordered_set<int>>(i,unordered_set<int>(count.begin(),count.end())));
        }
    }
    //twice single check
    ///for kernel
    for(auto i: kernel){
        for(auto nei: graph.adj[i]){
            if(kernel.count(nei)>0){
                if(single.count({nei,i})==0){
                    single.insert(pair<int,int>(i,nei));
                }

            }
        }
    }
    ///for comm
    for(auto i: comm){
        for(auto nei: graph.adj[i.first]){
            if(comm.count(nei)>0){
                if(single.count({nei,i.first})==0){
                    single.insert(pair<int,int>(i.first,nei));
                }

            }
        }
    }
    //dedupe single



}

void printGraph(Graph &graph){
    cout<<"label"<<endl;
    for(auto i: graph.label){
        cout<<i<<" ";
    }
    cout<<endl;
    cout<<"degree"<<endl;
    for(auto i : graph.degree){
        cout<<i<<" ";
    }
    cout<<endl;
    cout<<"adj"<<endl;
    for(int i = 0;i< graph.adj.size(); ++i ){
        cout<<i<<": ";
        for(auto j : graph.adj[i]){
            cout<<j<<" ";
        }
        cout<<endl;
    }
}