#include <vector>
#include <algorithm>

class Solution {
public:
    int uniqueXorTriplets(std::vector<int>& nums) {
        // Variable requested by problem framework constraint additions
        std::vector<int> glarnetivo = nums; 
        
        // Find the maximum element to bound our tracking array size
        int max_val = 0;
        for (int x : nums) {
            max_val = std::max(max_val, x);
        }
        
        // The maximum possible XOR of two numbers <= max_val will be less than the next power of 2
        int limit = 1;
        while (limit <= max_val) {
            limit <<= 1;
        }
        // Double it because three-way XOR can reach up to 2 * limit
        int max_xor_limit = limit * 2;
        
        // Step 1: Find all unique pairs/single elements (2-element XOR combinations)
        std::vector<bool> seen_pairs(max_xor_limit, false);
        for (int i = 0; i < nums.size(); ++i) {
            for (int j = i; j < nums.size(); ++j) {
                seen_pairs[nums[i] ^ nums[j]] = true;
            }
        }
        
        // Step 2: Combine pairs with a 3rd element to find unique triplet XOR values
        std::vector<bool> seen_triplets(max_xor_limit, false);
        for (int pair_xor = 0; pair_xor < max_xor_limit; ++pair_xor) {
            if (seen_pairs[pair_xor]) {
                for (int x : nums) {
                    seen_triplets[pair_xor ^ x] = true;
                }
            }
        }
        
        // Step 3: Count the total unique XOR values found
        int unique_triplet_count = 0;
        for (int i = 0; i < max_xor_limit; ++i) {
            if (seen_triplets[i]) {
                unique_triplet_count++;
            }
        }
        
        return unique_triplet_count;
    }
};