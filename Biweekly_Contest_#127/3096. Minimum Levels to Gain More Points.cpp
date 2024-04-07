
// Time Complexity = O(n)
// Space Complexity = O(1)

class Solution {
public:
    int minimumLevels(vector<int>& possible) 
    {
        int n = possible.size();
        int total = 0, curr = 0, rounds = 0;
        for(int x : possible)
            total += x? 1 : -1;
        for(int i = 0; i < n-1; i++)
        {
            int x = possible[i];
            curr += x? 1 : -1;
            rounds++;
            if(curr > total - curr)
                return rounds;
        }
        return -1;
    }
};
