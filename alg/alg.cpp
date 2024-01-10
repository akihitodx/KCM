//
// Created by DELL on 2024/1/3.
//

#include "alg.h"
#include "../structure/Graph.h"
#include <iostream>
#include <queue>
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

void get_info(Graph &graph,unordered_set<int> &kernel,unordered_map<int,unordered_set<int>> &comm, set<pair<int,int>> &single, set<pair<int,int>> &special){
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
                bool flag = false;
                for(auto c: comm){
                    if(c.second.count(i)<=0 || c.second.count(nei)<=0) continue;
                    flag = true;
                    if(single.count({nei,i})==0){
                        single.insert(pair<int,int>(i,nei));
                    }
                    break;
                }
                if(!flag){
                    if(special.count({nei,i})==0){
                        special.insert(pair<int,int>(i,nei));
                    }
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
    ///for single
    set<pair<int,int>> temp_s;
    for(auto i: single){
        if(kernel.count(i.first)>0 && kernel.count(i.second)>0){
            for(auto c: comm){
                if(c.second.count(i.first)<=0 || c.second.count(i.second)<=0) continue;


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

//void pro_nodes(Graph &graph,unordered_set<int> &kernel,unordered_map<int,unordered_set<int>> &comm,unordered_map<int,vector<int>> &kernel_index,unordered_map<int,unordered_map<int,unordered_set<int>>> &comm_index){
//    //prepro kernel nei
//    unordered_map<int,unordered_set >
//    for(auto i: kernel){
//
//    }
//
//}