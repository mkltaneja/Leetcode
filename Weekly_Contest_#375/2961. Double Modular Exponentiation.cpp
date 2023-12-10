
// Time Complexity = O(n*(loga + logb))
// Space Complexity = O(n)

class Solution {
public:
    
    int pow(int a, int b, int m)
    {
        int ans = 1;
        while(b)
        {
            if(b & 1)
                ans = (ans * a) % m;
            a = (a * a) % m;
            b >>= 1;
        }
        return ans;
    }
    
    vector<int> getGoodIndices(vector<vector<int>>& variables, int target) 
    {
        vector<int> ans;
        int i = 0;
        for(vector<int> &v : variables)
        {
            int a = v[0], b = v[1], c = v[2], m = v[3];
            
            int aa = pow(a, b, 10);
            aa = pow(aa, c, m);
            
            if(aa == target)
                ans.push_back(i);
            i++;
        }
        return ans;
    }
};
