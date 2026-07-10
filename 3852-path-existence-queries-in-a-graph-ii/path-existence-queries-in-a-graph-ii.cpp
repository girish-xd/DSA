class Solution {
public:
    vector<int> pathExistenceQueries(int n, vector<int>& nums, int maxDiff, vector<vector<int>>& queries) {
           // POTD - Solve again later by yourself.
        // Idea:
        // 1. Sort nodes by value.
        // 2. Build connected components using adjacent gaps.
        // 3. For every sorted position, find the farthest node reachable in ONE edge.
        // 4. Binary lifting on these greedy jumps to answer minimum hops.

        vector<pair<int,int>> v;
        for (int i = 0; i < n; i++)
            v.push_back({nums[i], i});

        sort(v.begin(), v.end());

        vector<int> pos(n), comp(n);

        int id = 0;
        comp[0] = 0;
        pos[v[0].second] = 0;

        for (int i = 1; i < n; i++) {
            if (v[i].first - v[i - 1].first > maxDiff)
                id++;
            comp[i] = id;
            pos[v[i].second] = i;
        }

        // farthest reachable in one edge
        vector<int> nxt(n);
        int r = 0;
        for (int i = 0; i < n; i++) {
            while (r + 1 < n && v[r + 1].first - v[i].first <= maxDiff)
                r++;
            nxt[i] = r;
        }

        int LOG = 20;
        vector<vector<int>> up(LOG, vector<int>(n));

        up[0] = nxt;
        for (int k = 1; k < LOG; k++) {
            for (int i = 0; i < n; i++) {
                up[k][i] = up[k - 1][up[k - 1][i]];
            }
        }

        vector<int> ans;

        for (auto &q : queries) {
            int a = pos[q[0]];
            int b = pos[q[1]];

            if (a == b) {
                ans.push_back(0);
                continue;
            }

            if (a > b) swap(a, b);

            if (comp[a] != comp[b]) {
                ans.push_back(-1);
                continue;
            }

            int cur = a;
            int steps = 0;

            for (int k = LOG - 1; k >= 0; k--) {
                if (up[k][cur] < b) {
                    cur = up[k][cur];
                    steps += (1 << k);
                }
            }

            ans.push_back(steps + 1);
        }

        return ans;
    }
};