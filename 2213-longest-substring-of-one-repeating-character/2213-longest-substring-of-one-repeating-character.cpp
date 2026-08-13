class Solution {
public:
    struct Node {
        int len;
        int left;
        int right;
        int best;

        Node(int l = 0, int r = 0, int b = 0, int x = 0)
            : len(l), left(r), right(b), best(x) {}
    };

    vector<Node> tree;
    string s;

    Node merge(Node a, Node b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Node res;
        res.len = a.len + b.len;

        res.left = a.left;
        res.right = b.right;
        res.best = max(a.best, b.best);

        // If the boundary characters are equal,
        // the two runs can be joined.
        if (s == s) {
            // handled below using character information
        }

        return res;
    }

    struct Info {
        int len, pref, suff, best;
        char lc, rc;

        Info(int l = 0, int p = 0, int su = 0, int b = 0,
             char x = 0, char y = 0)
            : len(l), pref(p), suff(su), best(b), lc(x), rc(y) {}
    };

    vector<Info> seg;

    Info combine(Info a, Info b) {
        if (a.len == 0) return b;
        if (b.len == 0) return a;

        Info res;
        res.len = a.len + b.len;
        res.lc = a.lc;
        res.rc = b.rc;

        res.pref = a.pref;
        if (a.pref == a.len && a.rc == b.lc)
            res.pref = a.len + b.pref;

        res.suff = b.suff;
        if (b.suff == b.len && a.rc == b.lc)
            res.suff = b.len + a.suff;

        res.best = max(a.best, b.best);

        if (a.rc == b.lc)
            res.best = max(res.best, a.suff + b.pref);

        return res;
    }

    void build(int node, int l, int r) {
        if (l == r) {
            seg[node] = Info(1, 1, 1, 1, s[l], s[l]);
            return;
        }

        int mid = (l + r) / 2;

        build(node * 2, l, mid);
        build(node * 2 + 1, mid + 1, r);

        seg[node] = combine(seg[node * 2], seg[node * 2 + 1]);
    }

    void update(int node, int l, int r, int idx, char c) {
        if (l == r) {
            s[idx] = c;
            seg[node] = Info(1, 1, 1, 1, c, c);
            return;
        }

        int mid = (l + r) / 2;

        if (idx <= mid)
            update(node * 2, l, mid, idx, c);
        else
            update(node * 2 + 1, mid + 1, r, idx, c);

        seg[node] = combine(seg[node * 2], seg[node * 2 + 1]);
    }

    vector<int> longestRepeating(string str,
                                 string queryCharacters,
                                 vector<int>& queryIndices) {
        s = str;
        int n = s.size();

        seg.resize(4 * n + 5);

        build(1, 0, n - 1);

        vector<int> ans;

        for (int i = 0; i < queryIndices.size(); i++) {
            update(1, 0, n - 1,
                   queryIndices[i],
                   queryCharacters[i]);

            ans.push_back(seg[1].best);
        }

        return ans;
    }
};