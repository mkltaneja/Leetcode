
// Time = O(n)
// Space = O(1)

class Solution {
public:
    int areaOfMaxDiagonal(vector<vector<int>>& dimensions) 
    {
        int md = 0, ma = 0;
        for(vector<int> dim : dimensions)
        {
            int a = dim[0] * dim[1];
            int d2 = dim[0] * dim[0] + dim[1] * dim[1];
            
            if(d2 > md)
                md = d2, ma = a;
            else if(d2 == md)
                ma = max(ma, a);
        }
        
        return ma;
    }
};
