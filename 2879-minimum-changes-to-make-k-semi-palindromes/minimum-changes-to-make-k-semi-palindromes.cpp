class Solution {
public:
    int minimumChanges(string s, int k) {
        int n = s.size();
        const int INF = 1e9;
        
        // Precompute proper divisors
        vector<vector<int>> divisors(n + 1);
        for (int len = 2; len <= n; ++len) {
            for (int d = 1; d < len; ++d) {
                if (len % d == 0) {
                    divisors[len].push_back(d);
                }
            }
        }
        
        // Precompute substring semi-palindrome costs
        vector<vector<int>> cost(n, vector<int>(n, INF));
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                int len = j - i + 1;
                int min_changes = INF;
                for (int d : divisors[len]) {
                    int changes = 0;
                    for (int start = 0; start < d; ++start) {
                        int l = i + start;
                        int r = j - (d - 1 - start);
                        while (l < r) {
                            if (s[l] != s[r]) changes++;
                            l += d;
                            r -= d;
                        }
                    }
                    min_changes = min(min_changes, changes);
                }
                cost[i][j] = min_changes;
            }
        }
        
        // Partition DP
        vector<vector<int>> dp(k + 1, vector<int>(n + 1, INF));
        dp[0][0] = 0;
        
        for (int p = 1; p <= k; ++p) {
            for (int i = 2 * p; i <= n; ++i) {
                for (int j = 2 * (p - 1); j <= i - 2; ++j) {
                    dp[p][i] = min(dp[p][i], dp[p - 1][j] + cost[j][i - 1]);
                }
            }
        }
        
        return dp[k][n];
    }
};