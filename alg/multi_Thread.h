#ifndef KCM_MULTI_THREAD_H
#define KCM_MULTI_THREAD_H

#include <thread>
#include <mutex>
#include "alg.h"

void partial_join(unsigned_key first, unsigned_key second ,unordered_map<unsigned_key, set<vector<int>>> &index,unordered_map<unsigned_key, mutex*> &mm);

void do_thread(unordered_map<unsigned_key, set<vector<int>>> &index,vector<pair<unsigned_key,unsigned_key>> &match_order);

#endif //KCM_MULTI_THREAD_H
