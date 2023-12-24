
// Time = O(n^2), Space = O(n^2)

class Solution {
public:
    
    #define ll long long
    int MOD = 1e9 + 7;
    int maximizeSquareArea(int m, int n, vector<int>& hFences, vector<int>& vFences) 
    {
        sort(hFences.begin(), hFences.end());
        sort(vFences.begin(), vFences.end());
        vector<int> h, v;
        int p = 1;
        for(int hh : hFences)
        {
            h.push_back(hh - p);
            p = hh;
        }
        h.push_back(m - p);
        
        p = 1;
        for(int vv : vFences)
        {
            v.push_back(vv - p);
            p = vv;
        }
        v.push_back(n - p);
        
        if(v.size() < h.size())
            h.swap(v);
        
        ll ans = -1;
        unordered_set<int> st1, st2;
        for(int i = 0; i < h.size(); i++)
        {
            int sum = 0;
            for(int j = i; j < h.size(); j++)
            {
                sum += h[j];
                st1.insert(sum);
            }
        }
        for(int i = 0; i < v.size(); i++)
        {
            int sum = 0;
            for(int j = i; j < v.size(); j++)
            {
                sum += v[j];
                if(st1.count(sum))
                    ans = max(ans, (ll)sum);
            }
        }
        return ans == -1? ans : ans % MOD * ans % MOD % MOD;
    }
};
