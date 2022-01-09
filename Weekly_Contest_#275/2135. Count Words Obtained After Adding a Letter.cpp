
#define ull unsigned long long
int primes[26] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101};

int wordCount(vector<string> &startWords, vector<string> &targetWords)
{
    unordered_map<ull, int> m;
    for (string s : targetWords)
    {
        ull x = 1;
        for (char c : s)
            x *= primes[c - 'a'];
        m[x]++;
    }
    int ans = 0;
    for (string s : startWords)
    {
        ull x = 1;
        for (char c : s)
            x *= primes[c - 'a'];
        for (int i = 0; i < 26; i++)
        {
            ull y = x * (ull)primes[i];
            ans += m[y];
            m[y] = 0;
        }
    }

    return ans;
}