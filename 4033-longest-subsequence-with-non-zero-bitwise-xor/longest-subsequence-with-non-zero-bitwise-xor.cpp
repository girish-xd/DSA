class Solution {
public:
    int longestSubsequence(vector<int>& nums) {

        // POTD - Solve again later by yourself.
        // If XOR of the whole array is non-zero, take everything.
        // Otherwise, if any non-zero element exists, remove one
        // element and the remaining XOR becomes non-zero.
        // If all elements are zero, answer is 0.

        int xr = 0;
        bool hasNonZero = false;

        for (int x : nums) {
            xr ^= x;
            if (x != 0)
                hasNonZero = true;
        }

        if (xr != 0)
            return nums.size();

        return hasNonZero ? nums.size() - 1 : 0;
    }
};