
// Time Complexity = O(n*32 + n*logn*32)
// Space Complexity = O(n*32)

class Solution {
public:
    int minimumDifference(vector<int>& nums, int k) 
    {
        int n = nums.size();
        vector<vector<int>> bc(n+1, vector<int>(32, 0));
        int ans = INT_MAX;
        for(int i = 0; i < n; i++)
        {
            int x = nums[i];
            bc[i+1] = bc[i];
            for(int j = 0; j < 32; j++)
                if(x & (1 << j))
                    bc[i+1][j]++;
        }
        
        for(int i = 0; i < n; i++)
        {
            int x = nums[i];
            
            int lo = i, hi = n-1;
            while(lo <= hi)
            {
                int mid = (lo + hi) / 2;
                int y = 0;
                for(int j = 0; j < 32; j++)
                {
                    int bits = bc[mid+1][j] - bc[i+1][j];
                    if(bits == mid - i)
                        y |= (1 << j);
                }
                int z = x & y;
                if(z == k)
                    return 0;
                if(z < k)
                    hi = mid - 1;
                else lo = mid + 1;
                
                ans = min(ans, abs(z - k));
            }
        }
        
        return ans;
    }
};
