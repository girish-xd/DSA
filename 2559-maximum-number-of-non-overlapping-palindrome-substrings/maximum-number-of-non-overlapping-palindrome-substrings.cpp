class Solution {
public:
    int maxPalindromes(string s, int k) {
       int n = s.length();
        int count = 0;
        int last_end = -1; // End index of the last chosen palindrome

        auto is_palindrome = [&](int l, int r) {
            while (l < r) {
                if (s[l] != s[r]) return false;
                ++l;
                --r;
            }
            return true;
        };

        for (int i = k - 1; i < n; ++i) {
            // Check for a palindrome of length k ending at i
            if (i - k + 1 > last_end && is_palindrome(i - k + 1, i)) {
                ++count;
                last_end = i;
            }
            // Otherwise, check for a palindrome of length k + 1 ending at i
            else if (i - k > last_end && is_palindrome(i - k, i)) {
                ++count;
                last_end = i;
            }
        }

        return count; 
    }
};