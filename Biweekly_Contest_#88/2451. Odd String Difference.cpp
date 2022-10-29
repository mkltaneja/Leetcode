class Solution {
public:
    string oddString(vector<string>& words) 
    {
        int n = words.size(), m = words[0].size();
        unordered_map<string,pair<int,int>> mp;
        for(int i = 0; i < n; i++)
        {
            string tmp = "";
            for(int j = 1; j < m; j++)
                tmp += to_string(words[i][j]-words[i][j-1])+",";
            mp[tmp] = {mp[tmp].first+1, i};
        }
        for(auto p : mp)
            if(p.second.first == 1)
                return words[p.second.second];
        return "";
    }
};
