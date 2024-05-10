
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

// DAY 7 (2816. Double a Number Represented as a Linked List)=======================================================================

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

ListNode* doubleIt(ListNode* head) 
{
    ListNode* newHead = reverseList(head);
    ListNode* itr = newHead, *prev = nullptr;
    int carry = 0;
    while(itr)
    {
        int sum = itr->val*2 + carry;
        int currVal = sum % 10;
        carry = sum / 10;
        itr->val = currVal;
        prev = itr;
        itr = itr->next;
    }
    if(carry && prev)
        prev->next = new ListNode(carry);

    head = reverseList(newHead);

    return head;
}

// DAY 8 (506. Relative Ranks)==========================================================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

vector<string> findRelativeRanks(vector<int>& score) 
{
    vector<int> scoreSorted = score;
    unordered_map<int,int> posInSorted;
    vector<string> place;
    sort(scoreSorted.rbegin(), scoreSorted.rend());
    for(int idx = 0; idx < scoreSorted.size(); idx++)
        posInSorted[scoreSorted[idx]] = idx+1;
    for(int currScore : score)
    {
        if(posInSorted[currScore] == 1)
            place.emplace_back("Gold Medal");
        else if(posInSorted[currScore] == 2)
            place.emplace_back("Silver Medal");
        else if(posInSorted[currScore] == 3)
            place.emplace_back("Bronze Medal");
        else place.emplace_back(to_string(posInSorted[currScore]));
    }
    return place;
}

// DAY 9 (3075. Maximize Happiness of Selected Children)==================================================================

// Time Complexity = O(n*logn + n)
// Space Complexity = O(1)

long long maximumHappinessSum(vector<int>& happiness, int k) 
{
    int n = happiness.size();
    long long maxScore = 0;
    sort(happiness.begin(), happiness.end(), greater<int>());
    for(int i = 0; i < k && i < n; i++)
        maxScore += max(0, happiness[i] - i);
    return maxScore;
}

// DAY 10 (786. K-th Smallest Prime Fraction)=============================================================================

// APPROACH 1 (Brute Force -> Comparing all pairs)

// Time Complexity = O(n^2 + n*logn)
// Space Complexity = O(n^2)

#define f first
#define s second
vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) 
{
    int size = arr.size();
    vector<pair<double, pair<int,int>>> fractions;
    for(int idx1 = 0; idx1 < size; idx1++)
        for(int idx2 = idx1+1; idx2 < size; idx2++)
            fractions.push_back({1.0 * arr[idx1] / arr[idx2], {arr[idx1], arr[idx2]}});
    sort(fractions.begin(), fractions.end());

    return {fractions[k-1].s.f, fractions[k-1].s.s};
}

// APPROACH 2 (Binary Search) --> [OPTIMIZED]

// Time Complexity = O(n*log(n))
// Space Complexity = O(1)

vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k) 
{
    double lo = 0, hi = 1;
    int size = arr.size();
    while(lo <= hi)
    {
        double mid = (lo + hi) / 2;
        int count = 0, num = 0, den = 0;
        double maxFrac = 0;
        for(int idx1 = 0, idx2 = 1; idx1 < size; idx1++)
        {
            while(idx2 < size && 1.0*arr[idx1]/arr[idx2] > mid) 
                idx2++;
            count += size - idx2;
            if(idx2 < size && 1.0*arr[idx1]/arr[idx2] > maxFrac)
            {
                maxFrac = 1.0*arr[idx1]/arr[idx2];
                num = arr[idx1];
                den = arr[idx2];
            }
        }
        if(count == k)
            return {num, den};
        if(count < k)
            lo = mid;
        else hi = mid;
    }
    return {-1, -1};
}
