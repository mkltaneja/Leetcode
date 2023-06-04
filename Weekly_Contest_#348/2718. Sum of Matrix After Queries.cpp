class Solution {
public:
    
    #define ll long long
    long long matrixSumQueries(int n, vector<vector<int>>& queries) 
    {
        ll sum = 0;
        unordered_set<int> row, col;
        for(int i = queries.size()-1; i >= 0; i--)
        {
            int type = queries[i][0];
            int index = queries[i][1];
            ll val = queries[i][2];
            
            if(type == 0)
            {
                if(row.count(index)) continue;
                row.insert(index);
                sum += (ll)(n - col.size()) * val;
            }
            else
            {
                if(col.count(index)) continue;
                col.insert(index);
                sum += (ll)(n - row.size()) * val;
            }
        }
        
        return sum;
    }
};
