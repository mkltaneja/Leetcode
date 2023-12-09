class Solution {
public:
    int removeAlmostEqualCharacters(string word) 
    {
        int i = 0, n = word.size(), ans = 0;
        while(i < n)
        {
            int j = i+1;
            while(j < n && abs(word[j] - word[j-1]) <= 1)
                j++;
            ans += (j-i) / 2;
            i = j;
        }
        return ans;
    }
};
