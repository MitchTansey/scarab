#ifndef CACHE_MAP_H
#define CACHE_MAP_H

#include <unordered_map>

class Cache {

private:
    unordered_map<string, bool> cache_map;
    int cache_size;
    int compulsory_misses;
    int capacity_misses;
    int conflict_misses;

public:
    void init_cache_tracker(int cache_size);

    void cache_access(string address);

    int size();
}