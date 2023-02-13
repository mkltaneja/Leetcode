class Solution {
public:
    
    #define ll long long
    long long findTheArrayConcVal(vector<int>& nums) 
    {
        ll ans = 0;
        int i = 0, j = nums.size()-1;
        while(i < j)
            ans += stoll(to_string(nums[i++]) + to_string(nums[j--]));
        if(i == j) ans += nums[i];
        
        return ans;
    }
};
