class Solution {
public:
    string smallestSubsequence(string s) {
        vector<int> last(26);
        vector<bool> visited(26, false);

        // Store the last occurrence of each character
        for (int i = 0; i < s.size(); i++) {
            last[s[i] - 'a'] = i;
        }

        string st;

        for (int i = 0; i < s.size(); i++) {
            char c = s[i];

            if (visited[c - 'a'])
                continue;

            while (!st.empty() &&
                   st.back() > c &&
                   last[st.back() - 'a'] > i) {
                visited[st.back() - 'a'] = false;
                st.pop_back();
            }

            st.push_back(c);
            visited[c - 'a'] = true;
        }

        return st;
    }
};


