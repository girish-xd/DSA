class Solution {
public:
// POTD - Solve again later by yourself.
        // Idea:
        // For each connected component,
        // let number of nodes = k.
        // A complete graph must have k*(k-1)/2 edges.
        // Since every edge is counted twice in adjacency list,
        // compare total degree sum with k*(k-1).

void dfs(int node, vector<vector<int>> &adj, vector<bool> &vis, int &nodes, int &edgeCount) {
        vis[node] = true;
        nodes++;
        edgeCount += adj[node].size();

        for (int nei : adj[node]) {
            if (!vis[nei])
                dfs(nei, adj, vis, nodes, edgeCount);
        }
    }
    int countCompleteComponents(int n, vector<vector<int>>& edges) {
         
        vector<vector<int>> adj(n);

        for (auto &e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        vector<bool> vis(n, false);
        int ans = 0;

        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                int nodes = 0;
                int edgeCount = 0;

                dfs(i, adj, vis, nodes, edgeCount);

                if (edgeCount == nodes * (nodes - 1))
                    ans++;
            }
        }

        return ans;
    }
};