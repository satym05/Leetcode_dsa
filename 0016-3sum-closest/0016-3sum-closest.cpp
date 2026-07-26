class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());

        int ans = nums[0] + nums[1] + nums[2];

        for (int i = 0; i < nums.size() - 2; i++) {
            int l = i + 1, r = nums.size() - 1;

            while (l < r) {
                int sum = nums[i] + nums[l] + nums[r];

                if (abs(target - sum) < abs(target - ans))
                    ans = sum;

                if (sum < target)
                    l++;
                else if (sum > target)
                    r--;
                else
                    return sum; // Exact match
            }
        }

        return ans;
    }
};