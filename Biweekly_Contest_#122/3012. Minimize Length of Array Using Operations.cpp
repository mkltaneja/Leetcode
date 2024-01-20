// APPROACH 1

// Time Complexity = O(n)
// Space Complexity = O(n)

class Solution {
public:
    int minimumArrayLength(vector<int>& nums) 
    {
        int mn = INT_MAX;
        int n = nums.size();
        unordered_map<int,int> mp, mp2;
        for(int x : nums)
        {
            mn = min(mn, x);
            mp[x]++;
        }
        for(int x : nums)
            if(x != mn)
                mp2[x % mn]++;
        
        if(mp[mn] == 1 || mp2[0] != n-mp[mn])
            return 1;
        return (mp[mn] + 1)/2;
    }
};

// APPROACH 2

// Time Complexity = O(n*logn)
// Space Complexity = O(1)

class Solution {
public:
    int minimumArrayLength(vector<int>& nums) 
    {
        int gcd = 0, cnt = 0, ans = 0;
        for(int x : nums)
            gcd = __gcd(gcd, x);
        for(int x : nums)
            cnt += gcd == x;
        
        ans = (max(cnt, 1) + 1) / 2;
        
        return ans;
    }
};

// [1,4,3,1]
// [5,5,5,10,5]
// [2,3,4]
// [5,5,5,5,5,5]
// [10,10,10,15,15,15]
// [5,2,2,2,9,10]
