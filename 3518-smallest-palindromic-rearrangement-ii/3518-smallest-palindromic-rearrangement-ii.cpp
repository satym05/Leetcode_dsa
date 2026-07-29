class Solution {
public:
    string smallestPalindrome(string s, int k) {
        vector<int> freq(26, 0);

        for (char c : s) {
            freq[c - 'a']++;
        }

        // Build the first half of the palindrome
        vector<int> half(26, 0);
        char middle = 0;

        for (int i = 0; i < 26; i++) {
            half[i] = freq[i] / 2;
            if (freq[i] % 2 == 1) {
                middle = char('a' + i);
            }
        }

        int halfLen = s.size() / 2;

        // Count number of distinct permutations of the first half.
        // We only need to know whether it is >= k.
        auto countWays = [&](vector<int> cnt) -> long long {
            long long ways = 1;
            int remaining = 0;

            for (int x : cnt) {
                remaining += x;
            }

            for (int c = 0; c < 26; c++) {
                for (int j = 1; j <= cnt[c]; j++) {
                    // ways = ways * (remaining - cnt[c] + j) / j
                    // Instead of calculating factorials, construct
                    // multinomial incrementally.
                }
            }

            // Calculate multinomial using combinations.
            ways = 1;
            remaining = 0;

            for (int c = 0; c < 26; c++) {
                if (cnt[c] == 0) continue;

                // Choose positions for this character
                int x = cnt[c];

                long long comb = 1;
                for (int i = 1; i <= x; i++) {
                    if (comb > k) return k;
                    comb = comb * (remaining + i) / i;
                    if (comb >= k) {
                        comb = k;
                        break;
                    }
                }

                ways *= comb;
                if (ways >= k) return k;

                remaining += x;
            }

            return ways;
        };

        // Check whether at least k palindromes exist.
        if (countWays(half) < k) {
            return "";
        }

        string left;
        left.reserve(halfLen);

        // Construct the lexicographically k-th smallest first half.
        for (int pos = 0; pos < halfLen; pos++) {
            for (int c = 0; c < 26; c++) {
                if (half[c] == 0) continue;

                // Try placing this character.
                half[c]--;

                long long ways = countWays(half);

                if (k > ways) {
                    // Skip all permutations beginning with this character.
                    k -= ways;
                    half[c]++;
                } else {
                    // This character belongs at this position.
                    left.push_back(char('a' + c));
                    break;
                }
            }
        }

        // Create the complete palindrome.
        string right = left;
        reverse(right.begin(), right.end());

        if (middle != 0) {
            return left + string(1, middle) + right;
        }

        return left + right;
    }
};