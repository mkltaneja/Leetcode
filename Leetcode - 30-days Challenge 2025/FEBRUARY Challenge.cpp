
// DAY 1 (3151. Special Array I)==========================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

bool isArraySpecial(vector<int>& nums) {
    for(int idx = 0; idx < nums.size()-1; idx++) {
        if((nums[idx] + nums[idx+1]) & 1 ^ 1) {
            return false;
        }
    }
    return true;
}
