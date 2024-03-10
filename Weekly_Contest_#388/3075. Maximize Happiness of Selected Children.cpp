
// Time Complexity = O(n*logn + min(n, k))
// Space Complexity = O(1)

class Solution {
public:
    
    #define ll long long
    long long maximumHappinessSum(vector<int>& happiness, int k) 
    {
        sort(happiness.rbegin(), happiness.rend());
        int i = 0;
        ll ans = 0;
        while(i < happiness.size() && k--)
            ans += max(0, happiness[i] - i++);
        return ans;
    }
};
