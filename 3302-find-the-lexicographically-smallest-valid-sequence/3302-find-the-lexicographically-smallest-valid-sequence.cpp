class Solution {
public:
    vector<int> validSequence(string word1, string word2) {
        int n = word1.size();
        int m = word2.size();

        // suf[i] = maximum number of characters from the end of word2
        // that can be matched exactly using word1[i...n-1]
        vector<int> suf(n + 1, 0);

        int j = m - 1;
        for (int i = n - 1; i >= 0; --i) {
            if (j >= 0 && word1[i] == word2[j])
                --j;

            suf[i] = m - 1 - j;
        }

        vector<int> ans;
        int p = 0;
        bool usedMismatch = false;

        for (int i = 0; i < n && p < m; ++i) {

            // Prefer exact match because taking the earliest possible
            // index always gives a lexicographically smaller sequence.
            if (word1[i] == word2[p]) {
                ans.push_back(i);
                ++p;
            }
            // Use the one allowed mismatch only if the remaining
            // characters can be matched exactly.
            else if (!usedMismatch && suf[i + 1] >= m - p - 1) {
                ans.push_back(i);
                ++p;
                usedMismatch = true;
            }
        }

        if (p == m)
            return ans;

        return {};
    }
};