class Solution {
public:
    string lexGreaterPermutation(string s, string target) {
        int n = s.size();
        int cnt[26] = {};

        for (char c : s) {
            cnt[c - 'a']++;
        }

        string ans;
        int i = 0;

        // Match target prefix as long as possible
        for (; i < n; i++) {
            int x = target[i] - 'a';

            if (cnt[x] > 0) {
                cnt[x]--;
                ans += target[i];
            } else {
                break;
            }
        }

        // At the first position where exact match is impossible,
        // try the smallest character greater than target[i].
        if (i < n) {
            int x = target[i] - 'a';

            for (int c = x + 1; c < 26; c++) {
                if (cnt[c] > 0) {
                    string res = ans;
                    res += char('a' + c);
                    cnt[c]--;

                    // Add remaining characters in sorted order
                    for (int k = 0; k < 26; k++) {
                        res += string(cnt[k], char('a' + k));
                    }

                    return res;
                }
            }
        }

        // Backtrack: try increasing the rightmost possible position
        for (int j = (int)ans.size() - 1; j >= 0; j--) {
            cnt[ans[j] - 'a']++;

            int x = target[j] - 'a';

            for (int c = x + 1; c < 26; c++) {
                if (cnt[c] > 0) {
                    string res = ans.substr(0, j);
                    res += char('a' + c);
                    cnt[c]--;

                    // Remaining characters in smallest order
                    for (int k = 0; k < 26; k++) {
                        res += string(cnt[k], char('a' + k));
                    }

                    return res;
                }
            }
        }

        return "";
    }
};