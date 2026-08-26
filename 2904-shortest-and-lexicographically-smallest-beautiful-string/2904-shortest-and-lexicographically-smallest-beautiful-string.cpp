class Solution {
public:
    string shortestBeautifulSubstring(string s, int k) {
        int n = s.size();
        int ones = 0;
        int left = 0;

        string ans = "";
        int minLen = INT_MAX;

        for (int right = 0; right < n; right++) {
            if (s[right] == '1')
                ones++;

            // Shrink while we have more than k ones
            while (ones > k) {
                if (s[left] == '1')
                    ones--;
                left++;
            }

            // Exactly k ones
            if (ones == k) {
                // Remove unnecessary leading zeros
                while (left <= right && s[left] == '0') {
                    left++;
                }

                int len = right - left + 1;
                string curr = s.substr(left, len);

                if (len < minLen ||
                    (len == minLen && curr < ans)) {
                    minLen = len;
                    ans = curr;
                }
            }
        }

        return ans;
    }
};