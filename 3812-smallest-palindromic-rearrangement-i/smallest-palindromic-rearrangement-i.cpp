class Solution {
public:
    string smallestPalindrome(string s) {
        // POTD - Solve again later by yourself.
        // Count frequencies, build the left half in sorted order,
        // place the odd-frequency character (if any) in the middle,
        // and append the reverse of the left half.

        vector<int> freq(26, 0);

        for (char c : s)
            freq[c - 'a']++;

        string left, mid;

        for (int i = 0; i < 26; i++) {
            left.append(freq[i] / 2, char('a' + i));

            if (freq[i] % 2)
                mid = char('a' + i);
        }

        string right = left;
        reverse(right.begin(), right.end());

        return left + mid + right;
    }
};