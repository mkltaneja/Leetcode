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
vector<int> findDuplicates(vector<int> &nums)
{
    unordered_map<int, int> m;
    for (int i : nums)
        m[i]++;
    vector<int> ans;
    for (auto itr : m)
        if (itr.second > 1)
            ans.push_back(itr.first);
    return ans;
}

/////////////////////////////OR/////////////////////////

// O(nlogn) time and O(n) space
vector<int> findDuplicates(vector<int> &nums)
{
    ios::sync_with_stdio(false);
    cin.tie(0);

    vector<int> ans;
    set<int> s;
    for (int i : nums)
    {
        if (s.find(i) == s.end())
            s.insert(i);
        else
            ans.push_back(i);
    }
    return ans;
}

//////////////////////////OR/////////////////////////

// O(nlogn) time and O(1) space
vector<int> findDuplicates(vector<int> &nums)
{
    sort(nums.begin(), nums.end());

    vector<int> ans;
    for (int i = 1; i < nums.size(); i++)
    {
        if (nums[i - 1] == nums[i])
            ans.push_back(nums[i++]);
    }
    return ans;
}

////////////////////////////OR//////////////////////

// O(n) time and O(1) space
vector<int> findDuplicates(vector<int> &nums)
{
    vector<int> ans;
    for (int ele : nums)
    {
        if (nums[abs(ele) - 1] < 0)
        {
            ans.push_back(abs(ele));
            continue;
        }
        nums[abs(ele) - 1] *= -1;
    }
    return ans;
}

// DAY 7 (Vertical Order Traversal of a Binary Tree)==============================================================

static bool sortby_vlhld(const pair<int, pair<int, int>> &a, const pair<int, pair<int, int>> &b)
{
    if (a.second.second == b.second.second)
    {
        if (a.second.first == b.second.first)
            return a.first < b.first;
        return a.second.first < b.second.first;
    }
    return a.second.second < b.second.second;
}

void preorder_append(vector<pair<int, pair<int, int>>> &vpp, TreeNode *node, int hl, int vl)
{
    if (node == nullptr)
        return;
    vpp.push_back({node->val, {hl, vl}});
    preorder_append(vpp, node->left, hl + 1, vl - 1);
    preorder_append(vpp, node->right, hl + 1, vl + 1);
}

vector<vector<int>> verticalTraversal(TreeNode *root)
{
    if (root == nullptr)
        return {};
    vector<pair<int, pair<int, int>>> vpp;
    preorder_append(vpp, root, 0, 0);
    // for(auto p : vpp)
    //     cout<<p.first<<" "<<p.second.first<<" "<<p.second.second<<endl;
    sort(vpp.begin(), vpp.end(), sortby_vlhld);
    // for(auto p : vpp)
    //     cout<<p.first<<" "<<p.second.first<<" "<<p.second.second<<endl;

    vector<vector<int>> ans;
    for (int i = 0; i < vpp.size(); i++)
    {
        vector<int> temp;
        int j = i;
        int vl = vpp[i].second.second;

        while (j < vpp.size() && vl == vpp[j].second.second)
            temp.push_back(vpp[j++].first);

        ans.push_back(temp);
        i = j - 1;
    }
    return ans;
}

// DAY 8 (Path Sum 3)=================================================================

int nodesum(TreeNode *node, int sum, int &count)
{
    if (sum == 0)
        count++;
    // cout<<count<<" --> "<<sum<<" - "<<node->val<<",  ";
    if (node->left)
        nodesum(node->left, sum - node->left->val, count);
    if (node->right)
        nodesum(node->right, sum - node->right->val, count);
    // cout<<endl;
    return count;
}

int preorder_sum(TreeNode *node, int sum, int &count)
{
    if (node == nullptr)
        return 0;
    int total = 0;
    // cout<<node->val<<": \n";
    nodesum(node, sum - node->val, total);
    count += total;
    // cout<<count<<endl;
    preorder_sum(node->left, sum, count);
    preorder_sum(node->right, sum, count);
    return count;
}

int pathSum(TreeNode *root, int sum)
{
    int count = 0;
    preorder_sum(root, sum, count);
    return count;
}

///////////////////////////////////////////OR/////////////////////////////////

// less complex
int rootsum(TreeNode *node, int sum)
{
    if (node == nullptr)
        return 0;
    int count = 0;
    if (node->val == sum)
        count++;
    count += rootsum(node->left, sum - node->val);
    count += rootsum(node->right, sum - node->val);
    return count;
}

int pathSum(TreeNode *root, int sum)
{
    if (root == nullptr)
        return 0;
    return rootsum(root, sum) + pathSum(root->left, sum) + pathSum(root->right, sum);
}

// DAY 9 (Rotten Oranges)=======================================

int orangesRotting(vector<vector<int>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();

    queue<pair<int, int>> que;

    bool f = false;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 1)
                f = true;
            else if (grid[i][j] == 2)
                que.push({i, j});
        }
    }
    if (!f)
        return 0;

    vector<vector<int>> dir = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    int time = 0;
    while (!que.empty())
    {
        int sz = que.size();
        while (sz--)
        {
            pair<int, int> tp = que.front();
            que.pop();
            // cout<<tp.first<<" "<<tp.second<<endl;
            for (int d = 0; d < 4; d++)
            {
                int r = tp.first + dir[d][0];
                int c = tp.second + dir[d][1];
                if (r >= 0 && c >= 0 && r < n && c < m && grid[r][c] == 1)
                {
                    grid[r][c] = 2;
                    que.push({r, c});
                }
            }
        }
        if (!que.empty())
            time++;
    }
    for (vector<int> v : grid)
        for (int i : v)
            if (i == 1)
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
    while (x)
    {
        if (x & 1)
            ans *= n;
        n *= n;
        x >>= 1;
    }
    return ans;
}

int titleToNumber(string s)
{
    int col = 0;
    for (int i = 0; i < s.size(); ++i)
    {
        int r = s.size() - i - 1;
        int idx = s[i] - 'A' + 1;
        col += pow(26, r) * idx;
    }
    return col;
}

// DAY 11 (H -index)====================================================

// Method 1 (naive approach) --> O(n^2)

int hIndex(vector<int> &citations)
{
    int n = citations.size();
    unordered_map<int, int> m;
    for (int i : citations)
        m[i]++;

    for (int h = n; h > 0; h--)
    {
        int lh = 0, gh = 0;
        for (int i : citations)
            if (i > h)
                gh++;
            else if (i < h)
                lh++;
        int hh = m[h];
        int req = 0;
        if (lh > n - h || gh > h)
            continue;
        if (lh < n - h)
            req += (n - h) - lh;
        if (gh < h)
            req += h - gh;
        if (hh >= req)
            return h;
    }
    return 0;
}

////////////////////////OR///////////////////////

// Method 2 (optimized) --> O(n)

int hIndex(vector<int> &citations)
{
    int n = citations.size();
    int h = 0;
    sort(citations.begin(), citations.end());

    for (int i = n - 1; i >= 0; i--)
    {
        if (citations[i] >= h + 1)
            h++;
        else
            return h;
    }
    return h;
}

// DAY 12 (Pascal's Triangle 2)===================================================

// Method 1 (using queue)
vector<int> getRow(int rowIndex)
{
    queue<int> que;
    que.push(1);
    int lvl = 0;
    while (lvl != rowIndex)
    {
        int prev = 0;
        int sz = que.size();
        while (sz--)
        {
            int top = que.front();
            que.pop();
            que.push(top + prev);
            prev = top;
        }
        lvl++;
        que.push(1);
    }
    vector<int> ans;
    while (!que.empty())
    {
        ans.push_back(que.front());
        que.pop();
    }
    return ans;
}

/////////////////////////////OR///////////////////////

// Method 2 (using loops)
vector<int> getRow(int rowIndex)
{
    vector<int> ans;

    for (int i = 0; i <= rowIndex; i++)
    {
        ans.push_back(1);
        for (int j = i - 1; j > 0; j--)
            ans[j] = ans[j] + ans[j - 1];
    }
    return ans;
}

// Day 13 (Iterator for Combination)==================================================

// Method 1 (by popping the front element every time)
// very slow
class CombinationIterator
{
public:
    vector<string> comb;
    void combs(string &s, int k, int idx, string ans, vector<string> &res)
    {
        if (ans.size() == k)
        {
            res.push_back(ans);
            return;
        }
        for (int i = idx; i < s.size(); i++)
            combs(s, k, i + 1, ans + s[i], res);
    }

    CombinationIterator(string characters, int combinationLength)
    {
        combs(characters, combinationLength, 0, "", this->comb);
        // for(string s : comb)
        //     cout<<s<<" ";
    }

    string next()
    {
        string s = comb.front();
        this->comb.erase(comb.begin());
        return s;
    }

    bool hasNext()
    {
        return comb.size() > 0;
    }
};

/**
 * Your CombinationIterator object will be instantiated and called as such:
 * CombinationIterator* obj = new CombinationIterator(characters, combinationLength);
 * string param_1 = obj->next();
 * bool param_2 = obj->hasNext();
 */

/////////////////////////////////OR//////////////////////////

// Method 2 (using index to print, instead of front element)
// much faster

vector<string> comb;
int ele;
void combs(string &s, int k, int idx, string ans, vector<string> &res)
{
    if (ans.size() == k)
    {
        res.push_back(ans);
        return;
    }
    for (int i = idx; i < s.size(); i++)
        combs(s, k, i + 1, ans + s[i], res);
}

CombinationIterator(string characters, int combinationLength)
{
    this->ele = 0;
    combs(characters, combinationLength, 0, "", this->comb);
    // for(string s : comb)
    //     cout<<s<<" ";
}

string next()
{
    string s = comb[ele++];
    return s;
}

bool hasNext()
{
    return ele != comb.size();
}

// Method 3 (using queue instead of array to add strings)
// same time

queue<string> comb;
void combs(string &s, int k, int idx, string ans)
{
    if (ans.size() == k)
    {
        comb.push(ans);
        return;
    }
    for (int i = idx; i < s.size(); i++)
        combs(s, k, i + 1, ans + s[i]);
}

CombinationIterator(string characters, int combinationLength)
{
    combs(characters, combinationLength, 0, "");
}

string next()
{
    string s = comb.front();
    comb.pop();
    return s;
}

bool hasNext()
{
    return !comb.empty();
}

// OR
// same as prev, just made the main string as the member function

string s;
queue<string> comb;
void combs(string &s, int k, int idx, string ans)
{
    if (ans.size() == k)
    {
        comb.push(ans);
        return;
    }
    for (int i = idx; i < s.size(); i++)
        combs(s, k, i + 1, ans + s[i]);
}

CombinationIterator(string characters, int combinationLength)
{
    this->s = characters;
    combs(characters, combinationLength, 0, "");
}

string next()
{
    string s = comb.front();
    comb.pop();
    return s;
}

bool hasNext()
{
    return !comb.empty();
}

// DAY 15 (Lonegest Palindrome)======================================================

// Method 1 (using map)
int longestPalindrome(string s) 
{
    unordered_map<char,int> mc;
    for(char c : s)
        mc[c]++;
    
    int maxlen = 0;
    bool odd = false;
    for(auto itr : mc)
    {
        if(itr.second & 1)
        {
            maxlen += itr.second - 1;
            odd = true;
        }
        else
            maxlen += itr.second;
    }
    return maxlen + odd;
}

// DAY 15 (Non - Overlapping intervals)==============================================

int eraseOverlapIntervals(vector<vector<int>>& intervals) 
{
    int n = intervals.size();
    sort(intervals.begin(),intervals.end(),[](const vector<int> &a, const vector<int> &b){      
        return a[0] < b[0];
    });
    
    int nono = 0, last = 0;
    for(int i = 1; i < n ; i++)
    {
        if(intervals[i][0] < intervals[last][1])
        {
            nono++;
            if(intervals[i][1] < intervals[last][1])
                last = i;
        }
        else
            last = i;
    }
    return nono;
}

// DAY 16 (Best Time to Buy and Sell Stock III)====================================================

int maxProfit(vector<int>& prices) 
{
    int n = prices.size();
    if(n <= 1)
        return 0;
    vector<int> profit1(n,0);
    vector<int> profit2(n,0);
    int pmin = prices[0], pmax = prices[n-1];
    
    for(int i=1; i<n; i++)
    {
        profit1[i] = max(profit1[i-1], prices[i] - pmin);
        pmin = min(pmin, prices[i]);
        
        int j = n-i-1;
        profit2[j] = max(profit2[j+1], pmax - prices[j]);
        pmax = max(pmax, prices[j]);
    }
    
    int maxprofit = 0;
    for(int i=0; i<n; i++)
        maxprofit = max(maxprofit, profit1[i]+profit2[i]);
    
    return maxprofit;
}

// DAY 17 (Distribute Candies to People) =======================================================

// Method 1 --> x*O(n)  (x >= 1)
vector<int> distributeCandies(int candies, int num_people) 
{
    int req = 1;
    vector<int> dist(num_people,0);
    int i = 0;
    while(candies - req >= 0)
    {
        dist[i] += req;
        candies -= req;
        req++;
        i = (i + 1) % num_people;
    }
    dist[i] += candies;
    return dist;
}

///////////////////////////OR//////////////////////////////

// Method 2 --> O(n)
int sqroot(int n)
{
    int si = 1, ei = n;
    
    while(si <= ei)
    {
        int mid = (si + ei) / 2;
        if((long long)mid*mid == n)
            return mid;
        else if((long long)mid*mid < n)
            si = mid + 1;
        else
            ei = mid - 1;
    }
    return si - 1;
}

vector<int> distributeCandies(int candies, int num_people) 
{
    int n = 2*candies;
    int x = sqroot(n);
    // cout<<x<<" ";
    while(x*x + x > n)   // here x is the number for which sum of first x nos.(x(x+1)/2) is just less or     
        x--;                                                                               // equal to n.
    // cout<<x<<endl;
    
    int cycles = x / num_people;
    int cycle_end = x % num_people;
    int candies_before_end = num_people * (cycles*(cycles+1)/2);
    int candies_after_end = num_people * (cycles*(cycles-1)/2);
    int rem_candies = candies - (x*(x+1))/2;
    // cout<<cycles<<" "<<cycle_end<<" "<<candies_before_end<<" "<<candies_after_end<<" "<<rem_candies<<endl;
    
    vector<int> dist(num_people, 0);
    for(int i=0; i<num_people; i++)
    {
        if(i < cycle_end)
            dist[i] += candies_before_end + (cycles+1) * (i + 1);
        else
            dist[i] += candies_after_end + cycles * (i + 1);
    }
    dist[cycle_end % num_people] += rem_candies;
    
    return dist;
}

// DAY 18 (Numbers With Same Consecutive Differences)================================================

vector<int> digits;

void kdiff(long int num, int last, int count, int n, int k)
{
    if(count == n+1)
    {
        digits.push_back(num/10);
        return;
    }
    
    // cout<<last<<" "<<num<<endl;
    if(last - k >= 0)
        kdiff((num + (last-k))*10, last - k, count + 1, n, k);
    if(last + k <= 9 && k != 0)
        kdiff((num + (last+k))*10, last + k, count + 1, n, k);
}

vector<int> numsSameConsecDiff(int N, int K) 
{
    if(N == 1)
        digits.push_back(0);
    for(int i = 1 ; i <= 9 ; i++)
    {
        long int num = i*10;
        kdiff(num, i, 2, N, K);
    }
    return digits;
}

// DAY 19(Goat Latin)=================================================

bool isVowel(char c)
{
    c = tolower(c);
    if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u')
        return true;
    return false;
}

string toGoatLatin(string S) 
{
    stringstream ss(S);
    string word, a = "a", ans;
    while(ss >> word)
    {
        if(!isVowel(word[0]))
        {
            char c = word[0];
            word.erase(word.begin());
            word += c;
        }
        word += "ma" + a;
        // cout<<word<<endl;
        ans += word + " ";
        a += "a";
    }
    ans.pop_back();
    return ans;
}

// DAY 20(Reorder List)==============================================

// Method 1
void reorderList(ListNode* head) 
{
    if(head == nullptr)
        return;
    ListNode* node = head;
    int size = 0;
    while(node)
    {
        node = node->next;
        size++;
    }
    node = head;
    ListNode *temp = node;
    int mid = (size+1)/2;
    while(--mid)
        temp = temp->next;
    ListNode *rnode = temp->next;
    temp->next = nullptr;
    
    ListNode *curr = rnode, *prev = nullptr, *forw = rnode;
    while(curr)
    {
        forw = curr->next;
        curr->next = prev;
        prev = curr;
        curr = forw;
    }
    rnode = prev;
    
    ListNode *i1 = node, *i2 = rnode, *res = node;
    temp = res;
    i1 = i1->next;
    while(i1 || i2)
    {
        if(i2)
        {
            temp->next = i2;
            i2 = i2->next;
            temp = temp->next;
        }
        if(i1)
        {
            temp->next = i1;
            i1 = i1->next;
            temp = temp->next;
        }
    }
}

///////////////////////////////OR////////////////////////////////
// Method 2 (cleaner)

ListNode* findmid(ListNode* head)
{
    ListNode *slow = head, *fast = head, *prev = nullptr;
    while(fast && fast->next)
    {
        prev = slow;
        slow = slow->next;
        fast = fast->next->next;
    }
    if(fast == nullptr)
        slow = prev;
    return slow;
}

ListNode* reverselist(ListNode* node)      // recursively
{
    if(!node->next)
        return node;
    ListNode* head = reverselist(node->next);
    node->next->next = node;
    node->next = nullptr;
    return head;
}

void reorderList(ListNode* head) 
{
    if(!head || !head->next)
        return;
    
    ListNode* midnode = findmid(head);
    ListNode *node = head, *rnode = midnode->next;
    midnode->next = nullptr;
    
    rnode = reverselist(rnode);
    
    while(node && rnode)
    {
        ListNode *temp1 = node->next, *temp2 = rnode->next;
        
        node->next = rnode;
        rnode->next = temp1;
        node = temp1;
        rnode = temp2;
    }
    return;
}

// DAY 21 (Sort Array By Parity)=============================================

// Method 1 (extra memory) O(n^2) time
vector<int> sortArrayByParity(vector<int>& A) 
{
    int n = A.size();
    vector<int> B;
    B.reserve(n);
    for(int i : A)
        if(i & 1)
            B.push_back(i);
        else
            B.insert(B.begin(),i);
    return B;
}

// Method 2 (same approach as separating 0 and 1) --> O(n)
vector<int> sortArrayByParity(vector<int>& A) 
{
    int n = A.size();
    int s = 0, e = n-1;
    while(s < e)
    {
        if(A[s] % 2 == 1)
        {
            if(A[e] % 2 == 0)
                swap(A[s++], A[e--]);
            else
            {
                e--;
                continue;
            }
        }
        else
            s++;
    }
    return A;
}

// Method 3 (using custom comaprator) --> O(n*logn)
vector<int> sortArrayByParity(vector<int>& A) 
{
    int n = A.size();
    sort(A.begin(), A.end(), [](const int &a, const int &b){
        return (a % 2) < (b % 2);
    });
    return A;
}

// Method 4 (Using extra memory but less time) --> O(2*n)
vector<int> sortArrayByParity(vector<int>& A) 
{
    int n = A.size();
    vector<int> B(n);
    int j = 0;
    for(int i : A)
        if(!(i & 1))
            B[j++] = i;
    for(int i : A)
        if((i & 1))
            B[j++] = i;
    return B;
}
// DAY 23 (Stream of Characters)==========================================================

// Method 1 (by checking in the queried string if its equal to the given words) --> O(n^2)
// TLE
class StreamChecker {
public:
    
    string s;
    unordered_map<char,vector<string>> lc;
    StreamChecker(vector<string>& words) 
    {
        s = "";
        for(string word : words)
            lc[word[word.size()-1]].push_back(word);
    }
    
    bool query(char letter) 
    {
        s += letter;
        if(lc.find(letter) == lc.end())
           return false;
        for(string str : lc[letter])
        {
            if(s.size() >= str.size() && s.substr(s.size()-str.size(), s.size()) == str)
                return true;
        }
        return false;
    }
};

/**
 * Your StreamChecker object will be instantiated and called as such:
 * StreamChecker* obj = new StreamChecker(words);
 * bool param_1 = obj->query(letter);
 */

////////////////////////////////OR///////////////////////////////

// Method 2 (Using Trie) --> O(n)
// AC
class StreamChecker {
public:
    
    class trie
    {
        public:
        vector<trie*> t;
        bool wordEnd;
        trie()
        {
            t.assign(26,nullptr);
            wordEnd = false;
        }
    };
    
    string s;
    trie* node;
    StreamChecker(vector<string>& words) 
    {
        this->s = "";
        this->node = new trie();
        
        for(string word : words)    // INSERTING
        {
            trie* curr = node;
            for(int i=word.size()-1; i>=0; i--)
            {
                char c = word[i];
                if(!curr->t[c-'a'])
                    curr->t[c-'a'] = new trie();
                curr = curr->t[c-'a'];
            }
            curr->wordEnd = true;
        }
    }
    
    bool query(char letter) 
    {
        s += letter;
        trie* curr = node;
        if(!curr->t[letter - 'a'])
            return false;
        for(int i=s.size()-1; i>=0; i--)
        {
            if(!curr->t[s[i] - 'a'])
                return false;
            if(curr->t[s[i] - 'a'] && curr->t[s[i] - 'a']->wordEnd)
                return true;
            curr = curr->t[s[i] - 'a'];
        }
        return false;
    }
};

// DAY 25 (Sum of Left Leaves)========================================

// Method 1 (by checking for left with a character)
int sum = 0;
void totalleft(TreeNode* node, char c)
{
    if(!node->left && !node->right)
    {
        if(c == 'l')
            sum += node->val;
        return;
    }
    if(node->left)
        totalleft(node->left, 'l');
    if(node->right)
        totalleft(node->right, 'r');
}

int sumOfLeftLeaves(TreeNode* root)
{
    if(!root || (!root->left && !root->right))
        return 0;
    char c = 'n';
    totalleft(root,c);
    return sum;
}

// Method 2 (using true for left)================================
// faster
int sumOfLeftLeaves(TreeNode* root, bool left = false)
{
    if(!root)
        return 0;
    int sum = sumOfLeftLeaves(root->left, true) + sumOfLeftLeaves(root->right, false);
    if(!root->left && !root->right && left)
        sum = root->val;
    return sum;
}

// Method 3 (without using any extra parameter)====================================
int sumOfLeftLeaves(TreeNode* root)
{
    if(!root)
        return 0;
    int sum = sumOfLeftLeaves(root->left) + sumOfLeftLeaves(root->right);
    if(root->left && !root->left->right && !root->left->left)
        sum += root->left->val;
    return sum;
}

// DAY 26 (Minimum Cost For Tickets)====================================================

// Method 1 (recursion)
// TLE
int mincost = INT_MAX;

void ways(int idx, vector<int> &days, vector<int> &costs, int cost)
{
    if(idx >= days.size())
    {
        mincost = min(mincost, cost);
        return;
    }
    // cout<<idx<<endl;
    ways(idx+1, days, costs, cost+costs[0]);
    
    int i = idx;
    for(; i < days.size() && days[i] < days[idx]+7; i++)
    {}
    ways(i, days, costs, cost+costs[1]);
    
    i = idx;
    for(; i < days.size() && days[i] < days[idx]+30; i++)
    {}
    ways(i, days, costs, cost+costs[2]);
}

int mincostTickets(vector<int>& days, vector<int>& costs) 
{
    ways(0, days, costs, 0);
    return mincost;
}

////////////////////////OR///////////////////////

// Method 2 (memoized)
// AC

int ways(int idx, vector<int> &days, vector<int> &costs, vector<int> &dp, int maxcost)
{
    if(idx == days.size())
        return dp[idx] = 0;
    if(dp[idx] != maxcost)
        return dp[idx];
    // cout<<idx<<endl;
    int cost1, cost7, cost30;
    
    cost1 = ways(idx+1, days, costs, dp, maxcost) + costs[0];
    
    int i = idx;
    for(; i < days.size() && days[i] < days[idx]+7; i++)
    {}
    cost7 = ways(i, days, costs, dp, maxcost) + costs[1];
    
    i = idx;
    for(; i < days.size() && days[i] < days[idx]+30; i++)
    {}
    cost30 = ways(i, days, costs, dp, maxcost) + costs[2];
    
    return dp[idx] = min(dp[idx], min(cost1, min(cost7, cost30)));
}

int mincostTickets(vector<int>& days, vector<int>& costs) 
{
    int maxcost = 365*costs[0];
    vector<int> dp(days.size()+1,maxcost);
    return ways(0, days, costs, dp, maxcost);
}

// Method 3 (DP)
// AC
int ways_dp(vector<int> &days, vector<int> &costs, vector<int> &dp)
{
    for(int idx = days.size(); idx >= 0; idx--)
    {
        if(idx == days.size())
        {
            dp[idx] = 0;
            continue;
        }
        int cost1, cost7, cost30;

        cost1 = dp[idx+1] + costs[0];

        int i = idx;
        for(; i < days.size() && days[i] < days[idx]+7; i++)
        {}
        cost7 = dp[i] + costs[1];

        i = idx;
        for(; i < days.size() && days[i] < days[idx]+30; i++)
        {}
        cost30 = dp[i] + costs[2];

        dp[idx] = min(dp[idx], min(cost1, min(cost7, cost30)));
    }
    return dp[0];
}

int mincostTickets(vector<int>& days, vector<int>& costs) 
{
    int maxcost = 365*costs[0];
    vector<int> dp(days.size()+1,maxcost);
    return ways_dp(days, costs, dp);
}