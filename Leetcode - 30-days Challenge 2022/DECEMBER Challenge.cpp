// DAY 1 (1704. Determine if String Halves Are Alike)===============================================================================

bool halvesAreAlike(string s) 
{
    int n = s.size();

    auto isVowel = [&](char c)
    {
        c = tolower(c);
        return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
    };

    int cnt = 0;
    for(int i = 0, j = n/2; j < n; i++, j++)
    {
        if(isVowel(s[i])) cnt++;
        if(isVowel(s[j])) cnt--;
    }
    return cnt == 0;
}

// DAY 2 (1657. Determine if Two Strings Are Close)==========================================================================

bool closeStrings(string word1, string word2) 
{
    vector<int> map1(26), map2(26);
    for(char &c : word1)
        map1[c-'a']++;
    for(char &c : word2)
        map2[c-'a']++;

    vector<int> unique1, unique2;
    for(int i = 0; i < 26; i++)
        if(map1[i])
            unique1.push_back(i);
    for(int i = 0; i < 26; i++)
        if(map2[i])
            unique2.push_back(i);

    sort(map1.begin(), map1.end());
    sort(map2.begin(), map2.end());

    return (unique1 == unique2) && (map1 == map2);
}

// DAY 3 (451. Sort Characters By Frequency)=====================================================================================

string frequencySort(string s) 
{
    unordered_map<char,int> mp;
    vector<pair<int,char>> map;
    for(char &c : s)
        mp[c]++;
    for(auto &p : mp)
        map.push_back({p.second, p.first});
    sort(map.rbegin(), map.rend());

    string ans = "";
    for(int i = 0; i < map.size(); i++)
        while(map[i].first--)
            ans += map[i].second;

    return ans;
}

// DAY (2256. Minimum Average Difference)========================================================================================

int minimumAverageDifference(vector<int>& nums) 
{
    int n = nums.size();
    long lsum = 0, rsum = 0, mn = INT_MAX;
    for(int x : nums)
        lsum += x;

    int ans = -1;
    for(int i = n-1; i >= 0; i--)
    {
        long ravg = i != n-1? (rsum / (n-i-1)) : 0;
        long lavg = lsum / (i+1);
        rsum += nums[i];
        lsum -= nums[i];

        long curr = abs(lavg - ravg);
        if(curr <= mn)
        {
            mn = curr;
            ans = i;
        }
    }

    return ans;
}

// DAY 5 (876. Middle of the Linked List)==================================================================================

ListNode* middleNode(ListNode* head) 
{
    ListNode* mid = head, *fast = head;
    while(fast && fast->next)
    {
        mid = mid->next;
        fast = fast->next->next;
    }

    return mid;
}

// DAY 6 (328. Odd Even Linked List)====================================================================================

ListNode* oddEvenList(ListNode* head) 
{
    if(!head || !head->next) return head;

    ListNode* oddHead = head, *evenHead = head->next;
    ListNode *odd = oddHead, *even = evenHead;
    while(odd->next && even->next)
    {
        odd->next = odd->next->next;
        odd = odd->next;
        even->next = even->next->next;
        even = even->next;
    }
    odd->next = evenHead;

    return head;
}
