// DAY 1 (Distribute Candies)=============================================================

// METHOD 1 (Using Set) --> O(n*logn)
int distributeCandies(vector<int> &candyType)
{
    int n = candyType.size();
    unordered_set<int> s;
    for (int x : candyType)
        s.insert(x);
    return (s.size() < n / 2) ? s.size() : n / 2;
}

// METHOD 2 (Using Bitset) --> O(n)

int distributeCandies(vector<int> &candyType)
{
    int n = candyType.size();
    bitset<200005> f;
    for (int x : candyType)
        f.set(x + 100000);
    int count = f.count();
    // cout<<count<<endl;
    return (count < n / 2) ? count : n / 2;
}