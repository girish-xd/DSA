class Solution {
public:
    int minInsertions(string s) {
        int open = 0;
        int ans = 0;

        for (int i = 0; i < s.size(); i++) {

            if (s[i] == '(') {
                open++;
            }
            else {
                // Need an opening '('
                if (open == 0) {
                    ans++;
                    open++;
                }

                // Current ')' needs another ')' to form "))"
                if (i + 1 < s.size() && s[i + 1] == ')') {
                    i++;
                }
                else {
                    ans++;
                }

                // One " )) " closes one '('
                open--;
            }
        }

        // Every remaining '(' needs "))"
        ans += 2 * open;

        return ans;
    }
};