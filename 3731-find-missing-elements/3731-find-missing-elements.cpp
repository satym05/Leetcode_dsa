class Solution {
public:
    vector<int> findMissingElements(vector<int>& nums) {
        int mn = *min_element(nums.begin(), nums.end());
        int mx = *max_element(nums.begin(), nums.end());

        vector<bool> present(101, false);
        for (int x : nums) present[x] = true;

        vector<int> ans;
        for (int x = mn; x <= mx; x++) {
            if (!present[x]) ans.push_back(x);
        }

        return ans;
    }
};