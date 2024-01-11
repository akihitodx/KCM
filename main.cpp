#include <iostream>
#include "alg/alg.h"
#include "structure/Graph.h"
#include <unordered_set>
#include <map>
using namespace std;

int main() {
//    string query_path = "../test/demo1";
//    string query_path = "../test/demo2";
    string query_path = "../test/query";
    string data_path = "../test/data";

    auto* query = new Graph();
    query->read_graph(query_path);

    auto* data = new Graph();
    data->read_graph(data_path);

    unordered_set<int> kernel;
    unordered_map<int,unordered_set<int>> comm;
    set<pair<int,int>> single;
    set<pair<int,int>> special;
    get_info(*query,kernel,comm,single,special);

    unordered_map<int,unordered_set<int>> kernel_index;
    unordered_map<int,unordered_map<int,unordered_map<int,unordered_set<int>>>> comm_index;

    pro_nodes(*query,*data,kernel,comm,kernel_index,comm_index);

    unordered_map<unsigned_key, set<vector<int>>> index;
    init_index(query->count_v,comm_index,index);

    vector<pair<unsigned_key,unsigned_key>> match_order;
    init_match_order(index,match_order);



    return 0;

}
