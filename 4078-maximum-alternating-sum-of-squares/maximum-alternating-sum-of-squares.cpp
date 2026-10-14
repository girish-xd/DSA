class Solution {
public:
    long long maxAlternatingSum(vector<int>& nums) {
        int n = nums.size();
        vector<long long> squares(n);
        
        for (int i = 0; i < n; ++i) {
            squares[i] = 1LL * nums[i] * nums[i];
        }
        
        // Sort squares in ascending order
        sort(squares.begin(), squares.end());
        
        long long score = 0;
        int m = n / 2; // Number of negative slots
        
        // The first m elements are subtracted
        for (int i = 0; i < m; ++i) {
            score -= squares[i];
        }
        
        // The remaining elements are added
        for (int i = m; i < n; ++i) {
            score += squares[i];
        }
        
        return score;
    }
};