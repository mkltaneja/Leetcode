
// APPROACH 1 (Storing indices in map and taking prefix sum)

// Time = O(n)
// Space = O(n)

class Solution {
public:
    
    #define ll long long
    ll NINF = -1e15;
    long long maximumSubarraySum(vector<int>& nums, int k) 
    {
        ll maxsum = NINF;
        int n = nums.size();
        unordered_map<int,int> mp;
        vector<ll> psum(n);
        for(int i = 0; i < n; i++)
            psum[i] = (ll)nums[i] + (i? psum[i-1] : 0);
        for(int i = 0; i < n; i++)
        {
            if(mp.count(nums[i] - k))
            {
                int pidx = mp[nums[i] - k];
                ll csum = psum[i] - (pidx? psum[pidx-1] : 0);
                maxsum = max(maxsum, csum);
            }
            if(mp.count(nums[i] + k))
            {
                int pidx = mp[nums[i] + k];
                ll csum = psum[i] - (pidx? psum[pidx-1] : 0);
                maxsum = max(maxsum, csum);
            }
            if(!mp.count(nums[i]))
                mp[nums[i]] = i;
            else
            {
                int pidx = mp[nums[i]];
                ll csum = psum[i-1] - (pidx? psum[pidx-1] : 0);
                if(csum < 0)
                    mp[nums[i]] = i;
            }
        }
        return maxsum == NINF? 0 : maxsum;
    }
};


// APPROACH 2 (Storing sums in the map)

// Time = O(n)
// Space = O(n)

class Solution {
public:
    
    #define ll long long
    long long maximumSubarraySum(vector<int>& nums, int k) 
    {
        int n = nums.size();
        unordered_map<int,ll> mp;
        ll sum = 0, maxSum = LLONG_MIN;
        for(int num : nums)
        {
            if(mp.count(num - k))
                maxSum = max(maxSum, sum + num - mp[num - k]);
            if(mp.count(num + k))
                maxSum = max(maxSum, sum + num - mp[num + k]);
            if(!mp.count(num))
                mp[num] = sum;
            else mp[num] = min(mp[num], sum);
            sum += num;
        }
        
        return maxSum == LLONG_MIN? 0 : maxSum;
    }
};
