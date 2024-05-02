
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
