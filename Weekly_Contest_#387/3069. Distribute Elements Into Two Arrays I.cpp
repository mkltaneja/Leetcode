
// Time Complexity = O(2*n)
// Space Complexity = O(2*n)

class Solution {
public:
    vector<int> resultArray(vector<int>& nums) 
    {
        int n = nums.size();
        vector<int> arr1, arr2, res;
        arr1.push_back(nums[0]);
        arr2.push_back(nums[1]);
        for(int i = 2; i < n; i++)
        {
            if(arr1.back() > arr2.back())
                arr1.push_back(nums[i]);
            else
                arr2.push_back(nums[i]);
        }
        res.insert(res.end(), arr1.begin(), arr1.end());
        res.insert(res.end(), arr2.begin(), arr2.end());
        
        return res;
    }
};
