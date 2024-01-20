// Time Complexity = O(n*logn)
// Space Complexity = O(n)

class Solution {
public:
    
    #define ll long long
    long long minimumCost(vector<int>& nums, int k, int dist) 
    {
        int n = nums.size();
        multiset<ll> mains, extra;
        ll sum = 0, ans = LLONG_MAX;
        for(int i = 1; i < n; i++)
        {
            mains.insert(nums[i]);
            sum += nums[i];
            if(mains.size() >= k)
            {
                auto itr = mains.end();
                itr--;
                sum -= *itr;
                extra.insert(*itr);
                mains.erase(itr);
            }
            
            if(i - dist > 0)
            {
                ans = min(ans, sum);
                
                int remNum = nums[i-dist];
                auto itr1 = mains.find(remNum);
                if(itr1 != mains.end())
                {
                    sum -= remNum;
                    mains.erase(itr1);
                    if(extra.empty()) continue;
                    auto itr2 = extra.begin();
                    sum += *itr2;
                    mains.insert(*itr2);
                    extra.erase(itr2);
                }
                else
                    extra.erase(extra.find(remNum));                
            }
        }
        
        return ans + nums[0];
    }
};
