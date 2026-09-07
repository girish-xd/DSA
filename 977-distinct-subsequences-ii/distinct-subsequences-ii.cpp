class Solution {
public:
    int distinctSubseqII(string s) {
        long long dp[26] = {0};
        long long mod = 1e9 + 7;
            for (char c : s) {
            long long current_sum = 0;
            for (int i = 0; i < 26; ++i) {
                current_sum = (current_sum + dp[i]) % mod;
            }
            dp[c - 'a'] = (current_sum + 1) % mod;
        }
        
        long long result = 0;
        for (int i = 0; i < 26; ++i) {
            result = (result + dp[i]) % mod;
        }
        
        return result;
    }
};