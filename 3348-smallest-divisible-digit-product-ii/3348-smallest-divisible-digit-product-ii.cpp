class Solution {
public:
    static const int INF = 1e9;

    int dp[47][30][21][17];

    int p2[10] = {0,0,1,0,2,0,1,0,3,0};
    int p3[10] = {0,0,0,1,0,0,1,0,0,2};
    int p5[10] = {0,0,0,0,0,1,0,0,0,0};
    int p7[10] = {0,0,0,0,0,0,0,1,0,0};

    void buildDP(int A, int B, int C, int D) {
        for (int a = 0; a <= A; ++a)
            for (int b = 0; b <= B; ++b)
                for (int c = 0; c <= C; ++c)
                    for (int d = 0; d <= D; ++d)
                        dp[a][b][c][d] = INF;

        dp[0][0][0][0] = 0;

        for (int a = 0; a <= A; ++a) {
            for (int b = 0; b <= B; ++b) {
                for (int c = 0; c <= C; ++c) {
                    for (int d = 0; d <= D; ++d) {

                        if (a == 0 && b == 0 && c == 0 && d == 0)
                            continue;

                        for (int x = 2; x <= 9; ++x) {
                            int na = max(0, a - p2[x]);
                            int nb = max(0, b - p3[x]);
                            int nc = max(0, c - p5[x]);
                            int nd = max(0, d - p7[x]);

                            dp[a][b][c][d] =
                                min(dp[a][b][c][d],
                                    dp[na][nb][nc][nd] + 1);
                        }
                    }
                }
            }
        }
    }

    bool factorize(long long t, int &a, int &b, int &c, int &d) {
        a = b = c = d = 0;

        while (t % 2 == 0) {
            ++a;
            t /= 2;
        }

        while (t % 3 == 0) {
            ++b;
            t /= 3;
        }

        while (t % 5 == 0) {
            ++c;
            t /= 5;
        }

        while (t % 7 == 0) {
            ++d;
            t /= 7;
        }

        return t == 1;
    }

    void removeDigit(int x, int &a, int &b, int &c, int &d) {
        a = max(0, a - p2[x]);
        b = max(0, b - p3[x]);
        c = max(0, c - p5[x]);
        d = max(0, d - p7[x]);
    }

    string buildSuffix(int len, int a, int b, int c, int d) {
        string res;
        res.reserve(len);

        for (int pos = 0; pos < len; ++pos) {
            int remaining = len - pos - 1;

            for (int x = 1; x <= 9; ++x) {
                int na = max(0, a - p2[x]);
                int nb = max(0, b - p3[x]);
                int nc = max(0, c - p5[x]);
                int nd = max(0, d - p7[x]);

                if (dp[na][nb][nc][nd] <= remaining) {
                    res.push_back(char('0' + x));

                    a = na;
                    b = nb;
                    c = nc;
                    d = nd;

                    break;
                }
            }
        }

        return res;
    }

    string smallestNumber(string num, long long t) {
        int A, B, C, D;

        // Digits can only contain prime factors 2,3,5,7.
        if (!factorize(t, A, B, C, D))
            return "-1";

        int n = num.size();

        buildDP(A, B, C, D);

        /*
         * Minimum number of digits required to construct
         * a product divisible by t.
         */
        int need = dp[A][B][C][D];

        /*
         * If we need more digits than num has,
         * simply construct the smallest number of that length.
         */
        if (need > n) {
            return buildSuffix(need, A, B, C, D);
        }

        /*
         * Check whether num itself is valid.
         */
        int a = A, b = B, c = C, d = D;
        bool zeroFree = true;

        for (char ch : num) {
            int x = ch - '0';

            if (x == 0) {
                zeroFree = false;
                break;
            }

            removeDigit(x, a, b, c, d);
        }

        if (zeroFree && a == 0 && b == 0 && c == 0 && d == 0)
            return num;

        /*
         * pref[i] = remaining prime-factor requirement
         * after consuming num[0 ... i-1].
         */
        vector<array<int,4>> pref(n + 1);

        pref[0] = {A, B, C, D};

        for (int i = 0; i < n; ++i) {
            pref[i] = pref[i];

            int x = num[i] - '0';

            if (x == 0) {
                // Mark prefix as invalid.
                pref[i + 1] = {-1, -1, -1, -1};
            } else {
                pref[i + 1] = pref[i];

                if (pref[i][0] >= 0) {
                    removeDigit(
                        x,
                        pref[i + 1][0],
                        pref[i + 1][1],
                        pref[i + 1][2],
                        pref[i + 1][3]
                    );
                }
            }
        }

        /*
         * Try changing a position from RIGHT to LEFT.
         *
         * Rightmost change gives the smallest number because
         * it preserves the longest possible prefix.
         */
        for (int i = n - 1; i >= 0; --i) {

            // Prefix before i must be valid and zero-free.
            if (pref[i][0] < 0)
                continue;

            int cur = num[i] - '0';

            // Digits must be 1..9.
            int start = max(1, cur + 1);

            for (int x = start; x <= 9; ++x) {

                int a2 = pref[i][0];
                int b2 = pref[i][1];
                int c2 = pref[i][2];
                int d2 = pref[i][3];

                removeDigit(x, a2, b2, c2, d2);

                int remaining = n - i - 1;

                if (dp[a2][b2][c2][d2] <= remaining) {

                    string ans = num.substr(0, i);

                    ans.push_back(char('0' + x));

                    ans += buildSuffix(
                        remaining,
                        a2, b2, c2, d2
                    );

                    return ans;
                }
            }
        }

        /*
         * No valid number of length n exists.
         *
         * Since need <= n here, length n+1 is enough.
         */
        return buildSuffix(n + 1, A, B, C, D);
    }
};