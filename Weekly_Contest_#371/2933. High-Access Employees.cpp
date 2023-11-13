class Solution {
public:
    vector<string> findHighAccessEmployees(vector<vector<string>>& access_times) 
    {
        unordered_map<string, vector<int>> mp;
        for(auto p : access_times)
            mp[p[0]].push_back(stoi(p[1]));
        
        int mx = 3;
        vector<string> ans;
        for(auto p : mp)
        {
            sort(p.second.begin(), p.second.end());
            int prev = -2000, cnt = 0, currMax = 0;
            for(int i = 0; i < p.second.size(); i++)
            {
                int curCnt = 0;
                for(int j = i; j < p.second.size(); j++)
                {
                    if((p.second[j] - p.second[i]) < 100)
                        curCnt++;
                    else break;
                }
                cnt = max(cnt, curCnt);
            }
            if(cnt >= mx)
                ans.push_back(p.first);
        }
        
        return ans;
    }
};
