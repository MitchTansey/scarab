#include "cache_map.h"
#include <iostream>

using namespace std;

const int max_cache_size = 4096;

void Cache::init_cache(){
    this->cache_size = 0;
    cache_map.clear()
}

void Cache::cache_access(int address){
    if(cache_map.find(address) == cache_map.end()){
        // Compulsory Miss
    } else if(size() > max_cache_size){
        // Capacity Miss
    } else {
        // Conflict Miss
    }
}

void size(){
    return Cache->cache_size;
}