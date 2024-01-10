#include <iostream>
#include "alg/alg.h"
#include "structure/Graph.h"
#include <unordered_set>
#include <map>
using namespace std;

int main() {

//    string query_path = "../test/query";
//    string query_path = "../test/demo1";
//    string query_path = "../test/demo2";
    string query_path = "../test/data";

    auto* query = new Graph();
    query->read_graph(query_path);
    printGraph(*query);

    unordered_set<int> kernel;
    unordered_map<int,unordered_set<int>> comm;
    set<pair<int,int>> single;
    set<pair<int,int>> special;
    get_info(*query,kernel,comm,single,special);
    for(auto i : kernel){
        cout<<i<<" ";
    }
    cout<<endl;






    return 0;

}
