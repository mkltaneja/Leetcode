// DAY 1 (344. Reverse String)=================================================================================================

void reverseString(vector<char>& s) 
{
    reverse(s.begin(), s.end());
}

// DAY 2 (680. Valid Palindrome II)=================================================================================================

bool ispal(string &s, int i, int j)
{
    while(i <= j && s[i] == s[j]) i++, j--;

    return i > j;
}

bool validPalindrome(string s) 
{
    int i = 0, j = s.size()-1;
    while(i <= j)
    {
        if(s[i] != s[j])
            return ispal(s, i+1, j) || ispal(s, i, j-1);
        i++, j--;
    }
    return true;
}

// DAY 3 (31. Next Permutation)=================================================================================================

void nextPermutation(vector<int>& nums) {
    next_permutation(nums.begin(), nums.end());
}

// DAY 4 (1721. Swapping Nodes in a Linked List)=================================================================================================

ListNode* swapNodes(ListNode* head, int k) 
{
    int n = 0;
    ListNode* itr = head;
    while(itr)
    {
        itr = itr->next;
        n++;
    }
    int kk = n-k;
    ListNode* itr1 = head, *itr2 = head;
    while(--k)
        itr1 = itr1->next;
    while(kk--)
        itr2 = itr2->next;

    swap(itr1->val, itr2->val);

    return head;
}

// DAY 5 (11. Container With Most Water)=================================================================================================

int maxArea(vector<int>& height) 
{
    int i = 0, j = height.size()-1;
    int ans = 0;
    while(i < j)
    {
        ans = max(ans, (height[i] < height[j])? height[i] * (j - i++)
                                             : height[j] * (j-- - i));
    }
    return ans;
}

// DAY 6 (923. 3Sum With Multiplicity)=================================================================================================

#define f first
#define s second
int threeSumMulti(vector<int>& arr, int target) 
{
    int n = arr.size();
    long ans = 0;
    int mod = 1e9 + 7;
    unordered_map<int,long> mp;
    for(int i = 0; i < n; i++)
        mp[arr[i]]++;

    for(auto p1 : mp)
    {
        for(auto p2 : mp)
        {
            int x = target - p1.f - p2.f;
            if(!mp.count(x)) continue;

            if(p1.f == p2.f && p2.f == x)
                ans += p1.s * (p1.s - 1) * (p1.s - 2) / 6;
            else if(p1.f == p2.f)
                ans += mp[x] * p1.s * (p1.s - 1) / 2;
            else if(p1.f < p2.f && p2.f < x)
                ans += mp[x] * p1.s * p2.s;
        }
    }

    return ans % mod;
}

// DAY 7 (1046. Last Stone Weight)=================================================================================================

int lastStoneWeight(vector<int>& stones) 
{
    priority_queue<int> pq;
    for(int x : stones)
        pq.push(x);
    while(pq.size() > 1)
    {
        int x = pq.top();
        pq.pop();
        int y = pq.top();
        pq.pop();
        if(x > y) pq.push(x-y);
        else if(y > x) pq.push(y-x);
    }
    return pq.empty()? 0 : pq.top();
}

// DAY 8 (703. Kth Largest Element in a Stream)=================================================================================================

class KthLargest {
public:
    priority_queue<int, vector<int>, greater<int>> pq;
    int k;
    KthLargest(int k, vector<int>& nums) 
    {
        this->k = k;
        for(int x : nums)
        {
            pq.push(x);
            if(pq.size() > k)
                pq.pop();
        }
    }
    
    int add(int val) 
    {
        pq.push(val);
        if(pq.size() > k)
            pq.pop();
        return pq.top();
    }
};

/**
 * Your KthLargest object will be instantiated and called as such:
 * KthLargest* obj = new KthLargest(k, nums);
 * int param_1 = obj->add(val);
 */

// DAY 9 (347. Top K Frequent Elements)=================================================================================================

vector<int> topKFrequent(vector<int>& nums, int k) 
{
    unordered_map<int,int> mp;
    for(int x : nums)
        mp[x]++;

    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
    for(auto p : mp)
    {
        pq.push({p.second, p.first});
        if(pq.size() > k)
            pq.pop();
    }

    vector<int> ans;
    while(!pq.empty())
    {
        ans.push_back(pq.top().second);
        pq.pop();
    }

    return ans;
}

// DAY 10 (682. Baseball Game)=================================================================================================

int calPoints(vector<string>& ops) 
{
    int ans = 0;
    stack<int> st;
    for(string s : ops)
    {
        if(s[0] == '-' || (s[0] >= '1' && s[0] <= '9'))
            st.push(stoi(s));
        else if(s == "+")
        {
            int a = st.top();
            st.pop();
            int b = st.top();
            st.pop();
            st.push(b);
            st.push(a);
            st.push(a + b);
        }
        else if(s == "D")
        {
            int x = st.top();
            x *= 2;
            st.push(x);
        }
        else st.pop();
    }
    while(!st.empty())
    {
        ans += st.top();
        st.pop();
    }

    return ans;
}

// DAY 11 (1260. Shift 2D Grid)=================================================================================================

vector<vector<int>> shiftGrid(vector<vector<int>>& grid, int k) 
{
    int n = grid.size(), m = grid[0].size();
    k %= n*m;

    vector<int> grid1d(n*m);
    for(int i = 0; i < n*m; i++)
    {
        grid1d[i] = grid[i/m][i%m];
    }

    vector<int> a = vector<int>(grid1d.begin(), grid1d.begin() + n*m - k);
    vector<int> b = vector<int>(grid1d.begin() + n*m - k, grid1d.end());
    grid1d = vector<int>(b.begin(), b.end());
    grid1d.insert(grid1d.end(), a.begin(), a.end());

    for(int i = 0; i < n*m; i++)
        grid[i/m][i%m] = grid1d[i];

    return grid;
}

// DAY 12 (289. Game of Life)=================================================================================================

void gameOfLife(vector<vector<int>>& board) 
{
    int n = board.size(), m = board[0].size();

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            int lives = (i? (board[i-1][j] == 1 || board[i-1][j] == 2) : 0) + 
                (j? (board[i][j-1] == 1 || board[i][j-1] == 2) : 0) + 
                (i+1 < n? (board[i+1][j] == 1 || board[i+1][j] == 2) : 0) + 
                (j+1 < m? (board[i][j+1] == 1 || board[i][j+1] == 2) : 0) + 
                (i && j+1 < m? (board[i-1][j+1] == 1 || board[i-1][j+1] == 2) : 0) + 
                (j && i+1 < n? (board[i+1][j-1] == 1 || board[i+1][j-1] == 2) : 0) + 
                (i && j? board[i-1][j-1] == 1 || board[i-1][j-1] == 2 : 0) + 
                (i+1 < n && j+1 < m? (board[i+1][j+1] == 1 || board[i+1][j+1] == 2) : 0);
            if(board[i][j])
            {
                if(lives < 2 || lives > 3) board[i][j] = 2;
            }
            else if(lives == 3) board[i][j] = 3;
        }
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            board[i][j] %= 2;
        }
    }
}

// DAY 13 (59. Spiral Matrix II)=================================================================================================

vector<vector<int>> generateMatrix(int n) 
{
    vector<vector<int>> arr(n,vector<int>(n));
    int sr = 0, sc = 0, er = n-1, ec = n-1, x = 1;
    while(x <= n*n)
    {
        for(int i = sc; i <= ec && x <= n*n; i++, x++)
            arr[sr][i] = x;
        sr++;
        for(int i = sr; i <= er && x <= n*n; i++, x++)
            arr[i][ec] = x;
        ec--;
        for(int i = ec; i >= sc && x <= n*n; i--, x++)
            arr[er][i] = x;
        er--;
        for(int i = er; i >= sr && x <= n*n; i--, x++)
            arr[i][sc] = x;
        sc++;
    }
    return arr;
}

// DAY 14 (700. Search in a Binary Search Tree)=================================================================================================

TreeNode* searchBST(TreeNode* root, int val) 
{
    if(!root) return nullptr;
    if(root->val == val) return root;

    return root->val < val? searchBST(root->right, val) : searchBST(root->left, val);
}

// DAY 15 (669. Trim a Binary Search Tree)=================================================================================================

TreeNode* trimBST(TreeNode* root, int low, int high) 
{
    if(!root) return nullptr;
    if(low <= root->val && high >= root->val) 
    {
        root->left = trimBST(root->left, low, high);
        root->right = trimBST(root->right, low, high);
        return root;
    }
    else if(low > root->val)
        return trimBST(root->right, low, high);
    else
        return trimBST(root->left, low, high);
}

// DAY 16 (538. Convert BST to Greater Tree)=================================================================================================

int tot = 0;
TreeNode* convertBST(TreeNode* root) 
{
    if(!root) return root;

    convertBST(root->right);
    tot += root->val;
    root->val = tot;
    convertBST(root->left);

    return root;
}

// DAY 17 (897. Increasing Order Search Tree)=================================================================================================

TreeNode* ans = new TreeNode(-1), *itr = ans;
void inorder(TreeNode* node)
{
    if(!node) return;
    inorder(node->left);
    itr->right = new TreeNode(node->val);
    itr = itr->right;
    inorder(node->right);
}

TreeNode* increasingBST(TreeNode* root) 
{
    inorder(root);
    return ans->right;
}

// DAY 18 (230. Kth Smallest Element in a BST)=================================================================================================

int kthSmallest(TreeNode* root, int &k) 
{
    if(!root) return -1;

    int lans = kthSmallest(root->left, k);
    if(--k == 0) return root->val;
    int rans = kthSmallest(root->right, k);

    if(lans != -1 || rans != -1)
        return lans == -1? rans : lans;
    return -1;
}

// DAY 19 (99. Recover Binary Search Tree)=================================================================================================

TreeNode* prev = new TreeNode(INT_MIN), *a = nullptr, *b = nullptr;
void inorder(TreeNode* curr)
{
    if(!curr) return;

    inorder(curr->left);

    if(!a && curr->val < prev->val)
    {
        a = prev;
        b = curr;
    }
    else if(curr->val < prev->val)
        b = curr;

    prev = curr;

    inorder(curr->right);
}

void recoverTree(TreeNode* root) 
{
    inorder(root);

    swap(a->val, b->val);
}

// DAY 20 (173. Binary Search Tree Iterator)=================================================================================================

stack<TreeNode*> st;
void lefts(TreeNode* node)
{
    while(node)
    {
        st.push(node);
        node = node->left;
    }
}

BSTIterator(TreeNode* root) 
{
    lefts(root);
}

int next() 
{
    TreeNode* ans = st.top();
    st.pop();
    lefts(ans->right);
    return ans->val;
}

bool hasNext() 
{
    return !st.empty();
}

// DAY 21 (705. Design HashSet)=================================================================================================

// APPROACH 1 (1D Mapping)

class MyHashSet {
public:
    
    vector<bool> set;
    MyHashSet() 
    {
        set.assign(1e6+5, false);
    }
    
    void add(int key) 
    {
        set[key] = true;
    }
    
    void remove(int key) 
    {
        set[key] = false;
    }
    
    bool contains(int key) 
    {
        return set[key];
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */

// APPROACH 2 (Buckets -> 2D Mapping)

class MyHashSet {
    
    int n;
    vector<vector<int>> buckets;
    int hash_value(int key)
    {
        return key % n;
    }
    
public:
    
    MyHashSet() 
    {
        this->n = 10000;
        this->buckets.assign(n, vector<int>());
    }
    
    void add(int key) 
    {
        int i = hash_value(key);
        if(find(buckets[i].begin(), buckets[i].end(), key) == buckets[i].end())
            buckets[i].push_back(key);
    }
    
    void remove(int key) 
    {
        int i = hash_value(key);
        vector<int>::iterator itr = find(buckets[i].begin(), buckets[i].end(), key);
        if(itr == buckets[i].end()) return;
        buckets[i].erase(itr);
    }
    
    bool contains(int key) 
    {
        int i = hash_value(key);
        return (find(buckets[i].begin(), buckets[i].end(), key) != buckets[i].end());
    }
};

/**
 * Your MyHashSet object will be instantiated and called as such:
 * MyHashSet* obj = new MyHashSet();
 * obj->add(key);
 * obj->remove(key);
 * bool param_3 = obj->contains(key);
 */

// DAY 22 (706. Design HashMap)=================================================================================================

class MyHashMap {
    
    int n;
    vector<vector<pair<int,int>>> buckets;
    
    int hash(int x)
    {
        return x % n;
    }
    
public:
    
    MyHashMap() 
    {
        this->n = 1000;
        buckets.resize(n, vector<pair<int,int>>());
    }
    
    int find(int bucket, int key)
    {
        for(int i = 0; i < buckets[bucket].size(); i++)
            if(buckets[bucket][i].first == key)
                return i;
        return -1;
    }
    
    void put(int key, int value) 
    {
        int bucket = hash(key);
        int i = find(bucket, key);
        
        if(i == -1) buckets[bucket].push_back({key, value});
        else buckets[bucket][i] = {key, value};
    }
    
    int get(int key) 
    {
        int bucket = hash(key);
        int i = find(bucket, key);
        
        return (i == -1)? -1 : buckets[bucket][i].second;
    }
    
    void remove(int key) 
    {
        int bucket = hash(key);
        int i = find(bucket, key);
        
        if(i != -1) 
        {
            swap(buckets[bucket][i], buckets[bucket].back());
            buckets[bucket].pop_back();
        }
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */

// DAY 23 (535. Encode and Decode TinyURL)=================================================================================================

unordered_map<string,string> enc;
unordered_map<string,string> dec;
string dict = "1234567890qwertyuiopasdfghjklzxcvbnmQWERTYUIOPASDFGHJKLZXCVBNM";
// Encodes a URL to a shortened URL.
string encode(string longUrl) 
{
    string res = "";

    while(res.empty())
    {
        for(int i = 0; i < 10; i++)
            res += dict[rand() % 62];
        if(enc.count(res)) res = "";
    }
    enc[longUrl] = res;
    dec[res] = longUrl;
    return "http://tinyurl.com/" + res;
}

// Decodes a shortened URL to its original URL.
string decode(string shortUrl) 
{
    return dec[shortUrl.substr(19)];
}

// DAY 24 (1396. Design Underground System)=================================================================================================

class UndergroundSystem {
public:
    
    #define f first
    #define s second
    
    unordered_map<int,pair<string, int>> mid;
    map<string,pair<int, int>> mt;
    UndergroundSystem() 
    {
        
    }
    
    void checkIn(int id, string stationName, int t) 
    {
        mid[id] = {stationName, t};
    }
    
    void checkOut(int id, string stationName, int t) 
    {
        mt[mid[id].f + " " + stationName].f += (t - mid[id].s);
        mt[mid[id].f + " " + stationName].s++;
    }
    
    double getAverageTime(string startStation, string endStation) 
    {
        return 1.0 * mt[startStation + " " + endStation].f / mt[startStation + " " + endStation].s;
    }
};

/**
 * Your UndergroundSystem object will be instantiated and called as such:
 * UndergroundSystem* obj = new UndergroundSystem();
 * obj->checkIn(id,stationName,t);
 * obj->checkOut(id,stationName,t);
 * double param_3 = obj->getAverageTime(startStation,endStation);
 */

// DAY 25 (284. Peeking Iterator)=================================================================================================

/*
 * Below is the interface for Iterator, which is already defined for you.
 * **DO NOT** modify the interface for Iterator.
 *
 *  class Iterator {
 *		struct Data;
 * 		Data* data;
 *  public:
 *		Iterator(const vector<int>& nums);
 * 		Iterator(const Iterator& iter);
 *
 * 		// Returns the next element in the iteration.
 *		int next();
 *
 *		// Returns true if the iteration has more elements.
 *		bool hasNext() const;
 *	};
 */

class PeekingIterator : public Iterator {
public:
    
	PeekingIterator(const vector<int>& nums) : Iterator(nums) 
    {
	    // Initialize any member here.
	    // **DO NOT** save a copy of nums and manipulate it directly.
	    // You should only use the Iterator interface methods.
	}
	
    // Returns the next element in the iteration without advancing the iterator.
	int peek() 
    {
        Iterator itr = *this;
        return itr.next();
	}
	
	// hasNext() and next() should behave the same as in the Iterator interface.
	// Override them if needed.
	int next() 
    {
	    return Iterator::next();
	}
	
	bool hasNext() const 
    {
	    return Iterator::hasNext();
	}
};

// DAY 26 (1584. Min Cost to Connect All Points)=================================================================================================

int minCostConnectPoints(vector<vector<int>>& points) 
{
int n = points.size();

vector<vector<pair<int,int>>> gp(n);
for(int i = 0; i < n; i++)
    for(int j = i+1; j < n; j++)
	gp[i].push_back({j, abs(points[i][0] - points[j][0]) + abs(points[i][1] - points[j][1])});

int ans = 0;
priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
pq.push({0,0});
vector<bool> vis(n,false);
while(!pq.empty())
{
    auto tp = pq.top();
    pq.pop();
    if(vis[tp.second]) continue;
    vis[tp.second] = true;
    ans += tp.first;

    for(int i = 0; i < n; i++)
	if(!vis[i])
	    pq.push({abs(points[i][0] - points[tp.second][0]) + abs(points[i][1] - points[tp.second][1]), i});
}

return ans;
}
