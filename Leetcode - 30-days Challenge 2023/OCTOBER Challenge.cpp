
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

// DAY 4 (706. Design HashMap)=============================================================================================

// APPROACH 1 (Using 1D array of bigger size to avoid collision) --> Time = O(1), Space = O(MAX_NUMBER)

class MyHashMap {
public:

    vector<int> map;
    int size = 1e6+1;
    MyHashMap() 
    {
        map.assign(size, -1);
    }
    
    void put(int key, int value) 
    {
        map[key] = value;
    }
    
    int get(int key) 
    {
        return map[key];
    }
    
    void remove(int key) 
    {
        map[key] = -1;
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */

// APPROACH 2 (Using BST to avoid collision) --> Time = O(size * log(queries)), Space = O(size*queries) --> [OPTIMIZED]

class MyHashMap {
public:

    class Node
    {
        public:
        Node* left, *right;
        int key, val;
        Node(int key, int val)
        {
            this->key = key;
            this->val = val;
            this->left = nullptr;
            this->right = nullptr;
        }
    };

    Node* insert(Node* root, int key, int val)
    {
        if(!root)
            return new Node(key, val);
        if(root->key == key)
            root->val = val;
        else if(root->key < key)
            root->right = insert(root->right, key, val);
        else root->left = insert(root->left, key, val);

        return root;
    }

    Node* removeNode(Node* root, int key)
    {
        if(!root)
            return nullptr;
        if(root->key == key)
        {
            if(!root->left)
            {
                Node* tmp = root->right;
                delete root;
                return tmp;
            }
            else if(!root->right)
            {
                Node* tmp = root->left;
                delete root;
                return tmp;
            }

            Node* minNode = root->right;
            while(minNode->left) minNode = minNode->left;

            root->key = minNode->key;
            root->val = minNode->val;
            root->right = removeNode(root->right, minNode->key);
        }
        else if(root->key < key)
            root->right = removeNode(root->right, key);
        else root->left = removeNode(root->left, key);

        return root;
    }

    int getNodeVal(Node* root, int key)
    {
        if(!root)
            return -1;
        if(root->key < key)
            return getNodeVal(root->right, key);
        else if(root->key > key)
            return getNodeVal(root->left, key);
        else return root->val;
    }

    vector<Node*> map;
    int size = 10000;
    MyHashMap() 
    {
        map.assign(size, nullptr);
    }
    
    void put(int key, int value) 
    {
        int hash = key % size;
        map[hash] = insert(map[hash], key, value);
    }
    
    int get(int key) 
    {
        int hash = key % size;
        return getNodeVal(map[hash], key);
    }
    
    void remove(int key) 
    {
        int hash = key % size;
        map[hash] = removeNode(map[hash], key);
    }
};

/**
 * Your MyHashMap object will be instantiated and called as such:
 * MyHashMap* obj = new MyHashMap();
 * obj->put(key,value);
 * int param_2 = obj->get(key);
 * obj->remove(key);
 */

// DAY 5 (229. Majority Element II)============================================================================

vector<int> majorityElement(vector<int>& nums) 
{
    int n = nums.size();
    int cnta = 0, cntb = 0, a = INT_MIN, b = INT_MIN;
    for(int x : nums)
    {
        if(x == a) cnta++;
        else if(x == b) cntb++;
        else if(cnta == 0) a = x, cnta = 1;
        else if(cntb == 0) b = x, cntb = 1;
        else cnta--, cntb--;
    }
    cnta = 0, cntb = 0;
    for(int x : nums)
    {
        cnta += x == a;
        cntb += x == b;
    }

    if(cnta > n/3 && cntb > n/3)
        return {a, b};
    if(cnta > n/3)
        return {a};
    if(cntb > n/3)
        return {b};
    return {};
}

// DAY 6 (343. Integer Break)========================================================================

int integerBreak(int n) 
{
    vector<int> dp(n+1, 0);
    for(int i = 1; i < n; i++)
    {
        dp[i] = i;
        for(int x = 1; x <= i/2; x++)
            dp[i] = max(dp[i], dp[x] * dp[i-x]);
    }
    for(int x = 1; x <= n/2; x++)
        dp[n] = max(dp[n], dp[x] * dp[n-x]);

    return dp[n];
}

// DAY 7 (1420. Build Array Where You Can Find The Maximum Exactly K Comparisons)==========================================================================

int mod = 1e9 + 7;
int numOfArraysHelper(int n, int m, int k, int mx, vector<vector<vector<int>>> &dp)
{
    if(n == 0) return k == 0;
    if(k < 0) return 0;
    if(dp[n][mx][k] != -1) return dp[n][mx][k];

    int ans = 0;
    for(int x = 1; x <= m; x++)
        ans = ans % mod + numOfArraysHelper(n-1, m, k - (x > mx), max(mx, x), dp) % mod % mod;
    return dp[n][mx][k] = ans % mod;
}

int numOfArrays(int n, int m, int k)
{
    vector<vector<vector<int>>> dp(n+1, vector<vector<int>> (m+1, vector<int>(k+1, -1)));
    return numOfArraysHelper(n, m, k, 0, dp) % mod;
}

// DAY 8 (1458. Max Dot Product of Two Subsequences)=====================================================================================

int maxDotProd = INT_MIN;

int dfs(int i, int j, vector<int>& nums1, vector<int>& nums2, vector<vector<int>> &dp)
{
    if(i == nums1.size() || j == nums2.size())
        return INT_MIN;
    if(dp[i][j] != -1)
        return dp[i][j];

    int include = dfs(i+1, j+1, nums1, nums2, dp);
    include = (nums1[i] * nums2[j]) + (include == INT_MIN? 0 : include);
    int excludei = dfs(i+1, j, nums1, nums2, dp);
    int excludej = dfs(i, j+1, nums1, nums2, dp);

    int currProd = max({include, excludei, excludej});
    maxDotProd = max(maxDotProd, currProd);
    currProd = currProd < 0? INT_MIN : currProd;

    return dp[i][j] = currProd;
}

int maxDotProduct(vector<int>& nums1, vector<int>& nums2)
{
    vector<vector<int>> dp(nums1.size(), vector<int>(nums2.size(), -1));
    dfs(0, 0, nums1, nums2, dp);

    return maxDotProd;
}

// DAY 9 (34. Find First and Last Position of Element in Sorted Array)===========================================================================

int lowerBound(vector<int> &nums, int target)
{
    int lo = 0, hi = nums.size()-1;
    int ans = nums.size();
    while(lo <= hi)
    {
        int mid = lo + ((hi - lo) >> 1);
        if(nums[mid] < target)
            lo = mid + 1;
        else 
        {
            ans = mid;
            hi = mid - 1;
        }
    }

    return ans;
}

vector<int> searchRange(vector<int>& nums, int target) 
{
    int firstPos = lowerBound(nums, target);
    if(firstPos == nums.size() || nums[firstPos] != target)
        return {-1, -1};

    int lastPos = lowerBound(nums, target+1) - 1;

    return {firstPos, lastPos};
}

// DAY 10 (2009. Minimum Number of Operations to Make Array Continuous)=================================================================================

// METHOD 1 (Using map to handle repeating elements) -> Time = O(2*n), Space = O(n)

int minOperations(vector<int>& nums) 
{
    sort(nums.begin(), nums.end());
    int n = nums.size(), maxDiff = n-1;
    int maxContSubarray = 0;
    unordered_map<int,int> cnt;

    for(int i = 0, j = 0; i < n; i++)
    {
        cnt[nums[i]]++;
        while(nums[i] - nums[j] > maxDiff)
        {
            if(--cnt[nums[j]] == 0)
                cnt.erase(nums[j]);
            j++;
        }
        maxContSubarray = max(maxContSubarray, (int)cnt.size());
    }

    return n - maxContSubarray;
}

// METHOD 2 (Without using map - handling repeating elements separately) -> Time = O(3*n), Space = O(n) [OPTIMIZED]

int minOperations(vector<int>& nums) 
{
    sort(nums.begin(), nums.end());
    int n = nums.size(), maxDiff = n-1;
    int maxContSubarray = 0;
    vector<int> uni;
    for(int i = 0; i < n; )
    {
        uni.push_back(nums[i]);
        int j = i;
        while(j < n && nums[i] == nums[j]) j++;
        i = j;
    }
    int m = uni.size();

    int ans = n - m;
    for(int i = 0, j = 0; i < m; i++)
    {
        while(uni[i] - uni[j] > maxDiff) j++;
        maxContSubarray = max(maxContSubarray, i-j+1);
    }
    ans += m - maxContSubarray;

    return ans;
}
