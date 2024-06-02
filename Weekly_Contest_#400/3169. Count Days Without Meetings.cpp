
// Time Complexity = O(n*logn + n)
// Space Complexity = O(1)

class Solution {
public:
    int countDays(int days, vector<vector<int>>& meetings) 
    {
        sort(meetings.begin(), meetings.end());
        int cnt = 0, prevEnd = 0;
        for(vector<int> m : meetings)
        {
            if(m[0] > prevEnd)
                cnt += max(0, m[0] - prevEnd - 1);
            prevEnd = max(prevEnd, m[1]);
        }
        cnt += max(0, days - prevEnd);
        return cnt;
    }
};
