//
// Created by DELL on 2024/1/3.
//

#ifndef KCM_ALG_H
#define KCM_ALG_H

#include <string>
#include "../structure/Graph.h"
#include <map>
#include <unordered_map>
#include <set>

void init_query(Graph &graph);

void printGraph(Graph &graph);

void get_info(Graph &graph,unordered_set<int> &kernel,unordered_map<int,unordered_set<int>> &comm, set<pair<int,int>> &single,set<pair<int,int>> &specical);

void pro_nodes(Graph &query,Graph &data,unordered_set<int> &kernel,unordered_map<int,unordered_set<int>> &comm,unordered_map<int,unordered_set<int>> &kernel_index,unordered_map<int,unordered_map<int,unordered_map<int,unordered_set<int>>>> &comm_index);

void init_index(unordered_map<int,unordered_set<int>> &kernel_index,unordered_map<int,unordered_map<int,unordered_map<int,unordered_set<int>>>> &comm_index);
#endif //KCM_ALG_H
