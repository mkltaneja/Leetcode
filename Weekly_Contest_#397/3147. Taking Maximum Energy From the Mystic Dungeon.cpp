
// Time Complexity = O(n)
// Time Complexity = O(n)

class Solution {
public:
    
    int maximumEnergy(vector<int>& energy, int k) 
    {
        int n = energy.size();
        vector<int> esum(n, 0);
        int ans = INT_MIN;
        for(int i = 0; i < n; i++)
        {
            esum[i] += energy[i] + (i-k >= 0? esum[i-k] : 0);
            esum[i] = max(esum[i], energy[i]);
            if(n-i <= k)
                ans = max(ans, esum[i]);
        }
        return ans;
    }
};
