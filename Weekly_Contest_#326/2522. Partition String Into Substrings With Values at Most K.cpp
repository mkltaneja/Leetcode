class Solution {
public:
    
    int minimumPartition(string s, int k) 
    {
        int i = 0;
        int n = s.size();
        int ans = 0;
        while(i < n)
        {
            long j = i, x = 0;
            while(j < n && (x*10 + (s[j]-'0')) <= k)
            {
                x = x*10 + (s[j++]-'0');
            }
            if(j == i) return -1;
            ans++;
            i = j;
        }
        return ans;
    }
};
