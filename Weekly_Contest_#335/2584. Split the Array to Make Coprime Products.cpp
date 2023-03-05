class Solution {
public:
    
    unordered_map<int,unordered_map<int,int>> mp;
    
    unordered_map<int,int> primes(int x)
    {
        unordered_map<int,int> ans;
        for(int j = 2; j*j <= x; j++)
        {
            if(x % j == 0)
            {
                int k = x / j;
                ans[j]++;
                while(x % j == 0)
                    x /= j;
                if(k != j)
                {
                    ans[k]++;
                    while(x % k == 0)
                        x /= k;
                }
            }
        }
        if(x != 1) ans[x]++;
        
        return ans;
    }
    int findValidSplit(vector<int>& nums) 
    {
        int n = nums.size();
        unordered_map<int,int> mp1, mp2;
        for(int i = n-1; i >= 0; i--)
        {
            int x = nums[i];
            
            unordered_map<int,int> tmp = mp.count(x)? mp[x] : primes(x);
            for(auto x : tmp)
                mp2[x.first] += x.second;
        }
        
        for(int i = 0; i < n-1; i++)
        {
            int x = nums[i];
            
            unordered_map<int,int> tmp = mp.count(x)? mp[x] : primes(x);
            for(auto x : tmp)
            {
                mp1[x.first] += x.second;
                mp2[x.first] -= x.second;
            }
            int exist = false;
            for(auto x : mp1)
            {
                if(mp2[x.first])
                {
                    exist = true;
                    break;
                }
            }
            
            if(!exist) return i;
        }
        
        return -1;
    }
};
