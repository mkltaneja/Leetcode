
// DAY 1 (2000. Reverse Prefix of Word)=======================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

string reversePrefix(string word, char ch) 
{
    int size = word.size();
    string ans = "";
    bool found = false;
    for(int partIdx = 0; partIdx < size; partIdx++)
    {
        ans += word[partIdx];
        if(word[partIdx] == ch && !found)
        {
            reverse(ans.begin(), ans.end());
            found = true;
        }
    }

    return ans;
}

// DAY 2 (2441. Largest Positive Integer That Exists With Its Negative)===================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int findMaxK(vector<int>& nums) 
{
    unordered_set<int> numSet;
    int ans = -1;
    for(int num : nums)
    {
        if(numSet.count(-num))
            ans = max(ans, abs(num));
        numSet.insert(num);
    }
    return ans;
}

// DAY 3 (165. Compare Version Numbers)=================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int compareVersion(string version1, string version2) 
{
    int idx1 = 0, idx2 = 0;
    int size1 = version1.size(), size2 = version2.size();
    while(idx1 < size1 || idx2 < size2)
    {
        int num1 = 0, num2 = 0;
        while(idx1 < size1 && version1[idx1] != '.')
            num1 = num1*10 + (version1[idx1++]-'0');
        while(idx2 < size2 && version2[idx2] != '.')
            num2 = num2*10 + (version2[idx2++]-'0');
        
        if(num1 > num2)
            return 1;
        if(num2 > num1)
            return -1;
        
        idx1++, idx2++;
    }

    return 0;
}

// DAY 4 (881. Boats to Save People)=====================================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(1)

int numRescueBoats(vector<int>& people, int limit) 
{
    int size = people.size();
    sort(people.begin(), people.end());
    int start = 0, end = size-1;
    int minBoats = 0;
    while(start <= end)
    {
        if(people[start] + people[end] <= limit)
            start++, end--;
        else end--;
        minBoats++;
    }
    return minBoats;
}

// DAY 5 (237. Delete Node in a Linked List)======================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

void deleteNode(ListNode* node) 
{
    if(!node) return;
    ListNode* prevNode = nullptr;
    while(node->next)
    {
        node->val = node->next->val;
        prevNode = node;
        node = node->next;
    }
    assert(prevNode != nullptr);

    prevNode->next = nullptr;
}

// DAY 6 (2487. Remove Nodes From Linked List)====================================================================================

// APPROACH 1 (Using deque to compare values)

// Time Complexity = O(n)
// Space Complexity = O(n)

ListNode* removeNodes(ListNode* head) 
{
    vector<ListNode*> deque;
    ListNode* itr = head;
    ListNode* res = new ListNode(-1);
    while(itr)
    {
        while(!deque.empty() && deque.back()->val < itr->val)
            deque.pop_back();
        deque.push_back(itr);
        itr = itr->next;
    }
    itr = res;
    for(ListNode* node : deque)
    {
        itr->next = node;
        itr = itr->next;
    }

    return res->next;
}

// APPROACH 2 (Without additional space - reversing the list) --> [OPTIMIZED]

// Time Complexity = O(n)
// Space Complexity = O(1)

ListNode* reverseList(ListNode* head)
{
    ListNode* curr = head, *prev = nullptr;
    while(curr)
    {
        ListNode* next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    return prev;
}

ListNode* removeNodes(ListNode* head) 
{
    ListNode* newHead = reverseList(head);
    ListNode* itr = newHead;
    while(itr)
    {
        while(itr->next && itr->next->val < itr->val)
            itr->next = itr->next->next;
        itr = itr->next;
    }
    head = reverseList(newHead);
    return head;
}
