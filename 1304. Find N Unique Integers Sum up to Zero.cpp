class Solution {
public:
    vector<int> sumZero(int n) 
    {
        int st = -1*(n/2), end = n/2;
        vector<int> ans;
        while(st <= end)
        {
            if(st == 0 && (n&1^1))
                st++;
            else ans.push_back(st++);
        }

        return ans;
    }
};
