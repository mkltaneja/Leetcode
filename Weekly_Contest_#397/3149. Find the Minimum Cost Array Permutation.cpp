
// Time Complexity = O(2^n * (n + logn))
// Space Complexity = O(2^n * n)

class Solution {
public:
    
    vector<int> nums;
    int n;
    int minScore = INT_MAX;
    vector<int> minPerm;
    
    void dfs(int vis, int score, vector<int> &currPerm)
    {
        if(__builtin_popcount(vis) == n)
        {
            score += abs(nums[currPerm[0]] - currPerm.back());
            if(score < minScore)
            {
                minScore = score;
                minPerm = currPerm;
            }
            return;
        }
        for(int i = 0; i < n; i++)
        {
            if(vis & (1 << i)) continue;
            
            int newScore = score + (currPerm.empty()? 0 : abs(nums[i] - currPerm.back()));
            if(newScore >= minScore)
                continue;
            
            currPerm.push_back(i);
            dfs(vis | (1 << i), newScore, currPerm);
            currPerm.pop_back();
        }
    }
    
    vector<int> findPermutation(vector<int>& nums) 
    {
        n = nums.size();
        this->nums = nums;
        vector<int> currPerm;
        dfs(0, 0, currPerm);
        
        return minPerm;
    }
};
