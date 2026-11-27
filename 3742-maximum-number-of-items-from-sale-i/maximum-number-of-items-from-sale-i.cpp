class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        const int MAX_F = 1500;
        vector<int> freq(MAX_F + 1, 0);
        int min_price = INT_MAX;
        
        for (const auto& item : items) {
            freq[item[0]]++;
            min_price = min(min_price, item[1]);
        }
        
        // Precompute number of free copies obtained when buying 1 copy of an item with factor f
        vector<int> free_by_factor(MAX_F + 1, 0);
        for (int f = 1; f <= MAX_F; ++f) {
            if (freq[f] > 0) {
                int total_multiples = 0;
                for (int m = f; m <= MAX_F; m += f) {
                    total_multiples += freq[m];
                }
                free_by_factor[f] = total_multiples - 1;
            }
        }
        
        // 0/1 Knapsack for choosing which distinct items to buy at least once
        const int NEG_INF = -1e9;
        vector<int> dp(budget + 1, NEG_INF);
        dp[0] = 0;
        
        for (const auto& item : items) {
            int f = item[0];
            int p = item[1];
            if (p > budget) continue;
            
            int val = 1 + free_by_factor[f];
            for (int c = budget; c >= p; --c) {
                if (dp[c - p] != NEG_INF) {
                    dp[c] = max(dp[c], dp[c - p] + val);
                }
            }
        }
        
        // Spend remaining budget on the cheapest item (+1 copy per min_price)
        int ans = 0;
        for (int c = 0; c <= budget; ++c) {
            if (dp[c] >= 0) {
                int extra = (budget - c) / min_price;
                ans = max(ans, dp[c] + extra);
            }
        }
        
        return ans;
    }
};