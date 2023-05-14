class Solution {
public:
    bool doesValidArrayExist(vector<int>& derived) 
    {
        int n = derived.size();
        vector<int> ans(n);
        ans[0] = 1;
        for(int i = 1; i < n; i++)
            ans[i] = (ans[i-1] ^ derived[i-1]);
        return (ans[n-1] ^ ans[0]) == derived[n-1];
    }
};
