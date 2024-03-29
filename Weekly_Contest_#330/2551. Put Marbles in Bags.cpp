class Solution {
public:
    long long putMarbles(vector<int>& weights, int k)
    {
        int n = weights.size();
        vector<int> alts(n-1);
        for(int i = 0; i < n-1; i++)
            alts[i] = weights[i] + weights[i+1];
        sort(alts.begin(), alts.end());
        
        long long diff = 0;
        for(int i = 0; i < k-1; i++)
            diff += alts[n-2 - i] - alts[i];
        
        return diff;
    }
};
