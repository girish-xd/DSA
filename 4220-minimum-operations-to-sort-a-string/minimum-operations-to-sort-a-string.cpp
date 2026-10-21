class Solution {
public:
    int minOperations(string s) {
        int n = s.size();
        
        // Case 1: Already sorted
        bool sorted = true;
        for (int i = 1; i < n; ++i) {
            if (s[i] < s[i - 1]) {
                sorted = false;
                break;
            }
        }
        if (sorted) return 0;
        
        // Case 2: Impossible length 2 string
        if (n == 2) return -1;
        
        // Find minimum and maximum characters
        char mn = *std::min_element(s.begin(), s.end());
        char mx = *std::max_element(s.begin(), s.end());
        
        // Case 3: min at start or max at end -> 1 operation
        if (s[0] == mn || s[n - 1] == mx) {
            return 1;
        }
        
        // Case 4: min or max exists in the interior -> 2 operations
        for (int i = 1; i < n - 1; ++i) {
            if (s[i] == mn || s[i] == mx) {
                return 2;
            }
        }
        
        // Case 5: max is at start and min is at end -> 3 operations
        return 3;
    }
};