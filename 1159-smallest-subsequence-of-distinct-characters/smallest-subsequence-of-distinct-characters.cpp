class Solution {
public:
    string smallestSubsequence(string s) {

        // POTD - Solve again later by yourself.
        // Idea:
        // Maintain a monotonic increasing stack.
        // If the current character is smaller than the top of the stack
        // and the top character appears later as well, pop it.
        // Also ensure every character is taken only once.

        vector<int> last(26);
        for (int i = 0; i < s.size(); i++) {
            last[s[i] - 'a'] = i;
        }

        vector<bool> used(26, false);
        string st = "";

        for (int i = 0; i < s.size(); i++) {
            char c = s[i];

            if (used[c - 'a']) continue;

            while (!st.empty() &&
                   st.back() > c &&
                   last[st.back() - 'a'] > i) {
                used[st.back() - 'a'] = false;
                st.pop_back();
            }

            st.push_back(c);
            used[c - 'a'] = true;
        }

        return st;
    }
};