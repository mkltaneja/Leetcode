// DAY 1 (344. Reverse String)=================================================================================================

void reverseString(vector<char>& s) 
{
    reverse(s.begin(), s.end());
}

// DAY 2 (680. Valid Palindrome II)=================================================================================================

bool ispal(string &s, int i, int j)
{
    while(i <= j && s[i] == s[j]) i++, j--;

    return i > j;
}

bool validPalindrome(string s) 
{
    int i = 0, j = s.size()-1;
    while(i <= j)
    {
        if(s[i] != s[j])
            return ispal(s, i+1, j) || ispal(s, i, j-1);
        i++, j--;
    }
    return true;
}

// DAY 3 (31. Next Permutation)=================================================================================================

void nextPermutation(vector<int>& nums) {
    next_permutation(nums.begin(), nums.end());
}

// DAY 4 (1721. Swapping Nodes in a Linked List)=================================================================================================

ListNode* swapNodes(ListNode* head, int k) 
{
    int n = 0;
    ListNode* itr = head;
    while(itr)
    {
        itr = itr->next;
        n++;
    }
    int kk = n-k;
    ListNode* itr1 = head, *itr2 = head;
    while(--k)
        itr1 = itr1->next;
    while(kk--)
        itr2 = itr2->next;

    swap(itr1->val, itr2->val);

    return head;
}

// DAY 5 (11. Container With Most Water)=================================================================================================

int maxArea(vector<int>& height) 
{
    int i = 0, j = height.size()-1;
    int ans = 0;
    while(i < j)
    {
        ans = max(ans, (height[i] < height[j])? height[i] * (j - i++)
                                             : height[j] * (j-- - i));
    }
    return ans;
}

// DAY 6 (923. 3Sum With Multiplicity)=================================================================================================

#define f first
#define s second
int threeSumMulti(vector<int>& arr, int target) 
{
    int n = arr.size();
    long ans = 0;
    int mod = 1e9 + 7;
    unordered_map<int,long> mp;
    for(int i = 0; i < n; i++)
        mp[arr[i]]++;

    for(auto p1 : mp)
    {
        for(auto p2 : mp)
        {
            int x = target - p1.f - p2.f;
            if(!mp.count(x)) continue;

            if(p1.f == p2.f && p2.f == x)
                ans += p1.s * (p1.s - 1) * (p1.s - 2) / 6;
            else if(p1.f == p2.f)
                ans += mp[x] * p1.s * (p1.s - 1) / 2;
            else if(p1.f < p2.f && p2.f < x)
                ans += mp[x] * p1.s * p2.s;
        }
    }

    return ans % mod;
}

// DAY 7 (1046. Last Stone Weight)=================================================================================================

int lastStoneWeight(vector<int>& stones) 
{
    priority_queue<int> pq;
    for(int x : stones)
        pq.push(x);
    while(pq.size() > 1)
    {
        int x = pq.top();
        pq.pop();
        int y = pq.top();
        pq.pop();
        if(x > y) pq.push(x-y);
        else if(y > x) pq.push(y-x);
    }
    return pq.empty()? 0 : pq.top();
}

// DAY 8 (347. Top K Frequent Elements)=================================================================================================

vector<int> topKFrequent(vector<int>& nums, int k) 
{
    unordered_map<int,int> mp;
    for(int x : nums)
        mp[x]++;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    for(auto p : mp)
    {
        pq.push({p.second, p.first});
        if(pq.size() > k)
            pq.pop();
    }

    vector<int> ans;
    while(!pq.empty())
    {
        ans.push_back(pq.top().second);
        pq.pop();
    }

    return ans;
}

// DAY 9 (682. Baseball Game)=================================================================================================

int calPoints(vector<string>& ops) 
{
    int ans = 0;
    stack<int> st;
    for(string s : ops)
    {
        if(s[0] == '-' || (s[0] >= '1' && s[0] <= '9'))
            st.push(stoi(s));
        else if(s == "+")
        {
            int a = st.top();
            st.pop();
            int b = st.top();
            st.pop();
            st.push(b);
            st.push(a);
            st.push(a + b);
        }
        else if(s == "D")
        {
            int x = st.top();
            x *= 2;
            st.push(x);
        }
        else st.pop();
    }
    while(!st.empty())
    {
        ans += st.top();
        st.pop();
    }

    return ans;
}
