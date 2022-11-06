class Solution {
public:
    
    #define f first
    #define s second
    #define ll long long
    long long totalCost(vector<int>& costs, int k, int candidates) 
    {
        int n = costs.size();
        priority_queue<pair<int,pair<int,int>>, vector<pair<int,pair<int,int>>>, greater<pair<int,pair<int,int>>>> pq;
        for(int i = 0; i < candidates; i++)
            pq.push({costs[i], {i,1}});
        for(int i = n-1; n-i <= candidates && i >= candidates; i--)
            pq.push({costs[i], {i,2}});
        
        int i = candidates, j = n-candidates-1;
        ll ans = 0;
        while(k--)
        {
            ans += (ll)pq.top().f;
            int x = pq.top().s.s;
            pq.pop();
            if(x == 1)
            {
                if(i <= j)
                    pq.push({costs[i], {i++, 1}});
            }
            else
            {
                if(i <= j)
                    pq.push({costs[j], {j--, 2}});
            }
        }
        
        return ans;
    }
};
