class Solution {
public:
    vector<int> cycleLengthQueries(int n, vector<vector<int>>& queries) 
    {
        vector<int> ans;
        for(auto &q : queries)
        {
            int a = q[0];
            int b = q[1];
            int da = log2(a);
            int db = log2(b);
            
            if(db > da)
            {
                swap(da, db);
                swap(a, b);
            }
            
            int tmpd = da;
            while(tmpd > db)
            {
                a >>= 1;
                tmpd--;
            }
            
            while(a != b)
            {
                a >>= 1;
                b >>= 1;
            }
            
            int dp = log2(a);
            
            ans.push_back((da - dp) + (db - dp) + 1);
        }
        
        return ans;
    }
};
