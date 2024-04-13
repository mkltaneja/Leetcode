
// Time Complexity = O(n + n^2)
// Space Complexity = O(n)

class Solution {
public:
    
    #define ll long long
    long long numberOfSubarrays(vector<int>& nums) 
    {
        int n = nums.size();
        map<int, vector<int>> posMap;
        for(int i = 0; i < n; i++)
            posMap[-nums[i]].emplace_back(i);
        
        ll ans = 0;
        vector<int> hrdl = {-2};
        for(auto p : posMap)
        {
            int x = -p.first;
            vector<int> pos = p.second;
            
            vector<int> hrdl2;
            int j = 0;
            ll curr = 0;
            
            for(int i = 0, j = 0; i <= hrdl.size(); i++)
            {
                ll curr = 0;
                while(j < pos.size() && (i == hrdl.size() || pos[j] < hrdl[i]))
                {
                    curr++;
                    hrdl2.emplace_back(pos[j++]);
                }
                if(i != hrdl.size())
                    hrdl2.emplace_back(hrdl[i]);
                ans += (curr * (curr + 1)) / 2;
            }
            hrdl = hrdl2;
            posMap.erase(x);
        }
        return ans;
    }
};
