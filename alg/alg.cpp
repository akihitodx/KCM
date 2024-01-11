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

bool com_Match(multiset<int> &queryNode,multiset<int> &dataNode){
    // dataNode 包含 querNode
    return includes(dataNode.begin(),dataNode.end(),queryNode.begin(),queryNode.end());
}

void pro_nodes(Graph &query,Graph &data,unordered_set<int> &kernel,unordered_map<int,unordered_set<int>> &comm,unordered_map<int,unordered_set<int>> &kernel_index,unordered_map<int,unordered_map<int,unordered_map<int,unordered_set<int>>>> &comm_index){
    //prepro kernel
    unordered_set<int> kernel_set;
    for(int data_id = 0; data_id< data.count_v; ++data_id){
        for(auto kernel_id : kernel){
            if(query.label[kernel_id] == data.label[data_id] && query.degree[kernel_id] <= data.degree[data_id]){
                if(com_Match(query.nei_label[kernel_id],data.nei_label[data_id])){
                    kernel_index[kernel_id].insert(data_id);
                }
            }
        }
    }
    //prepro comm
    //存在效率问题 可优化
    for(int data_id = 0; data_id<data.count_v; ++data_id){
        // com comm的一项 first连通点 second 可连接的核心节点们
        for(auto com: comm){
            if(query.label[com.first] == data.label[data_id] && query.degree[com.first] <= data.degree[data_id]){
                unordered_map<int,unordered_map<int,unordered_set<int>>> temp;
                bool flag = true;
                for(auto n_com: com.second){

                    //n_com 每一个可连接的核心节点
                    for(auto nei: data.adj[data_id]){
                        //数据图节点的每一个邻居
                        if(kernel_index[n_com].count(nei)>0){
                            temp[data_id][n_com].insert(nei);
                        }
                    }
                    if(temp[data_id][n_com].empty()){
                        flag = false;
                        break;
                    }
                }
                if(flag){
                    comm_index[com.first][temp.begin()->first] = temp.begin()->second;
                }
            }
        }
    }

}

//这效率要死了
void init_index(int query_graph_length,unordered_map<int,unordered_map<int,unordered_map<int,unordered_set<int>>>> &comm_index,unordered_map<unsigned_key ,set<vector<int>>> &index){
    //    unordered_set<string> mini_piles;
    //    for(auto com: comm){
    //        for(auto a = com.second.begin(); a != com.second.end(); ++a){
    //            for(auto b = next(a); b!= com.second.end(); ++b){
    //                mini_piles.insert("")
    //            }
    //        }
    //    }
    for(const auto& query_com: comm_index){
        for(auto data_com = query_com.second.begin(); data_com!=query_com.second.end(); ++data_com){
            for(auto a_pair = data_com->second.begin(); a_pair != data_com->second.end(); ++a_pair){
                auto temp_it = a_pair;
                for(auto b_pair = ++temp_it; b_pair != data_com->second.end(); ++b_pair){
                    for(auto i: a_pair->second){
                        for(auto j: b_pair->second){
                            unsigned_key key =  (1<<query_com.first) | (1<<a_pair->first) | (1<<b_pair->first);
                            vector<int> table(query_graph_length,-1);
                            table[a_pair->first] = i;
                            table[b_pair->first] = j;
                            table[query_com.first] = data_com->first;
                            index[key].insert(table);
                        }
                    }
                }
            }
        }
    }
}