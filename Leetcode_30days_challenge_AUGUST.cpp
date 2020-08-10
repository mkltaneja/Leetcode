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

// DAY 6 (Find All Duplicates in an Array)=====================================================

// O(n) time and O(n) space
vector<int> findDuplicates(vector<int>& nums) 
{
    unordered_map<int,int> m;
    for(int i : nums)
        m[i]++;
    vector<int> ans;
    for(auto itr : m)
        if(itr.second > 1)
            ans.push_back(itr.first);
    return ans;
}

/////////////////////////////OR/////////////////////////

// O(nlogn) time and O(n) space
vector<int> findDuplicates(vector<int>& nums) 
{
    ios::sync_with_stdio(false); cin.tie(0);
    
    vector<int> ans;
    set<int> s;
    for(int i : nums)
    {
        if(s.find(i) == s.end())
            s.insert(i);
        else
            ans.push_back(i);
    }
    return ans;
}

//////////////////////////OR/////////////////////////

// O(nlogn) time and O(1) space
vector<int> findDuplicates(vector<int>& nums) 
{
    sort(nums.begin(), nums.end());
    
    vector<int> ans;
    for(int i=1;i<nums.size();i++)
    {
        if(nums[i-1] == nums[i])
            ans.push_back(nums[i++]);
    }
    return ans;
}

////////////////////////////OR//////////////////////

// O(n) time and O(1) space
vector<int> findDuplicates(vector<int>& nums) 
{
    vector<int> ans;
    for(int ele : nums)
    {
        if(nums[abs(ele)-1] < 0)
        {
            ans.push_back(abs(ele));
            continue;
        }
        nums[abs(ele)-1] *= -1;
    }
    return ans;
}

// DAY 7 (Vertical Order Traversal of a Binary Tree)==============================================================

static bool sortby_vlhld(const pair<int,pair<int,int>> &a, const pair<int,pair<int,int>> &b)
{
    if(a.second.second == b.second.second)
    {
        if(a.second.first == b.second.first)
            return a.first < b.first;
        return a.second.first < b.second.first;
    }
    return a.second.second < b.second.second;
}

void preorder_append(vector<pair<int,pair<int,int>>> &vpp, TreeNode* node, int hl, int vl)
{
    if(node == nullptr)
        return;
    vpp.push_back({node->val,{hl,vl}});
    preorder_append(vpp, node->left, hl+1, vl-1);
    preorder_append(vpp, node->right, hl+1, vl+1);
}

vector<vector<int>> verticalTraversal(TreeNode* root) 
{
    if(root == nullptr)
        return {};
    vector<pair<int,pair<int,int>>> vpp;
    preorder_append(vpp,root,0,0);
    // for(auto p : vpp)
    //     cout<<p.first<<" "<<p.second.first<<" "<<p.second.second<<endl;
    sort(vpp.begin(), vpp.end(), sortby_vlhld);
    // for(auto p : vpp)
    //     cout<<p.first<<" "<<p.second.first<<" "<<p.second.second<<endl;
    
    vector<vector<int>> ans;
    for(int i=0;i<vpp.size();i++)
    {
        vector<int> temp;
        int j = i;
        int vl = vpp[i].second.second;
        
        while(j < vpp.size() && vl == vpp[j].second.second)
            temp.push_back(vpp[j++].first);
        
        ans.push_back(temp);
        i = j-1;
    }
    return ans;
}

// DAY 8 (Path Sum 3)=================================================================

int nodesum(TreeNode* node, int sum, int &count)
{
    if(sum == 0)
        count++;
    // cout<<count<<" --> "<<sum<<" - "<<node->val<<",  ";
    if(node->left)
        nodesum(node->left, sum - node->left->val, count);
    if(node->right)
        nodesum(node->right, sum - node->right->val, count);
    // cout<<endl;
    return count;
}

int preorder_sum(TreeNode* node, int sum, int &count)
{
    if(node == nullptr)
        return 0;
    int total = 0;
    // cout<<node->val<<": \n";
    nodesum(node, sum-node->val, total);
    count += total;
    // cout<<count<<endl;
    preorder_sum(node->left, sum, count);
    preorder_sum(node->right, sum, count);
    return count;
}

int pathSum(TreeNode* root, int sum) 
{
    int count = 0;
    preorder_sum(root, sum, count);
    return count;
}

///////////////////////////////////////////OR/////////////////////////////////

// less complex
int rootsum(TreeNode* node, int sum)
{
    if(node == nullptr)
        return 0;
    int count = 0;
    if(node->val == sum)
        count++;
    count += rootsum(node->left, sum-node->val);
    count += rootsum(node->right, sum-node->val);
    return count;
}

int pathSum(TreeNode* root, int sum) 
{
    if(root == nullptr)
        return 0;
    return rootsum(root, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);    
}

// DAY 9 (Rotten Oranges)=======================================

int orangesRotting(vector<vector<int>>& grid) 
{
    int n = grid.size();
    int m = grid[0].size();
    
    queue<pair<int,int>> que;
    
    bool f = false;
    for(int i = 0 ; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(grid[i][j] == 1)
                f = true;
            else if(grid[i][j] == 2)
                que.push({i,j});
        }
    }
    if(!f)
        return 0;
    
    vector<vector<int>> dir = {{1,0},{0,1},{-1,0},{0,-1}};
    
    int time = 0;
    while(!que.empty())
    {
        int sz = que.size();
        while(sz--)
        {
            pair<int,int> tp = que.front();
            que.pop();
            // cout<<tp.first<<" "<<tp.second<<endl;
            for(int d=0;d<4;d++)
            {
                int r = tp.first + dir[d][0];
                int c = tp.second + dir[d][1];
                if(r >= 0 && c >= 0 && r < n && c < m && grid[r][c] == 1)
                {
                    grid[r][c] = 2;
                    que.push({r,c});
                }
            }
        }
        if(!que.empty())
            time++;
    }
    for(vector<int> v : grid)
        for(int i : v)
            if(i == 1)
            {
                f = false;
                break;
            }
    return time == 0 || !f ? -1 : time;
}

// DAY 10 (Excel Sheet Column Number)===========================================================

uint64_t pow(uint64_t n, int x)
{
    uint64_t ans = 1;
    while(x)
    {
        if(x & 1)
            ans *= n;
        n *= n;
        x >>= 1;
    }
    return ans;
}

int titleToNumber(string s) 
{
    int col = 0;
    for(int i = 0 ; i < s.size(); ++i)
    {
        int r = s.size() - i - 1;
        int idx = s[i] - 'A' + 1;
        col += pow(26,r)*idx;
    }
    return col;
}