#include <iostream>
#include "alg/alg.h"
#include "structure/Graph.h"
#include <unordered_set>
#include <map>
#include <bitset>
#include <fstream>
#include <chrono>

using namespace std;

int main() {

//    string query_path = "../test/demo1";
//    string query_path = "../test/demo2";
    string query_path = "../test/data";
//    string query_path = "../test/query";
    string data_path = "../test/data";
//    string query_path = "../test/y_1.graph";
//    string data_path ="../test/yeast.graph";

    auto* query = new Graph();
    query->read_graph(query_path);

    auto* data = new Graph();
    data->read_graph(data_path);

    // 开始计时
    auto startTime = std::chrono::high_resolution_clock::now();

    //query
    unordered_set<int> kernel;
    unordered_map<int,unordered_set<int>> comm;
    set<pair<int,int>> single;
    set<pair<int,int>> special;
    unordered_map<int,unordered_set<int>> others;
    get_info(*query,kernel,comm,single,special,others);

    unordered_set<int> temp;
//    int t = 0;
//    for(auto i: data->nei_label){
//        if(i.count(12)>0 && i.count(36)>0 && (*data).label[t]==13) {
//            temp.insert(t);
//        }
//        ++t;
//    }
    //data
    unordered_map<int,unordered_set<int>> kernel_index;
    unordered_map<int,unordered_map<int,unordered_map<int,unordered_set<int>>>> comm_index;
    unordered_map<int,unordered_map<int,unordered_map<int,unordered_set<int>>>> other_cand;
    pro_nodes(*query,*data,kernel,comm,kernel_index,comm_index,other_cand,others);

    unordered_map<int,unordered_map<int,vector<vector<int>>>> others_table;
    get_others_table(other_cand,others_table,(*query).count_v);

    unordered_map<unsigned_key, set<vector<int>>> index;
    init_index(query->count_v,comm_index,index,others_table);
    init_index_special(query->count_v,kernel_index,special,index,*data,others_table);

    vector<pair<unsigned_key,unsigned_key>> match_order;
    init_match_order(index,match_order);

    //test
    vector<vector<int>> count_1(match_order.size());
    vector<pair<bitset<13>,bitset<13>>> bits;
    bits.reserve(match_order.size());
    for(auto i: match_order){
        bits.emplace_back(bitset<13 > (i.first),bitset<13 > (i.second));
    }

    //join and check
    part_join(index,match_order);
    special_check(index,special,*data);

    // 结束计时
    auto endTime = std::chrono::high_resolution_clock::now();
    // 计算运行时间
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);

    //out
    ofstream out("../output.txt");
    if(out.is_open()){
        out<< "程序运行时间：" << duration.count() << " 毫秒" << std::endl;
        out<<"match count: "<<index.begin()->second.size()<<endl;
        for(const auto& vec: index.begin()->second){
            for(auto i: vec){
                out<<i<<" ";
            }
            out<<endl;
        }
        out.close();
    }else{
        cerr<<"unable to open the file"<<endl;
    }

    return 0;

}
