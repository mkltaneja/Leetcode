class Solution {
public:
    long long makeSimilar(vector<int>& nums, vector<int>& target) 
    {
        vector<int> o, e;
        for(int x : target)
        {
            if(x&1) o.push_back(x);
            else e.push_back(x);
        }
        sort(o.begin(), o.end());
        sort(e.begin(), e.end());
        sort(nums.begin(), nums.end());
        
        int i = 0, j = 0;
        long long ans = 0;
        for(int x : nums)
        {
            if(x&1)
                ans += abs(o[i++] - x)/2;
            else 
                ans += abs(e[j++] - x)/2;
        }
        
        return ans/2;
    }
};
