class Solution {
public:
    int findGCD(vector<int>& nums) {

        int maxEl = *max_element(nums.begin(), nums.end());
        int minEl = *min_element(nums.begin(), nums.end());

        return __gcd(maxEl, minEl);
    }
};