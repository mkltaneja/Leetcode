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