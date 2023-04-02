class Solution {
public:
    
    #define ll long long
    long long makeSubKSumEqual(vector<int>& arr, int k) 
    {
        int n = arr.size();
        vector<int> vis(n,0);
        ll ops = 0;
        for(int i = 0; i < n; i++)
        {
            if(vis[i]) continue;
            vector<ll> tmp;
            for(int j = i; !vis[j]; j = (j + k) % n)
            {
                tmp.push_back(arr[j]);
                vis[j] = 1;
            }
            sort(tmp.begin(), tmp.end());
            ll med = tmp[tmp.size()/2];
            for(ll x : tmp)
                ops += abs(x - med);
        }
        
        return ops;
    }
};
