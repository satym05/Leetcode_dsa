class Solution {
public:
    bool stoneGameIX(vector<int>& stones) {
        int cnt[3] = {0, 0, 0};

        for (int x : stones) {
            cnt[x % 3]++;
        }

        int c0 = cnt[0];
        int c1 = cnt[1];
        int c2 = cnt[2];

        // If there are no stones of one of the useful remainders
        if (c1 == 0 || c2 == 0) {
            return max(c1, c2) > 2 && (c0 % 2 == 1);
        }

        // Both remainder-1 and remainder-2 stones exist
        return abs(c1 - c2) > 2 || (c0 % 2 == 0);
    }
};