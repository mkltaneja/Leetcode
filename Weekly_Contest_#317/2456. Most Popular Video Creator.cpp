class Solution {
public:
    #define f first
    #define s second
    vector<vector<string>> mostPopularCreator(vector<string>& creators, vector<string>& ids, vector<int>& views) 
    {
        unordered_map<string,pair<long,int>> mp;
        for(int i = 0; i < creators.size(); i++)
        {
            int maxv = i;
            if(mp.count(creators[i]))
            {
                int x = mp[creators[i]].s;
                if(views[x] > views[maxv])
                    maxv = x;
                else if(views[x] == views[maxv])
                    maxv = ids[i] < ids[x]? i : x;
            }
            mp[creators[i]] = {(long)mp[creators[i]].f + views[i], maxv};
        }
        
        vector<vector<string>> ans;
        long mx = -1;
        for(auto p : mp)
        {
            if(p.s.f > mx)
            {
                ans.clear();
                ans.push_back({p.f, ids[p.s.s]});
                mx = p.s.f;
            }
            else if(p.s.f == mx) ans.push_back({p.f, ids[p.s.s]});
        }
        
        return ans;
    }
};
