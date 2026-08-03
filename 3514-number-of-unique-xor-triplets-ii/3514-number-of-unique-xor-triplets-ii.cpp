class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        vector<bool> present(2048, false);
        vector<int> vals;

        for (int x : nums) {
            if (!present[x]) {
                present[x] = true;
                vals.push_back(x);
            }
        }

        vector<bool> pairXor(2048, false);

        for (int a : vals) {
            for (int b : vals) {
                pairXor[a ^ b] = true;
            }
        }

        vector<bool> ans(2048, false);

        for (int x = 0; x < 2048; x++) {
            if (!pairXor[x]) continue;
            for (int v : vals) {
                ans[x ^ v] = true;
            }
        }

        int cnt = 0;
        for (bool x : ans)
            if (x) cnt++;

        return cnt;
    }
};