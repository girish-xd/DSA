class Solution {
public:
    int maxSum(vector<int>& nums, int k) {
        const int MOD = 1e9 + 7;
        
        // nums[i] <= 10^9 < 2^30
        vector<int> bit_count(30, 0);
        for (int x : nums) {
            for (int b = 0; b < 30; ++b) {
                if ((x >> b) & 1) {
                    bit_count[b]++;
                }
            }
        }
        
        long long ans = 0;
        
        // Greedily build the k largest elements
        for (int i = 0; i < k; ++i) {
            long long val = 0;
            for (int b = 0; b < 30; ++b) {
                if (bit_count[b] > 0) {
                    val |= (1LL << b);
                    bit_count[b]--;
                }
            }
            ans = (ans + (val % MOD) * (val % MOD)) % MOD;
        }
        
        return ans;
    }
};