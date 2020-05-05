// DAY 1(First Bad Version)=============================================================================
// O(log(n))
int binarysearch(unsigned int si, unsigned int ei)
{
    if (si == ei)
        return ei;
    unsigned int mid = (si + ei) / 2;
    // if(isBadVersion(mid) && !isBadVersion(mid-1))
    //     return mid;
    if (!isBadVersion(mid))
        return binarysearch(mid + 1, ei);
    else
        return binarysearch(si, mid);
}

int firstBadVersion(int n)
{
    return binarysearch(0, n);
}

// DAY 2()=============================================================================
//O(n^2)
int numJewelsInStones(string J, string S)
{
    int count = 0;
    for (int i = 0; i < J.size(); i++)
    {
        for (int j = 0; j < S.size(); j++)
        {
            if (S[j] == J[i])
                count++;
        }
    }
    return count;
}

////////////// OR //////////////
//O(n)
int numJewelsInStones(string J, string S)
{
    unordered_set<char> jewels;
    int ans = 0;

    for (char c : J)
        jewels.insert(c);
    for (char c : S)
        ans += jewels.count(c);

    return ans;
}

// DAY 3(Ransom Note)=============================================================================
// O(n^2)
bool canConstruct(string ransomNote, string magazine)
{
    int n = ransomNote.size();
    int m = magazine.size();
    if (m < n)
        return false;
    int k = 0;
    for (int i = 0; i < n; i++)
        for (int j = k; j < m; j++)
        {
            if (magazine[j] == ransomNote[i])
            {
                swap(magazine[j], magazine[k]);
                k++;
                break;
            }
            else if (j == m - 1)
                return false;
        }
    return true;
}

////////////OR////////////
// O(n)
bool canConstruct(string ransomNote, string magazine)
{
    int n = ransomNote.size();
    int m = magazine.size();
    if (m < n)
        return false;
    vector<int> count(26, 0);
    for (int i = 0; i < m; i++)
        count[magazine[i] - 'a']++;
    for (int i = 0; i < n; i++)
        if (--count[ransomNote[i] - 'a'] < 0)
            return false;
    return true;
}

// DAY 4()=============================================================================
// O(no. of bits)
int findComplement(int num)
{
    int bsize = 0;
    int n = num;
    while (n)
    {
        n >>= 1;
        bsize++;
    }
    int mask = 1;
    for (int i = 0; i < bsize; i++)
        num ^= (mask << i);
    return num;
}
// DAY 5(First Unique Character in a String)=============================================================================
// O(n)
int firstUniqChar(string s)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n = s.length();
    vector<int> count(26, 0);
    for (int i = 0; i < n; i++)
        count[s[i] - 'a']++;
    for (int i = 0; i < n; i++)
        if (count[s[i] - 'a'] == 1)
            return i;
    return -1;
}
