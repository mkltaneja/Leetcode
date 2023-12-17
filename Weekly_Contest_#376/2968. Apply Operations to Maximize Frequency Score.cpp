
// Time = O(n), Space = O(n)

class Solution {
public:

    #define ll long long

    ll findCost(int left, int right, vector<int> &nums, vector<ll> &preSum)
    {
        int medIdx = (right + left) >> 1;
        int median = nums[medIdx];
        ll leftCount = medIdx - left + 1;
        ll rightCount = right - medIdx;
        ll leftSum = preSum[medIdx] - (left? preSum[left-1] : 0);
        ll rightSum = preSum[right] - preSum[medIdx];

        ll cost = (leftCount * median - leftSum) + (rightSum - rightCount * median);
        return cost;
    }

    int maxFrequencyScore(vector<int>& nums, long long k) 
    {
        int size = nums.size();
        sort(nums.begin(), nums.end());
        vector<ll> preSum(size);
        for(int idx = 0; idx < size; idx++)
            preSum[idx] = nums[idx] + (idx? preSum[idx-1] : 0);

        int left = 0, right = 0;
        int maxLen = 0;
        while(right < size)
        {
            ll cost = findCost(left, right, nums, preSum);
            if(cost <= k)
                maxLen = max(maxLen, right - left + 1);
            else left++;
            right++;
        }
        return maxLen;
    }
};
