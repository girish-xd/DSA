/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    vector<int> nodesBetweenCriticalPoints(ListNode* head) {
          int first = -1;
        int prevCritical = -1;
        int minDist = INT_MAX;

        ListNode* prev = head;
        ListNode* curr = head->next;

        int index = 1;

        while (curr->next != nullptr) {
            ListNode* next = curr->next;

            bool isMax = curr->val > prev->val &&
                         curr->val > next->val;

            bool isMin = curr->val < prev->val &&
                         curr->val < next->val;

            if (isMax || isMin) {
                if (first == -1) {
                    first = index;
                } else {
                    minDist = min(minDist, index - prevCritical);
                }

                prevCritical = index;
            }

            prev = curr;
            curr = curr->next;
            index++;
        }

        if (first == -1 || first == prevCritical) {
            return {-1, -1};
        }

        return {
            minDist,
            prevCritical - first
        };
    }
};