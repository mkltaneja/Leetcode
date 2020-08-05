// Day 1 (Detect Capital)===========================================

bool detectCapitalUse(string word)
{
    int count = 0;
    for (char w : word)
        if (isupper(w))
            count++;
    return ((isupper(word[0]) && count == 1) || (count == word.size()) || count == 0);
}

// DAY 2 (Design Hashset)=============================

// 1st -> by taking bucketsize = 15000 and using "vector<vector>>"
class MyHashSet
{
    int numbuckets;
    vector<vector<int>> buckets;
    int hash_function(int key)
    {
        return key % numbuckets;
    }

public:
    /** Initialize your data structure here. */
    MyHashSet()
    {
        this->numbuckets = 15000;
        this->buckets = vector<vector<int>>(numbuckets, vector<int>{});
    }

    void add(int key)
    {
        int address = hash_function(key);
        if (find(buckets[address].begin(), buckets[address].end(), key) == buckets[address].end())
            buckets[address].push_back(key);
    }

    void remove(int key)
    {
        int address = hash_function(key);
        auto itr = find(buckets[address].begin(), buckets[address].end(), key);
        if (itr != buckets[address].end())
        {
            iter_swap(itr, buckets[address].end() - 1);
            buckets[address].pop_back();
        }
    }

    /** Returns true if this set contains the specified element */
    bool contains(int key)
    {
        int address = hash_function(key);
        return (find(buckets[address].begin(), buckets[address].end(), key) != buckets[address].end());
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */

//////////////////////////OR//////////////////////////////////////

// 2nd -> by using list  -->  finding is slow but insertion and deletion is fast
int numbuckets;
vector<list<int>> buckets;
int hash_function(int key)
{
    return key % numbuckets;
}

public:
/** Initialize your data structure here. */
MyHashSet()
{
    this->numbuckets = 15000;
    this->buckets.assign(numbuckets, list<int>());
}

void add(int key)
{
    int address = hash_function(key);
    if (find(buckets[address].begin(), buckets[address].end(), key) == buckets[address].end())
        buckets[address].push_back(key);
}

void remove(int key)
{
    int address = hash_function(key);
    auto itr = find(buckets[address].begin(), buckets[address].end(), key);
    if (itr != buckets[address].end())
        buckets[address].erase(itr);
}

/** Returns true if this set contains the specified element */
bool contains(int key)
{
    int address = hash_function(key);
    return (find(buckets[address].begin(), buckets[address].end(), key) != buckets[address].end());
}

////////////////////////////////OR/////////////////////////////

// 3rd -> by taking bucket size as 1  -->  time complexity increased to "10 times"
int numbuckets;
vector<list<int>> buckets;
int hash_function(int key)
{
    return key % numbuckets;
}

public:
/** Initialize your data structure here. */
MyHashSet()
{
    this->numbuckets = 15000;
    this->buckets.assign(numbuckets, list<int>());
}

void add(int key)
{
    int address = hash_function(key);
    if (find(buckets[address].begin(), buckets[address].end(), key) == buckets[address].end())
        buckets[address].push_back(key);
}

void remove(int key)
{
    int address = hash_function(key);
    auto itr = find(buckets[address].begin(), buckets[address].end(), key);
    if (itr != buckets[address].end())
        buckets[address].erase(itr);
}

/** Returns true if this set contains the specified element */
bool contains(int key)
{
    int address = hash_function(key);
    return (find(buckets[address].begin(), buckets[address].end(), key) != buckets[address].end());
}

// DAY 3 (Valid Palindrome)=========================================

// Method 1
bool isPalindrome(string s)
{
    string s1 = "";
    for (int i = 0; i < s.size(); i++)
    {
        s[i] = tolower(s[i]);
        if ((s[i] - 'a' >= 0 && s[i] - 'a' < 26) || (s[i] - '0' >= 0 && s[i] - '0' < 10))
            s1 += s[i];
    }
    // cout<<s1<<endl;
    for (int i = 0; i < s1.size() / 2; i++)
        if (s1[i] != s1[s1.size() - i - 1])
            return false;
    return true;
}

/////////////////////OR/////////////////////////

// Method 2
bool isPalindrome(string s)
{
    string s1 = "";
    for (int i = 0; i < s.size(); i++)
    {
        s[i] = tolower(s[i]);
        if (isalnum(s[i]))
            s1 += s[i];
    }
    // cout<<s1<<endl;
    for (int i = 0; i < s1.size() / 2; i++)
        if (s1[i] != s1[s1.size() - i - 1])
            return false;
    return true;
}

/////////////////////////////OR////////////////////////////////

// Method 3 -> without extra space
bool isPalindrome(string s)
{
    int l = 0, r = s.size() - 1;
    while (l < r)
    {
        if (isalnum(s[l]) && isalnum(s[r]))
        {
            if (tolower(s[l]) == tolower(s[r]))
                l++, r--;
            else
                return false;
        }
        else
        {
            if (!isalnum(s[l]))
                l++;
            if (!isalnum(s[r]))
                r--;
        }
    }
    return true;
}

// DAY 4 (Power of 4)==============================================

// Method 1 (loop)
bool isPowerOfFour(int num)
{
    if ((num <= 0) || (num & (num - 1)))
        return false;
    int count = 0;
    while (num != 1)
    {
        count++;
        num >>= 1;
    }
    return !(count % 2);
}

////////////////////////////////OR///////////////////////////////

// Method 2 (one - liner)
bool isPowerOfFour(int num)
{
    return num > 0 && !(num & (num - 1)) && (num & 0x55555555);
}

// DAY 5 (Add and Search Word - Data structure design)======================================================================

// Method 1 (Search by indices)
class WordDictionary
{
public:
    vector<WordDictionary *> wd;
    bool wordEnd;
    /** Initialize your data structure here. */
    WordDictionary()
    {
        this->wd.assign(26, nullptr);
        this->wordEnd = false;
    }

    /** Adds a word into the data structure. */
    void addWord(string word)
    {
        WordDictionary *curr = this;
        for (char c : word)
        {
            if (!curr->wd[c - 'a'])
                curr->wd[c - 'a'] = new WordDictionary;
            curr = curr->wd[c - 'a'];
        }
        curr->wordEnd = true;
    }

    /** Returns if the word is in the data structure. A word could contain the dot character '.' to represent any one letter. */

    bool search2(string &word, int idx, WordDictionary *curr)
    {
        for (int i = idx; i < word.size(); i++)
        {
            if (word[i] == '.')
            {
                for (WordDictionary *ch : curr->wd)
                    if (ch && search2(word, i + 1, ch))
                        return true;
                return false;
            }
            else
            {
                if (!curr->wd[word[i] - 'a'])
                    return false;
                curr = curr->wd[word[i] - 'a'];
            }
        }
        return curr->wordEnd;
    }

    bool search(string word)
    {
        return search2(word, 0, this);
    }
};

// OR -> change in search part (by substring)//////////////////////////////////////////////////

bool search(string word)
{
    WordDictionary *curr = this;
    for (int i = 0; i < word.size(); i++)
    {
        if (word[i] == '.')
        {
            for (WordDictionary *ch : curr->wd)
                if (ch && ch->search(word.substr(i + 1)))
                    return true;
            return false;
        }
        else
        {
            if (!curr->wd[word[i] - 'a'])
                return false;
            curr = curr->wd[word[i] - 'a'];
        }
    }
    return curr->wordEnd;
}
/**
 * Your WordDictionary object will be instantiated and called as such:
 * WordDictionary* obj = new WordDictionary();
 * obj->addWord(word);
 * bool param_2 = obj->search(word);
 */