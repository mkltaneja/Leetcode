class Solution {
public:
    long long minimumMoney(vector<vector<int>>& transactions) 
    {
        int n = transactions.size();
        long long mincost = 0;
        for(vector<int> &v : transactions)
            if(v[0] > v[1])
                mincost += (v[0] - v[1]);
        long long money = 0;
        for(vector<int> &v : transactions)
        {
            if(v[0] > v[1])
                money = max(money, mincost - (v[0] - v[1]) + v[0]);
            else money = max(money, mincost + v[0]);
        }
        
        return money;
    }
};
