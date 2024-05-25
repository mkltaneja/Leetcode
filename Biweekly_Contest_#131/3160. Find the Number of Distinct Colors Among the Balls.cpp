
// Time Complexity = O(q)
// Space Complexity = O(q)

class Solution {
public:
    vector<int> queryResults(int limit, vector<vector<int>>& queries) 
    {
        vector<int> ans;
        unordered_map<int,int> cnt, clrCode;
        for(vector<int> &q : queries)
        {
            int ball = q[0], clr = q[1];
            if(clrCode.count(ball))
            {
                if(--cnt[clrCode[ball]] == 0)
                    cnt.erase(clrCode[ball]);
            }
            cnt[clr]++;
            clrCode[ball] = clr;
            ans.push_back(cnt.size());
        }
        return ans;
    }
};
