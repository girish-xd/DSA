class Solution {
public:
    int uniqueXorTriplets(vector<int>& nums) {

        // POTD - Solve again later by yourself.
        // Observation:
        // nums[i] <= 1500, so XOR values are at most 2047.
        // Compute all possible XORs of two numbers, then XOR
        // them with every number again to obtain all triplet XORs.

        const int MAX_XOR = 2048;

        vector<bool> twoXor(MAX_XOR, false);
        vector<bool> answer(MAX_XOR, false);

        int n = nums.size();

        // XOR of any two elements (repetition allowed).
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                twoXor[nums[i] ^ nums[j]] = true;
            }
        }

        // XOR the above values with every element.
        for (int x = 0; x < MAX_XOR; x++) {
            if (!twoXor[x]) continue;

            for (int num : nums) {
                answer[x ^ num] = true;
            }
        }

        int cnt = 0;
        for (bool x : answer) {
            if (x) cnt++;
        }

        return cnt;
    }
};