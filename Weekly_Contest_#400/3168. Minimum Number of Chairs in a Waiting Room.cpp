
// Time Complexity = O(n)
// Space Complexity = O(1)

class Solution {
public:
    int minimumChairs(string s) 
    {
        int cnt = 0, maxCnt = 0;
        for(char c : s)
        {
            if(c == 'E') cnt++;
            else cnt--;
            maxCnt = max(maxCnt, cnt);
        }
        
        return maxCnt;
    }
};
