class Solution {
public:
    
    #define ll long long
    #define f first
    #define s second
    vector<vector<int>> substringXorQueries(string s, vector<vector<int>>& queries) 
    {
        int n = s.size();
        unordered_map<int,pair<int,int>> fo;
        for(int i = 0; i < n; i++)
        {
            if(s[i] == '0')
            {
                if(!fo.count(0))
                    fo[0] = {i,i};
                continue;
            }
            for(ll x = 0, j = i; x <= INT_MAX && j < n; j++)
            {
                x = (x << 1) | (s[j]-'0');
                if(!fo.count(x)) fo[x] = {i,j};
            }
        }
        
        vector<vector<int>> ans;
        for(vector<int> &q : queries)
        {
            int x = q[0] ^ q[1];
            if(!fo.count(x)) 
            {
                ans.push_back({-1, -1});
                continue;
            }
            auto p = fo[x];
            ans.push_back({p.first, p.second});
        }
        
        return ans;
    }
};
