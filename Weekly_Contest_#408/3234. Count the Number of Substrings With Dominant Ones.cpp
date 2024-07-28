
// Time Complexity = O(n)
// Space Complexity = O(n)

class Solution {
public:
    int numberOfSubstrings(string s)
    {
        int n = s.size();
        vector<int> pos;
        int ans = 0;
        for(int idx = 0; idx < n; idx++)
            if(s[idx] == '0')
                pos.push_back(idx);
        
        for(int i = n-1; i >= 0; i--)
        {
            if(pos.size() && pos.back() > i)
                pos.pop_back();
            int m = pos.size();
            if(m == 0)
            {
                ans += i + 1;
                continue;
            }
            ans += i - pos.back();
            for(int j = m-1; j >= 0; j--)
            {
                int zeros = m - j;
                if(zeros * zeros >= n)
                    break;
                int ones = (i - pos[j] + 1) - zeros;
                int need = max(0, zeros * zeros - ones);
                int nextIdx = j? pos[j-1] + 1 : 0;
                
                ans += max(0, (pos[j] - nextIdx + 1) - need);
            }
        }
        
        return ans;
    }
};
