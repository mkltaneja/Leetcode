
// Time = O(n^3), Space = O(1)

class Solution {
public:
    int incremovableSubarrayCount(vector<int>& nums) 
    {
        int n = nums.size();
        int ans = 0;
        for(int i = 0; i < n; i++)
        {
            for(int j = i; j < n; j++)
            {
                vector<int> tmp(nums.begin(), nums.begin()+i);
                tmp.insert(tmp.end(), nums.begin()+j+1, nums.end());
                int p = -1, fl = 1;
                for(int x : tmp)
                {
                    if(x <= p)
                    {
                        fl = 0;
                        break;
                    }
                    p = x;
                }
                if(fl) ans++;
            }
        }
        
        return ans;
    }
};
