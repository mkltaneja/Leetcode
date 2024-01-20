// Time Complexity = O(n*logn)
// Space Complexity = O(n)

class Solution {
public:
    bool canSortArray(vector<int>& nums) 
    {
        int n = nums.size();
        vector<int> bc(n);
        int i = 0;
        for(int x : nums)
            bc[i++] = __builtin_popcount(x);
        i = 0;
        while(i < n)
        {
            int j = i;
            while(j < n && bc[j] == bc[i]) j++;
            sort(nums.begin()+i, nums.begin()+j);
            i = j;
        }
        
        for(int i = 1; i < n; i++)
            if(nums[i] < nums[i-1])
                return false;
        
        return true;
    }
};
