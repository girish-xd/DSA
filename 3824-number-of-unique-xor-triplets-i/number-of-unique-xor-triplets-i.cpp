class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {
        int n = nums.size();

        // POTD - Solve again later by yourself.
        // Observation:
        // If n < 3, only the elements themselves are possible.
        // For n >= 3, all XOR values in the range [0, 2^k - 1]
        // become achievable, where k is the number of bits in n.
        // Hence, answer is the next power of two greater than n.

        if (n <= 2) return n;

        int ans = 1;
        while (ans <= n) {
            ans <<= 1;
        }

        return ans;
    }
};