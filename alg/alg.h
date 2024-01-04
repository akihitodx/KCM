//
// Created by DELL on 2024/1/3.
//

#ifndef KCM_ALG_H
#define KCM_ALG_H

#include <string>
#include "../structure/Graph.h"
#include <map>
#include <set>

void init_query(Graph &graph);

void printGraph(Graph &graph);

void get_info(Graph &graph,unordered_set<int> &kernel,map<int,unordered_set<int>> &comm, set<pair<int,int>> &single);




#endif //KCM_ALG_H
