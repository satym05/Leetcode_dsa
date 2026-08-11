class Solution {
public:
    int missingInteger(vector<int>& nums) {
        int sum = nums[0];

        // Find the sum of the longest sequential prefix
        int i = 1;
        while (i < nums.size() && nums[i] == nums[i - 1] + 1) {
            sum += nums[i];
            i++;
        }

        // Find the smallest missing integer >= sum
        unordered_set<int> s(nums.begin(), nums.end());

        while (s.count(sum)) {
            sum++;
        }

        return sum;
    }
};