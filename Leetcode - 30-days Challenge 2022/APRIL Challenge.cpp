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
