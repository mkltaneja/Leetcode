
// APPROACH 1 (Using max to store elements, and sort to find max 2) --> time = O(>n + n*logn)

class Solution {
public:
    int maxSum(vector<int>& nums) 
    {
        unordered_map<int,vector<int>> mp;
        for(int x : nums)
        {
            int tmp = x;
            int y = 0;
            while(x)
            {
                y = max(y, x%10);
                x /= 10;
            }
            mp[y].push_back(tmp);
        }
        
        int ans = -1;
        for(auto p : mp)
        {
            if(p.second.size() < 2) continue;
            sort(p.second.begin(), p.second.end());
            ans = max(ans, p.second.back() + p.second[p.second.size()-2]);
        }
        
        return ans;
    }
};

// APPROACH 2 (Using Array to store max 2 and taking sum along with it) --> time = O(n) --> [OPTIMIZED]

class Solution {
public:
    int maxSum(vector<int>& nums) 
    {
        int n = nums.size();
        int ans = -1;
        vector<vector<int>> topMax(10, vector<int> (2, 0));
        for(int i = 0; i < n; i++)
        {
            int mx = 0, x = nums[i];
            while(x)
            {
                mx = max(mx, x % 10);
                x /= 10;
            }
            
            if(nums[i] >= topMax[mx][0])
            {
                topMax[mx][1] = topMax[mx][0];
                topMax[mx][0] = nums[i];
            }
            else
                topMax[mx][1] = max(topMax[mx][1], nums[i]);
            
            if(topMax[mx][0] && topMax[mx][1])
                ans = max(ans, topMax[mx][0] + topMax[mx][1]);
        }
        
        return ans;
    }
};
