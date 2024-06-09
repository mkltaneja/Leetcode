
// Time Complexity = O(n*logn + n + mx)
// Space Complexity = O(200000)

class Solution {
public:
    int maxTotalReward(vector<int>& rewardValues)
    {
        int n = rewardValues.size();
        sort(rewardValues.begin(), rewardValues.end());
        int maxAns = 0;
        int mx = rewardValues[n-1];
        bitset<100000> sums;
        bitset<100000> mask;
        sums.set(0);
        int prevSum = 0;
        
        for(int reward : rewardValues)
        {
            while(prevSum < reward)
                mask.set(prevSum++);
            sums |= (sums & mask) << reward;
        }
        
        for(int ans = 2*mx-1; ans >= 1; ans--)
            if(sums.test(ans))
                return ans;
        
        return 0;
    }
};
