class Solution {
public:
    string lexPalindromicPermutation(string s, string target) {
        int n = s.size();
        int freq[26] = {};

        for (char c : s)
            freq[c - 'a']++;

        // Check if palindrome is possible
        int odd = 0;
        char mid = 0;

        for (int i = 0; i < 26; i++) {
            if (freq[i] % 2) {
                odd++;
                mid = char('a' + i);
            }
        }

        if (odd > 1)
            return "";

        int m = n / 2;

        // Counts available for the left half
        int original[26];
        for (int i = 0; i < 26; i++)
            original[i] = freq[i] / 2;

        auto makePalindrome = [&](string half) {
            string res = half;

            if (n % 2)
                res += mid;

            string rev = half;
            reverse(rev.begin(), rev.end());
            res += rev;

            return res;
        };

        // Check if target's first half can be matched exactly
        int cnt[26];
        copy(original, original + 26, cnt);

        string equalHalf;
        bool possible = true;

        for (int i = 0; i < m; i++) {
            int x = target[i] - 'a';

            if (cnt[x] == 0) {
                possible = false;
                break;
            }

            cnt[x]--;
            equalHalf += target[i];
        }

        // If exact first half is possible, check complete palindrome
        if (possible) {
            string candidate = makePalindrome(equalHalf);

            if (candidate > target)
                return candidate;
        }

        /*
           Try changing a position from right to left.

           Keep prefix same as target[0...i-1],
           put smallest available character > target[i],
           then fill remaining positions in sorted order.
        */
        for (int pivot = m - 1; pivot >= 0; pivot--) {
            int cnt2[26];
            copy(original, original + 26, cnt2);

            string half;
            bool validPrefix = true;

            // Match prefix before pivot
            for (int i = 0; i < pivot; i++) {
                int x = target[i] - 'a';

                if (cnt2[x] == 0) {
                    validPrefix = false;
                    break;
                }

                cnt2[x]--;
                half += target[i];
            }

            if (!validPrefix)
                continue;

            // Find smallest character greater than target[pivot]
            int x = target[pivot] - 'a';

            for (int c = x + 1; c < 26; c++) {
                if (cnt2[c] > 0) {
                    string candidateHalf = half;
                    candidateHalf += char('a' + c);
                    cnt2[c]--;

                    // Fill remaining with smallest characters
                    for (int k = 0; k < 26; k++) {
                        candidateHalf += string(cnt2[k], char('a' + k));
                    }

                    return makePalindrome(candidateHalf);
                }
            }
        }

        return "";
    }
};