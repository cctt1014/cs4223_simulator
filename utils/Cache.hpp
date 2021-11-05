#include <iostream>
#include <vector>

#include "config.hpp"

class Cache {
private:
    int num_sets;
    int num_ways;
    std::vector<std::vector<std::vector<int>>> dummy_cache; 
public:
    // Construct a dummy cache with shape: associativity(num_ways), num of cache set, 2
    // 2: index 0 for states, index 1 for tag
    void set_params(int cache_size, int associativity, int blk_size) {
        num_ways = associativity;
        num_sets = (cache_size / blk_size) / associativity;
        std::vector<int> temp(2, 0);
        std::vector<std::vector<int>> temp2;
        for (int i = 0; i < num_sets; i++) {
            temp2.push_back(temp);
        }
        for (int i = 0; i < associativity; i++) {
            dummy_cache.push_back(temp2);
        }
    }

    int pr_read(int i_set, int tag) {
        for (int i = 0; i < num_ways; i++) {
            // Read hit
            if ((dummy_cache[i][i_set][0] != status_MESI::I) && (dummy_cache[i][i_set][1] == tag))
                return 1;
        }
        // Read miss
        return 1; // placeholder
    }

    int pr_write(int i_set, int tag) {
        return 1; // placeholder
    } 
    
};