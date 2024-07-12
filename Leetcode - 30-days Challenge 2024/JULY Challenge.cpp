
// DAY 1 (1550. Three Consecutive Odds)=========================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

bool threeConsecutiveOdds(vector<int>& arr)
{
    int size = arr.size();
    for(int idx = 0; idx < size-2; idx++)
        if((arr[idx] & 1) && (arr[idx+1] & 1) && (arr[idx+2] & 1))
            return true;
    return false;
}

// DAY 2 (350. Intersection of Two Arrays II)====================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

vector<int> intersect(vector<int>& nums1, vector<int>& nums2)
{
    vector<int> ans;
    unordered_map<int,int> nums1Map;
    for(int num : nums1)
        nums1Map[num]++;
    for(int num : nums2)
        if(nums1Map[num]-- > 0)
            ans.push_back(num);
    return ans;
}

// DAY 3 (1509. Minimum Difference Between Largest and Smallest Value in Three Moves)===========================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int minDifference(vector<int>& nums)
{
    if(nums.size() <= 4)
        return 0;
    int min1 = INT_MAX, min2 = INT_MAX, min3 = INT_MAX, min4 = INT_MAX;
    int max1 = INT_MIN, max2 = INT_MIN, max3 = INT_MIN, max4 = INT_MIN;
    for(int num : nums)
    {
        if(num >= max1)
        {
            max4 = max3;
            max3 = max2;
            max2 = max1;
            max1 = num;
        }
        else if(num >= max2)
        {
            max4 = max3;
            max3 = max2;
            max2 = num;
        }
        else if(num >= max3)
        {
            max4 = max3;
            max3 = num;
        }
        else if(num >= max4)
            max4 = num;
        
        if(num <= min1)
        {
            min4 = min3;
            min3 = min2;
            min2 = min1;
            min1 = num;
        }
        else if(num <= min2)
        {
            min4 = min3;
            min3 = min2;
            min2 = num;
        }
        else if(num <= min3)
        {
            min4 = min3;
            min3 = num;
        }
        else if(num <= min4)
            min4 = num;
    }
    return min({max1 - min4, max2 - min3, max3 - min2, max4 - min1});
}

// DAY 4 (2181. Merge Nodes in Between Zeros)=======================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

ListNode* mergeNodes(ListNode* head)
{
    ListNode* newHead = new ListNode(-1);
    ListNode* itr1 = head, *itr2 = newHead;
    int currSum = 0;
    while(itr1)
    {
        currSum += itr1->val;
        if(itr1->val == 0)
        {
            if(currSum)
            {
                itr2->next = new ListNode(currSum);
                itr2 = itr2->next;
            }
            currSum = 0;
        }
        itr1 = itr1->next;
    }
    return newHead->next;
}

// DAY 5 (2058. Find the Minimum and Maximum Number of Nodes Between Critical Points)=======================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

vector<int> nodesBetweenCriticalPoints(ListNode* head)
{
    int idx = 1, prevCriticalIdx = -1, a = -1;
    vector<int> dist(2);
    dist[0] = INT_MAX, dist[1] = INT_MIN;
    ListNode* itr = head->next, *prev = head;
    while(itr->next)
    {
        if((prev->val < itr->val && itr->next->val < itr->val) || (prev->val > itr->val && itr->next->val > itr->val))
        {
            if(prevCriticalIdx != -1)
            {
                dist[0] = min(dist[0], idx - prevCriticalIdx);
                dist[1] = idx - a;
            }
            else a = idx;
            prevCriticalIdx = idx;
        }
        prev = itr;
        itr = itr->next;
        idx++;
    }
    return dist[0] == INT_MAX? vector<int>(2, -1) : dist;
}

// DAY 6 (2582. Pass the Pillow)=============================================================================================

// Time Complexity = O(1)
// Space Complexity = O(1)

int passThePillow(int n, int time)
{
    int dir = int(ceil(1.0 * time / (n-1))) & 1;
    int index = (time % (n-1));
    if(index == 0)
        dir = (time / (n-1)) & 1? 0 : 1;
    return dir? (1 + index) : (n - index);
}

// DAY 7 (1518. Water Bottles)==========================================================================================

// Time Complexity = O(log[numExchange](numBottles))
// Space Complexity = O(1)

int numWaterBottles(int numBottles, int numExchange)
{
    int bottlesDrunk = 0, emptyBottles = 0;
    while(numBottles)
    {
        bottlesDrunk += numBottles;
        int currBottles = numBottles;
        numBottles = (currBottles + emptyBottles) / numExchange;
        emptyBottles = (currBottles + emptyBottles) % numExchange;
    }
    return bottlesDrunk;
}

// DAY 8 (1823. Find the Winner of the Circular Game)===========================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int getWinnerIndex(int n, int k)
{
    if(n == 1) return 0;
    return (getWinnerIndex(n-1, k) + k) % n;
}

int findTheWinner(int n, int k)
{
    return getWinnerIndex(n, k) + 1;
}

// DAY 9 (1701. Average Waiting Time)========================================================================================

// Time Complexity = O(n)
// Time Complexity = O(1)

double averageWaitingTime(vector<vector<int>>& customers)
{
    int totalCustomers = customers.size();
    long totalWaitingTime = 0, lastEndingTime = 0;
    for(vector<int> customer : customers)
    {
        long arrivalTime = customer[0];
        long time = customer[1];
        long currentWaitingTime = max(0l, lastEndingTime - arrivalTime) + time;
        lastEndingTime = arrivalTime + currentWaitingTime;
        totalWaitingTime += currentWaitingTime;
    }
    return 1.0 * totalWaitingTime / totalCustomers;
}

// DAY 10 (1598. Crawler Log Folder)==========================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int minOperations(vector<string>& logs)
{
    int distanceFromRoot = 0;
    for(string log : logs)
    {
        if(log == "../")
            distanceFromRoot = max(distanceFromRoot - 1, 0);
        else if(log[0] != '.')
            distanceFromRoot++;
    }
    return distanceFromRoot;
}

// DAY 11 (1190. Reverse Substrings Between Each Pair of Parentheses)=============================================================

// APPROACH 1 (Naive way)

// Time Complexity = O(n^2)
// Space Complexity = O(n)

string reverseParentheses(string s)
{
    string ans = "";
    stack<int> st;
    for(char c : s)
    {
        if(c == '(')
            st.push(ans.size());
        else if(c == ')')
        {
            int startIdx = st.top();
            st.pop();
            reverse(ans.begin() + startIdx, ans.end());
        }
        else ans += c;
    }
    return ans;
}

// APPROACH 2 (Wormhole Teleportation Technique) --> [OPTIMIZED[

// Time Complexity = O(n)
// Space Complexity = O(n)

string reverseParentheses(string s)
{
    int n = s.size();
    string ans = "";
    stack<int> st;
    vector<int> bracePair(n);
    for(int idx = 0; idx < n; idx++)
    {
        if(s[idx] == '(')
            st.push(idx);
        else if(s[idx] == ')')
        {
            int pairIdx = st.top();
            st.pop();
            bracePair[pairIdx] = idx;
            bracePair[idx] = pairIdx;
        }
    }

    for(int idx = 0, dir = 1; idx < n; idx += dir)
    {
        if(s[idx] == '(' || s[idx] == ')')
        {
            idx = bracePair[idx];
            dir *= -1;
        }
        else ans += s[idx];
    }
    return ans;
}

// WEEK 2 (1836. Remove Duplicates From an Unsorted Linked List)====================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

ListNode* deleteDuplicatesUnsorted(ListNode* head)
{
    unordered_map<int,int> freqMap;
    ListNode* itr = head;
    while(itr)
    {
        freqMap[itr->val]++;
        itr = itr->next;
    }

    itr = head;
    ListNode* prev = nullptr;
    while(itr)
    {
        if(freqMap[itr->val] > 1)
        {
            if(prev)
                prev->next = itr->next;
            else head = head->next;
        }
        else prev = itr;
        itr = itr->next;
    }
    return head;
}

// DAY 12 (1717. Maximum Score From Removing Substrings)===================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int getValue(stack<char> &st, int val)
{
    if(st.empty()) return 0;

    int cnt1 = 0, cnt2 = 0;
    char ch2 = st.top();
    while(!st.empty() && st.top() == ch2)
    {
        cnt2++;
        st.pop();
    }
    if(st.empty()) return 0;

    char ch1 = st.top();
    while(!st.empty() && st.top() == ch1)
    {
        cnt1++;
        st.pop();
    }

    return min(cnt1, cnt2) * val;
}

int maximumGain(string s, int x, int y)
{
    int ans = 0;
    stack<char> st;
    for(char c : s)
    {
        if(c == 'a' || c == 'b')
        {
            int xx = x, yy = y;
            char ch = 'b';
            if(c == 'b')
            {
                swap(xx, yy);
                ch = 'a';
            }
            if(yy > xx && !st.empty() && st.top() == ch)
            {
                ans += yy;
                st.pop();
            }
            else st.push(c);
        }
        else ans += getValue(st, min(x, y));
    }
    ans += getValue(st, min(x, y));

    return ans;
}
