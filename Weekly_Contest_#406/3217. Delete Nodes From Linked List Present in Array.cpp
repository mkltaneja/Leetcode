
// Time Complexity = O(n)
// Space Complexity = O(n)

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
    ListNode* modifiedList(vector<int>& nums, ListNode* head)
    {
        unordered_set<int> st;
        for(int x : nums)
            st.insert(x);
        ListNode* itr = head, *prev = nullptr;
        while(itr)
        {
            if(st.count(itr->val))
            {
                if(prev)
                    prev->next = itr->next;
                else head = itr->next;
            }
            else 
                prev = itr;
            itr = itr->next;
        }
        return head;
    }
};
