#include <vector>
#include <string>
#include <algorithm>

using namespace std;

class SegmentTree {
    struct Node {
        int max_len;
        int pref_len;
        int suff_len;
        char left_char;
        char right_char;
        int len;
    };

    int n;
    vector<Node> tree;

    Node merge(const Node& left, const Node& right) {
        Node parent;
        parent.len = left.len + right.len;
        parent.left_char = left.left_char;
        parent.right_char = right.right_char;

        // Merge prefix
        if (left.pref_len == left.len && left.right_char == right.left_char) {
            parent.pref_len = left.len + right.pref_len;
        } else {
            parent.pref_len = left.pref_len;
        }

        // Merge suffix
        if (right.suff_len == right.len && left.right_char == right.left_char) {
            parent.suff_len = right.len + left.suff_len;
        } else {
            parent.suff_len = right.suff_len;
        }

        // Merge maximum length
        parent.max_len = max(left.max_len, right.max_len);
        if (left.right_char == right.left_char) {
            parent.max_len = max(parent.max_len, left.suff_len + right.pref_len);
        }

        return parent;
    }

    void build(const string& s, int node, int start, int end) {
        if (start == end) {
            tree[node] = {1, 1, 1, s[start], s[start], 1};
            return;
        }
        int mid = start + (end - start) / 2;
        build(s, 2 * node, start, mid);
        build(s, 2 * node + 1, mid + 1, end);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int start, int end, int idx, char ch) {
        if (start == end) {
            tree[node] = {1, 1, 1, ch, ch, 1};
            return;
        }
        int mid = start + (end - start) / 2;
        if (start <= idx && idx <= mid) {
            update(2 * node, start, mid, idx, ch);
        } else {
            update(2 * node + 1, mid + 1, end, idx, ch);
        }
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

public:
    SegmentTree(const string& s) {
        n = s.length();
        tree.resize(4 * n);
        build(s, 1, 0, n - 1);
    }

    void update(int idx, char ch) {
        update(1, 0, n - 1, idx, ch);
    }

    int getMax() const {
        return tree[1].max_len;
    }
};

class Solution {
public:
    vector<int> longestRepeating(string s, string queryCharacters, vector<int>& queryIndices) {
        SegmentTree st(s);
        int k = queryIndices.size();
        vector<int> ans(k);

        for (int i = 0; i < k; ++i) {
            st.update(queryIndices[i], queryCharacters[i]);
            ans[i] = st.getMax();
        }

        return ans;
    }
};