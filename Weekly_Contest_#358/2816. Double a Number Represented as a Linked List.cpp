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
    
    int carry = 0;
    void iterate(ListNode* &head)
    {
        if(!head) return;
        
        iterate(head->next);
        int sum = 2*head->val + carry;
        carry = sum / 10;
        head->val = sum % 10;
    }
    
    ListNode* doubleIt(ListNode* head) 
    {
        iterate(head);
        if(carry)
        {
            ListNode* nhead = new ListNode(carry);
            nhead->next = head;
            return nhead;
        }
        return head;
    }
};
