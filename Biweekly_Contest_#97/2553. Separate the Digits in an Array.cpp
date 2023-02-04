class Solution {
public:
    vector<int> separateDigits(vector<int>& nums) 
    {
        vector<int> ans;
        for(int x : nums)
        {
            int y = x;
            vector<int> tmp;
            while(y)
            {
                tmp.push_back(y%10);
                y /= 10;
            }
            reverse(tmp.begin(), tmp.end());
            for(int z : tmp)
                ans.push_back(z);
        }
        
        return ans;
    }
};
