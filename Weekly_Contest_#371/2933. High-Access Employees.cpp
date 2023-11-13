
// METHOD 1 (Pushing numbers in the stoi() form) --> Time = O(n + n^2), Space = O(2*n)

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

// METHOD 2 (Pushing numbers in the minute form instead of stoi(), also utilizing the sort() method) --> Time = O(2*n), Space = O(2*n)

class Solution {
public:
    vector<string> findHighAccessEmployees(vector<vector<string>>& access_times) 
    {
        unordered_map<string, vector<int>> mp;
        for(auto p : access_times)
            mp[p[0]].push_back((((p[1][0] - '0') * 10 + (p[1][1] - '0')) * 60) + ((p[1][2] - '0') * 10 + (p[1][3] - '0')));
        
        vector<string> ans;
        for(auto &p : mp)
        {
            sort(p.second.begin(), p.second.end());
            for(int i = 2; i < p.second.size(); i++)
            {
                if((p.second[i] - p.second[i-2]) < 60)
                {
                    ans.push_back(p.first);
                    break;
                }
            }
        }
        
        return ans;
    }
};
