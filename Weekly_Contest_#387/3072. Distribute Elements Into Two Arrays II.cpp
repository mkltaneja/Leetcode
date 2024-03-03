
// Time Complexity = O(n * log(mx) + n)
// Space Complexity = O(mx + 2*n)

class Solution {
public:

    int OFFSET = 1e9 + 7;
    class Ftree
    {
        int n;
        unordered_map<int,int> mp;
        public:
        Ftree(int n)
        {
            this->n = n;
        }
        
        int get(int x)
        {
            int ans = 0;
            while(x <= n)
            {
                ans += mp[x];
                x += x & -x;
            }
            return ans;
        }
        void add(int x)
        {
            x--;
            while(x)
            {
                mp[x]++;
                x -= x & -x;
            }
        }
    };
    
    vector<int> resultArray(vector<int>& nums) 
    {
        int n = nums.size();
        int mx = *max_element(nums.begin(), nums.end()) + 5;
        Ftree ft1(mx);
        Ftree ft2(mx);
        vector<int> arr1, arr2, res;
        arr1.push_back(nums[0]);
        arr2.push_back(nums[1]);
        ft1.add(nums[0]);
        ft2.add(nums[1]);
        
        for(int i = 2; i < n; i++)
        {
            int g1 = ft1.get(nums[i]);
            int g2 = ft2.get(nums[i]);
            
            if(g1 > g2)
            {
                arr1.push_back(nums[i]);
                ft1.add(nums[i]);
            }
            else if(g1 < g2)
            {
                arr2.push_back(nums[i]);
                ft2.add(nums[i]);
            }
            else if(arr2.size() < arr1.size())
            {
                arr2.push_back(nums[i]);
                ft2.add(nums[i]);
            }
            else 
            {
                arr1.push_back(nums[i]);
                ft1.add(nums[i]);
            }
        }
        
        res.insert(res.end(), arr1.begin(), arr1.end());
        res.insert(res.end(), arr2.begin(), arr2.end());
        
        return res;
    }
};
