class Solution {
    struct Node {
        int prod = 1;
        int count[5] = {0};
    };

    int n, k;
    vector<Node> tree;

    Node merge(const Node& left, const Node& right) {
        Node res;
        res.prod = (left.prod * right.prod) % k;
        for (int r = 0; r < k; ++r) {
            res.count[r] = left.count[r];
        }
        for (int r = 0; r < k; ++r) {
            int new_rem = (left.prod * r) % k;
            res.count[new_rem] += right.count[r];
        }
        return res;
    }

    void build(int node, int l, int r, const vector<int>& nums) {
        if (l == r) {
            int val = nums[l] % k;
            tree[node].prod = val;
            tree[node].count[val] = 1;
            return;
        }
        int mid = l + (r - l) / 2;
        build(2 * node, l, mid, nums);
        build(2 * node + 1, mid + 1, r, nums);
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    void update(int node, int l, int r, int idx, int val) {
        if (l == r) {
            for (int i = 0; i < k; ++i) tree[node].count[i] = 0;
            int rem = val % k;
            tree[node].prod = rem;
            tree[node].count[rem] = 1;
            return;
        }
        int mid = l + (r - l) / 2;
        if (idx <= mid) {
            update(2 * node, l, mid, idx, val);
        } else {
            update(2 * node + 1, mid + 1, r, idx, val);
        }
        tree[node] = merge(tree[2 * node], tree[2 * node + 1]);
    }

    Node query(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) {
            return tree[node];
        }
        int mid = l + (r - l) / 2;
        if (qr <= mid) {
            return query(2 * node, l, mid, ql, qr);
        }
        if (ql > mid) {
            return query(2 * node + 1, mid + 1, r, ql, qr);
        }
        return merge(query(2 * node, l, mid, ql, qr), 
                     query(2 * node + 1, mid + 1, r, ql, qr));
    }
public:
    vector<int> resultArray(vector<int>& nums, int k, vector<vector<int>>& queries) {
        this->n = nums.size();
        this->k = k;
        tree.assign(4 * n, Node());

        build(1, 0, n - 1, nums);

        vector<int> result;
        result.reserve(queries.size());

        for (const auto& q : queries) {
            int idx = q[0];
            int val = q[1];
            int start = q[2];
            int x = q[3];

            update(1, 0, n - 1, idx, val);
            Node res = query(1, 0, n - 1, start, n - 1);
            result.push_back(res.count[x]);
        }

        return result;
    }
};