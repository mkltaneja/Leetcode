
// DAY 1 (557. Reverse Words in a String III)=========================================================================

string reverseWords(string s) 
{
    string ans = "", prev = "";
    for(int i = 0; i <= s.size(); i++)
    {
        if(i == s.size() || s[i] == ' ')
        {
            reverse(prev.begin(), prev.end());
            ans += prev + (i != s.size()? " " : "");
            prev = "";
        }
        else prev += s[i];
    }

    return ans;
}

// DAY 2 (2038. Remove Colored Pieces if Both Neighbors are the Same Color)============================================================

bool winnerOfGame(string colors) 
{
    int As = 0, Bs = 0, Aturns = 0, Bturns = 0;
    for(char c : colors)
    {
        if(c == 'A')
        {
            As++;
            Bturns += max(0, Bs-2);
            Bs = 0;
        }
        else
        {
            Bs++;
            Aturns += max(0, As-2);
            As = 0;
        }
    }
    Aturns += max(0, As-2);
    Bturns += max(0, Bs-2);

    bool AliceWon = Aturns > Bturns;

    return AliceWon;
}

// DAY 3 (1512. Number of Good Pairs)=====================================================================================

int numIdenticalPairs(vector<int>& nums) 
{
    int ans = 0;
    unordered_map<int,int> mp;
    for(int x : nums)
        mp[x]++;
    for(auto p : mp)
        ans += p.second * (p.second - 1) / 2;

    return ans;
}
