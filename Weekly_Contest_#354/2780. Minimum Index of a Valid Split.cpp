
// APPROACH 1 (Using Priority Queue and map to store dominant count at every step --> Generic Approach) --> Time = O(2*n*logn), Space = O(6*n)

class Solution {
public:
    int minimumIndex(vector<int>& nums) 
    {
        int n = nums.size();
        vector<int> dom1(n), dom2(n);
        priority_queue<pair<int,int>> pq;
        unordered_map<int,int> mp;
        priority_queue<pair<int,int>> pq1;
        unordered_map<int,int> mp1;
        
        for(int i = 0; i < n; i++)
        {
            mp[nums[i]]++;
            pq.push({mp[nums[i]], nums[i]});
            if(pq.top().first * 2 > (i+1))
                dom1[i] = pq.top().second;
        }
        
        int ans = -1;
        for(int i = n-1; i >= 0; i--)
        {
            mp1[nums[i]]++;
            pq1.push({mp1[nums[i]], nums[i]});
            if(pq1.top().first * 2 > (n-i))
                dom2[i] = pq1.top().second;
            
            if(i == 0 || dom1[i-1] == 0 || dom2[i] == 0) continue;
            ans = dom1[i-1] == dom2[i]? i - 1 : ans;
        }
        
        return ans;
    }
};

// APPROACH 2 (Using the fact that overall one element is dominant) --> Time = O(4*n), Space = O(2*n) [OPTIMIZED]

class Solution {
public:
    int minimumIndex(vector<int>& nums) 
    {
        int n = nums.size();
        unordered_map<int,int> mp;
        for(int x : nums)
            mp[x]++;
        pair<int,int> mx = {-1,-1};
        for(auto [x, y] : mp)
            mx = max(mx, {y, x});
        int dom = mx.second;
        
        vector<int> psum(n, 0);
        for(int i = 0; i < n; i++)
        {
            psum[i] = ((nums[i] == dom)? 1 : -1) + (i? psum[i-1] : 0);
        }
        
        for(int i = 0; i < n-1; i++)
            if(psum[i] > 0 && (psum[n-1] - psum[i]) > 0)
                return i;
        
        return -1;
    }
};
