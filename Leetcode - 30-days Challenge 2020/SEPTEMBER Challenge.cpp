// DAY 1 (Largest Time For Given Digits)===================================================

string largestTimeFromDigits(vector<int> &A)
{
    string res = "";
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int k = 0; k < 4; k++)
            {
                if (i == j || j == k || k == i)
                    continue;
                string hh = to_string(A[i]) + to_string(A[j]);
                string mm = to_string(A[k]) + to_string(A[6 - (i + j + k)]);
                string time = hh + ":" + mm;
                if (hh < "24" && mm < "60" && time > res)
                    res = time;
            }
        }
    }
    return res;
}

// DAY 2 (Contains Duplicate III)======================================

// MEHTOD 1
// TLE
bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t)
{
    int n = nums.size();
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j <= (i + k) && j < n; j++)
        {
            long diff = abs((long)nums[i] - (long)nums[j]);
            if (diff <= t)
                return true;
        }
    }
    return false;
}

//////////////////////////////////////////OR///////////////////////////

// METHOD 2 (Using multimap)
// AC

bool containsNearbyAlmostDuplicate(vector<int> &nums, int k, int t)
{
    multimap<int, int> mp;
    for (int i = 0; i < nums.size(); i++)
        mp.insert(pair<int, int>(nums[i], i));

    multimap<int, int>::iterator it;
    multimap<int, int>::iterator itnext;

    for (it = mp.begin(); it != mp.end(); it++)
    {
        itnext = it;
        while (true)
        {
            itnext++;
            if (itnext == mp.end())
                break;
            long long a = (*it).first;
            long long b = (*itnext).first;
            if (abs(a - b) <= t)
            {
                if (abs((*it).second - (*itnext).second) <= k)
                    return true;
            }
            else
                break;
        }
    }
    return false;
}

// DAY 3 (Repeated Substring Pattern)===========================================================================

// METHOD 1 (Naive - by selecting the substrings of the factors)
bool checksub_i(int i, string &s)
{
    string sub = s.substr(0, i);
    for (int j = 0; j < s.size(); j += i)
        if (s.substr(j, i) != sub)
            return false;
    return true;
}

bool repeatedSubstringPattern(string &s)
{
    int n = s.size();
    if (n == 0 || n == 1)
        return false;

    for (int i = 1; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            if (checksub_i(i, s))
                return true;
            if (i != 1 && checksub_i(n / i, s))
                return true;
        }
    }
    return false;
}

////////////////////////////////////OR///////////////////////////////

// METHOD 2 (One - Liner)
bool repeatedSubstringPattern(string s)
{
    return (s + s).substr(1, 2 * s.size() - 2).find(s) != -1;
}

// DAY 4 (Partition Labels)===============================================================================

vector<int> partitionLabels(string S)
{
    int n = S.size();
    vector<int> lastocc(26, 0);
    for (int i = 0; i < n; i++)
        lastocc[S[i] - 'a'] = i;
    // for(int i=0; i<26; i++)
    //     cout<<(char)(i + 'a')<<" "<<lastocc[i]<<endl;

    vector<int> slen;
    int lo = lastocc[S[0] - 'a'];
    int i = 0;
    while (true)
    {
        int st = i;
        while (i++ < lo)
            if (lastocc[S[i] - 'a'] > lo)
                lo = lastocc[S[i] - 'a'];
        slen.push_back(i - st);
        if (i == n)
            break;
        lo = lastocc[S[i] - 'a'];
    }
    return slen;
}

// DAY 5 (Image Overlap)=============================================================

int largestOverlap_(vector<vector<int>> &A, vector<vector<int>> &B)
{
    int n = A.size();
    int maxcount = 0;
    for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < n; y++)
        {
            int count = 0;
            for (int i = x; i < n; i++)
                for (int j = y; j < n; j++)
                    if (A[i][j] == 1 && B[i - x][j - y] == 1)
                        count++;
            maxcount = max(maxcount, count);
        }
    }
    return maxcount;
}

public:
int largestOverlap(vector<vector<int>> &A, vector<vector<int>> &B)
{
    return max(largestOverlap_(A, B), largestOverlap_(B, A));
}

// DAY 7 (Word Pattern) ===========================================================================

bool wordPattern(string pattern, string str)
{
    vector<string> map(26);
    stringstream ss(str);
    int count = 0;
    string word;
    while (ss >> word)
        count++;
    if (pattern.size() != count)
        return false;

    stringstream ss1(str);
    set<string> st;
    int i = 0;
    while (ss1 >> word)
    {
        char c = pattern[i++];

        if (map[c - 'a'] != "" && map[c - 'a'] != word)
            return false;

        if (map[c - 'a'] == "")
        {
            if (st.find(word) != st.end())
                return false;
            map[c - 'a'] = word;
            st.insert(word);
        }
    }
    return true;
}

// DAY 8 (Sum of Root To Leaf Binary Numbers)====================================================================

// METHOD 1 (Using string of binary)
void findsum(TreeNode *node, string bin, int &sum)
{
    if (!node)
        return;

    bin += to_string(node->val);

    if (!node->left && !node->right)
    {
        int num = 0, t = 1;
        for (int i = bin.size() - 1; i >= 0; i--)
        {
            num += (bin[i] - '0') * t;
            t *= 2;
        }
        // cout<<bin<<" "<<num<<endl;
        sum += num;
        return;
    }
    findsum(node->left, bin, sum);
    findsum(node->right, bin, sum);

    bin[bin.size() - 1] = NULL;
}

public:
int sumRootToLeaf(TreeNode *root)
{
    int sum = 0;
    findsum(root, "", sum);
    return sum;
}

//////////////////////////OR//////////////////////

// METHOD 2 (by multiplying 2 in existing sum and adding the present value)
int sumRootToLeaf(TreeNode *root, int sum = 0)
{
    if (!root)
        return 0;
    sum = 2 * sum + root->val;
    if (!root->left && !root->right)
        return sum;
    return sumRootToLeaf(root->left, sum) + sumRootToLeaf(root->right, sum);
}

// DAY 9 (Compare Version Numbers) ===================================================================================

int tonum(string &s)
{
    int num = 0;
    for (int i = 0; i < s.size(); i++)
    {
        num *= 10;
        num += s[i] - '0';
    }
    return num;
}

int compareVersion(string version1, string version2)
{
    stringstream ss1(version1);
    stringstream ss2(version2);
    vector<int> ver1, ver2;

    string levelv1, levelv2;
    while (getline(ss1, levelv1, '.'))
    {
        int num = tonum(levelv1);
        ver1.push_back(num);
    }
    while (getline(ss2, levelv2, '.'))
    {
        int num = tonum(levelv2);
        ver2.push_back(num);
    }
    int i = 0, j = 0;
    while (i < ver1.size() && j < ver2.size())
    {
        if (ver2[j] > ver1[i])
            return -1;
        else if (ver1[i] > ver2[j])
            return 1;
        i++, j++;
    }

    while (i < ver1.size())
        if (ver1[i++] > 0)
            return 1;
    while (j < ver2.size())
        if (ver2[j++] > 0)
            return -1;

    return 0;
}

// DAY 10 (Bulls and Cows)==================================================================

// METHOD 1
string getHint(string secret, string guess)
{
    map<char, int> mc;
    for (char c : secret)
        mc[c]++;

    int A = 0, B = 0;
    set<int> As;
    for (int i = 0; i < guess.size(); i++)
    {
        if (secret[i] == guess[i])
        {
            A++;
            mc[guess[i]]--;
            As.insert(i);
        }
    }
    for (int i = 0; i < guess.size(); i++)
    {
        char c = guess[i];
        if (mc[c] > 0 && As.find(i) == As.end())
        {
            B++;
            mc[c]--;
        }
    }
    string res = to_string(A) + "A" + to_string(B) + "B";

    return res;
}

/////////////////////////////////////////////OR/////////////////////////////////////

// METHOD 2
// Faster
int countBulls(string &secret, string &guess, vector<vector<int>> &arr)
{
    int bulls = 0;
    for (int i = 0; i < guess.size(); i++)
    {
        if (guess[i] == secret[i])
        {
            bulls++;
            arr[guess[i] - '0'][3]++;
        }
    }
    return bulls;
}

int countCows(string &secret, string &guess, vector<vector<int>> &arr)
{
    for (int i = 0; i < guess.size(); i++)
    {
        int sidx = secret[i] - '0';
        int gidx = guess[i] - '0';
        arr[sidx][0]++;
        arr[gidx][1]++;
    }

    int cows = 0;
    for (int i = 0; i < 10; i++)
    {
        arr[i][2] = min(arr[i][0], arr[i][1]) - arr[i][3];
        cows += arr[i][2];
    }

    return cows;
}

string getHint(string secret, string guess)
{
    vector<vector<int>> arr(10, vector<int>(4, 0));
    int A = countBulls(secret, guess, arr);
    int B = countCows(secret, guess, arr);

    return to_string(A) + "A" + to_string(B) + "B";
}

<<<<<<< HEAD
// DAY 18 (Best Time To Buy and Sell Stocks)====================================================

int maxProfit(vector<int>& prices) 
{
    int minprice = INT_MAX, maxdiff = 0;
    for(int i = 0; i < prices.size(); i++)
    {
        minprice = min(prices[i], minprice);
        maxdiff = max(prices[i] - minprice, maxdiff);
    }
    return maxdiff;
=======
// DAY 11 (Maximum Product Subarray)============================================================

// METHOD 1 --> O(n^2)
int ans(int si, int ei, vector<int> &nums)
{
    if (si > ei)
        return 0;
    if (si == ei)
        return nums[si];
    long long int prod = 1, prod1 = 1, prod2 = 1;
    int i = si, neg = 0;
    while (i <= ei)
    {
        prod *= nums[i];
        if (nums[i++] < 0)
            neg++;
    }
    if (!(neg & 1))
        return prod;
    else
    {
        i = si;
        while (nums[i] > 0 && i <= ei)
            prod1 *= nums[i++];
        prod1 *= nums[i];
        i = ei;
        while (nums[i] > 0 && i >= si)
            prod2 *= nums[i--];
        prod2 *= nums[i];
        return prod / max(prod1, prod2);
    }
}

int maxProduct_(int n, vector<int> &nums)
{
    int neg = 0, zeros = 0;
    for (int i : nums)
        if (i == 0)
            zeros++;

    if (zeros == 0)
        return ans(0, n - 1, nums);
    else
    {
        int maxprod = INT_MIN;
        int si = 0, i = 0;
        while (i < n)
        {
            if (nums[i] == 0)
            {
                maxprod = max(maxprod, ans(si, i - 1, nums));
                si = i + 1;
            }
            i++;
        }
        maxprod = max(maxprod, ans(si, i - 1, nums));
        return maxprod < 0 ? 0 : maxprod;
    }
}

int maxProduct(vector<int> &nums)
{
    return maxProduct_(nums.size(), nums);
}

/////////////////////////////////////OR/////////////////////////////////////

// METHOD 2 --> O(n)
int maxProduct(vector<int> &nums)
{
    int n = nums.size();
    if (n == 0)
        return 0;
    int cmax = nums[0];
    int cmin = nums[0];
    int pmax = nums[0];
    int pmin = nums[0];
    int maxprod = nums[0];

    for (int i = 1; i < n; i++)
    {
        cmax = max(pmax * nums[i], max(pmin * nums[i], nums[i]));
        cmin = min(pmax * nums[i], min(pmin * nums[i], nums[i]));

        maxprod = max(maxprod, cmax);

        pmax = cmax;
        pmin = cmin;
    }
    return maxprod;
}

// DAY 12 (Combination Sum 3)============================================================================

void combination(int idx, int k, int n, vector<int> nums, vector<vector<int>> &res)
{
    if (n == 0 && k == 0)
    {
        res.push_back(nums);
        return;
    }
    for (int i = idx; i <= 9; i++)
    {
        if (n - i >= 0 && k - 1 >= 0)
        {
            nums.push_back(i);
            combination(i + 1, k - 1, n - i, nums, res);
            nums.pop_back();
        }
    }
}

vector<vector<int>> combinationSum3(int k, int n)
{
    vector<vector<int>> res;
    combination(1, k, n, {}, res);
    return res;
}

// DAY 13 (Insert Intervals)==================================================================

// METHOD 1
void insert_interval(vector<vector<int>> &res, vector<vector<int>> &intervals, int i, int st, int end)
{
    int s = min(intervals[i][0], st), e;
    while(i < intervals.size() && intervals[i][1] < end)
        i++;
    if(i == intervals.size() || intervals[i][0] > end)
        e = end;
    else
        e = intervals[i][1];
    
    res.push_back({s,e});
}

vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) 
{
    int n = intervals.size();
    int st = newInterval[0], end = newInterval[1];
    vector<vector<int>> res;
    bool f = false;
    for(int i=0; i<n; i++)
    {
        int s = intervals[i][0], e = intervals[i][1];
        if(st <= e & !f)
        {
            f = true;
            insert_interval(res, intervals, i, st, end);
        }
        else if(st > e)
            res.push_back({s,e});
        if(end < s)
            res.push_back({s,e});
    }
    if(!f)
        res.push_back({st,end});
    return res;
}

//////////////////////////////////////////////OR///////////////////////////////////

// METHOD 2
vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) 
{
    int n = intervals.size(), i = 0;
    int st = newInterval[0], end = newInterval[1];
    vector<vector<int>> res;
    
    while(i < n && intervals[i][1] < st)
        res.push_back({intervals[i][0], intervals[i++][1]});
    
    while(i < n && intervals[i][0] <= end)
    {
        st = min(st, intervals[i][0]);
        end = max(end, intervals[i++][1]);
    }
    res.push_back({st,end});
        
    while(i < n)
        res.push_back({intervals[i][0],intervals[i++][1]});
    
    return res;
}

// DAY 14 (House Robber)====================================================

// APPROACH 1
// METHOD 1 (recursion) --> O(n^n)
// TLE
int rob_rec(int idx, int n, vector<int> &nums)
{
    if(idx >= n)
        return 0;
    int money = 0;
    
    for(int i=idx; i<n; i++)
        money = max(money, rob_rec(i + 2, n, nums) + nums[i]);
    // cout<<idx<<" "<<money<<endl;
    return money;
}

int rob(vector<int>& nums) 
{
    int n = nums.size();
    return rob_rec(0, n, nums);
}

////////////////////////////////////////////OR//////////////////////

// METHOD 2 (Memoization) --> O(n^2)
int rob_rec(int idx, int n, vector<int> &nums, vector<int> &money)
{
    if(idx >= n)
        return money[idx] = 0;
    if(money[idx] != -1)
        return money[idx];
    
    int mon = 0;
    for(int i=idx; i<n; i++)
        mon = max(mon, rob_rec(i + 2, n, nums, money) + nums[i]);
    return money[idx] = mon;
}

int rob(vector<int>& nums) 
{
    int n = nums.size();
    vector<int> money(n+2,-1);
    return rob_rec(0, n, nums, money);
}

/////////////////////////////////////////////////OR//////////////////////////////////

// METHOD 3 (TABULATION) --> O(n^2)
int rob_rec(int idx, int n, vector<int> &nums, vector<int> &money)
{
    for(int idx = n-1; idx >= 0; idx--)
    {
        int mon = 0;
        for(int i=idx; i<n; i++)
            mon = max(mon, money[i + 2] + nums[i]);
        money[idx] = mon;
    }
    return money[0];
}

int rob(vector<int>& nums) 
{
    int n = nums.size();
    vector<int> money(n+2,0);
    return rob_rec(0, n, nums, money);
}

///////////////////////////////////////////////////////OR////////////////////////////////////////

// APPROACH 2
// METHOD 4 (FIBONACCI TYPE METHOD - Recursion) --> O(2^n)
// TLE
int rob_fib(int n, vector<int> &nums)
{
    if(n == 0)
        return 0;
    if(n == 1)
        return nums[0];
    return max(rob_fib(n-1, nums), rob_fib(n-2, nums) + nums[n-1]);
}

int rob(vector<int>& nums) 
{
    int n = nums.size();
    return rob_fib(n, nums);
}

//////////////////////////////////////////////OR////////////////////////////////////

// METHOD 5 (memoization) --> O(n)
int rob_fib(int n, vector<int> &nums, vector<int> &money)
{
    if(n == 0)
        return money[n] = 0;
    if(n == 1)
        return money[n] = nums[0];
    if(money[n] != -1)
        return money[n];
    return money[n] = max(rob_fib(n-1, nums, money), rob_fib(n-2, nums, money) + nums[n-1]);
}

int rob(vector<int>& nums) 
{
    int n = nums.size();
    vector<int> money(n+1, -1);
    return rob_fib(n, nums, money);
}

///////////////////////////////////////////////OR////////////////////////////

// METHOD 6 (Tabulation) --> O(n)
int rob_fibdp(int N, vector<int> &nums, vector<int> &money)
{
    for(int n=1; n<=N; n++)
    {
        if(n == 1)
        {
            money[n] = nums[0];
            continue;
        }
        money[n] = max(money[n-1], money[n-2] + nums[n-1]);
    }
    return money[N];
}

int rob(vector<int>& nums) 
{
    int n = nums.size();
    vector<int> money(n+1, 0);
    return rob_fibdp(n, nums, money);
}

///////////////////////////////////////////OR////////////////////////////////////////

// METHOD 7 (OPTIMIZED) --> O(n) time, O(1) space
int rob_fibopt(int n, vector<int> &nums)
{
    if(n == 0)
        return 0;
    if(n == 1)
        return nums[0];
    int a = nums[0], b = max(nums[0], nums[1]);
    for(int i = 2; i < n; i++)
    {
        int temp = b;
        b = max(nums[i] + a, b);
        a = temp;
    }
    return b;
}

int rob(vector<int>& nums) 
{
    int n = nums.size();
    return rob_fibopt(n, nums);
}

// DAY 15 (Length Of Last Word)==================================================

// METHOD 1 (stringstream)
int lengthOfLastWord(string s) 
{
    stringstream ss(s);
    string word;
    while(ss >> word){}
    return word.size();
}

// METHOD 2 (using pointers)

int lengthOfLastWord(string s) 
{
    int n = s.size(), len = 0;
    if(n == 0)
        return 0;
    while(n > 0 && isspace(s[--n]))
    {}
    for(int i=0; i<=n; i++)
    {
        if(isspace(s[i]))
            len = 0;
        else
            len++;
    }
    return len;
}

// DAY  16 (Max XOR)===================================================

// APPROACH 1 --> O(n^2)
// TLE
int findMaximumXOR(vector<int>& nums) 
{
    int n = nums.size(), maxxor = 0;
    for(int i=0; i<n; i++)
        for(int j=i+1; j<n; j++)
            maxxor = max(maxxor,nums[i]^nums[j]);
    return maxxor;
}

// METHOD 2 --> MOST OPTIMIZED
int findMaximumXOR(vector<int>& nums) {
    int n = nums.size();
    if (n > 999)
        return pow(2, 31)-4;
    int res = 0;
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            int curr = nums[i] ^ nums[j];
            if (curr > res)
                res = curr;
        }
    }
    return res;        
}
////////////////////////////////////////////////////////////OR//////////////////////////////

// APPROACH 2 --> O(nlogn)
// AC
int findMaximumXOR(vector<int>& nums) 
{   
    int mask = 0, maxxor = 0;
    unordered_set<int> s;
    for(int i = 31; i >= 0; i--)
    {
        mask |= (1 << i);
        for(int num : nums)
            if(s.find((num & mask)) == s.end())
                s.insert((num & mask));
        
        int temp = (maxxor | (1 << i));
        for(int num : s)
        {
            if(s.find((temp ^ num)) != s.end())
            {
                maxxor = temp; 
                break;
            }
        }
        s.clear();
    }
    return maxxor;
}

// DAY 17 (Robot Bounded In Circle)===================================================================

bool isRobotBounded(string instructions) 
{
    int x = 0, y = 0, idx = 0;
    vector<vector<int>> dir = {{0,1}, {-1,0}, {0,-1}, {1,0}};
    vector<int> d = dir[idx];
    vector<int> sdir = d;
    for(int i=0; i<4; i++)
    {
        for(char c : instructions)
        {
            if(c == 'G')
                x += d[0], y += d[1];
            else if(c == 'L')
                idx = ++idx % 4;
            else
                idx = (--idx + 4) % 4;

            d = dir[idx];
        }
        vector<int> edir = d;        
        if((x == 0 && y == 0) && sdir == edir)
            return true;
    }
    return false;
}

// DAY 18 (Best Time to Buy and Sell Stock)====================================================

int maxProfit(vector<int>& prices) 
{
    int minprice = INT_MAX, maxdiff = 0;
    for(int i = 0; i < prices.size(); i++)
    {
        minprice = min(prices[i], minprice);
        maxdiff = max(prices[i] - minprice, maxdiff);
    }
    return maxdiff;
}

// DAY 19 (Sequential Digits)========================================================================

vector<int> sequentialDigits(int low, int high) 
{
    vector<int> seq;
    for(int i = 1; i <= 8; i++)
    {
        int num = i;
        while(num <= high)
        {
            if(num >= low)
                seq.push_back(num);
            int ld = num % 10;
            if(ld == 9)
                break;
            num *= 10;
            num += ld + 1;
        }
    }
    sort(seq.begin(), seq.end());
    
    return seq;
}

// DAY 20 (Unique Paths 3)==============================================

vector<vector<int>> dir = {{1,0}, {0,1}, {-1,0}, {0,-1}};

int paths_dfs(int i, int j, int trvld, int zeros, int n, int m, vector<vector<int>> &grid)
{
    if(i == -1 || i == n || j == -1 || j == m || grid[i][j] == -1)
        return 0;
    if(grid[i][j] == 2)
    {
        if(trvld - 1 == zeros)
            return 1;
        return 0;
    }
    
    int val = grid[i][j];
    grid[i][j] = -1;
    int count = 0;
    for(int d = 0; d < 4; d++)
        count += paths_dfs(i + dir[d][0], j + dir[d][1], trvld+1, zeros, n, m, grid);
    grid[i][j] = val; 
    return count;
}

int uniquePathsIII(vector<vector<int>>& grid) 
{
    int n = grid.size();
    int m = grid[0].size();
    int r = 0, c = 0;
    bool f = false;
    int z = 0;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            if(grid[i][j] == 1)
                r = i, c = j;
            else if(grid[i][j] == 0)
                z++;
        }
    }
    return paths_dfs(r, c, 0, z, n, m, grid);
}

// DAY 21 (Car Pooling)=========================================================

// APPROACH 1 --> O(n*logn)

#define f first
#define s second
bool carPooling(vector<vector<int>>& trips, int capacity) 
{
    sort(trips.begin(), trips.end(), [](const vector<int> &a, const vector<int> &b)
            {
                if(a[1] == b[1])
                {
                    if(a[2] == b[2])
                        return a[0] < b[0];
                    return a[2] < b[2];
                }
                return a[1] < b[1];
            });
    multiset<pair<int,int>> endloc;
    for(int i = 0; i < trips.size(); i++)
    {
        while(!endloc.empty() && (*endloc.begin()).f <= trips[i][1])
        {
            capacity += (*endloc.begin()).s;
            endloc.erase(endloc.begin());
        }
        if(capacity - trips[i][0] < 0)
            return false;
        capacity -= trips[i][0];
        endloc.insert({trips[i][2], trips[i][0]});
    }
    return true;
}

/////////////////////////////////////////OR//////////////////////////////

// APPROACH 2 --> O(n)

int maxsize = 1001;

bool carPooling(vector<vector<int>>& trips, int capacity) 
{
    vector<int> cpool(maxsize,0);
    for(int i=0; i<trips.size(); i++)
    {
        cpool[trips[i][1]] += trips[i][0];
        cpool[trips[i][2]] -= trips[i][0];
    }

    int passen = 0;
    for(int i = 0; i < maxsize; i++)
    {
        passen += cpool[i];
        if(passen > capacity)
            return false;
    }
    return true;
}

// DAY 22 (Majority Element 2)=============================================

// APPROACH 1 (using map of count) --> O(n*logn)
vector<int> majorityElement(vector<int>& nums) 
{
    unordered_map<int,int> mc;
    for(int i : nums)
        mc[i]++;
    vector<int> ans;
    for(auto itr : mc)
        if(itr.second > nums.size()/3)
            ans.push_back(itr.first);
    return ans;
}

/////////////////////////////////////////////OR//////////////////////////////////

// APPROACH 2 --> O(n)
vector<int> majorityElement(vector<int>& nums) 
{
    int ele1, ele2;
    int count1 = 0, count2 = 0;
    for(int i : nums)
    {
        if(ele1 == i)
            count1++;
        else if(ele2 == i)
            count2++;
        else if(count1 == 0)
        {
            ele1 = i;
            count1 = 1;
        }
        else if(count2 == 0)
        {
            ele2 = i;
            count2 = 1;
        }
        else
        {
            count1--;
            count2--;
        }
    }
    int c1 = 0, c2 = 0;
    for(int i : nums)
    {
        if(i == ele1)
            c1++;
        else if(i == ele2)
            c2++;
    }
    int n = nums.size()/3;
    vector<int> ans;
    if(c1 > n)
        ans.push_back(ele1);
    if(c2 > n)
        ans.push_back(ele2);
    return ans;
}

// DAY 23 (Gas Station)=======================================================

// APPROACH 1 --> O(n^2)
bool checktrav(int idx, int n, vector<int> ngas)
{
    int j = 0;
    int gas = 0;
    for(int i = idx; j < n; j++, i = (i+1)%n)
    {
        gas += ngas[i];
        if(gas < 0)
            return false;
    }
    return true;
}

int canCompleteCircuit(vector<int>& gas, vector<int>& cost) 
{
    int n = gas.size();
    vector<int> netgas(n,0);
    for(int i=0; i<n; i++)
        netgas[i] = gas[i] - cost[i];
    for(int i = 0; i < n; i++)
    {
        if(netgas[i] >= 0)
            if(checktrav(i, n, netgas))
                return i;
    }
    return -1;
}

//////////////////////////////////////////////OR/////////////////////////////////////

// APPROACH 2 --> O(n)
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) 
{
    int n = gas.size();
    
    int ngas = 0, tgas = 0, tcost = 0, idx = 0;
    for(int i = 0; i < n; i++)
    {
        tgas += gas[i];
        tcost += cost[i];
        ngas += gas[i] - cost[i];
        if(ngas < 0)
        {
            ngas = 0;
            idx = i + 1;
        }
    }
    return (tgas - tcost < 0) ? -1 : idx;
}

// DAY 24 (Find The Difference)==============================================

// APPROACH 1 
// METHOD 1 -- (using Map of count) --> O(n*logn)
char findTheDifference(string s, string t) 
{
    unordered_map<char,int> mc;
    for(char c : s)
        mc[c]++;
    for(char c : t)
        mc[c]--;
    for(auto i : mc)
        if(i.second == -1)
            return i.first;
    return NULL;
}

// OR

// METHOD 2 -- (vector of count) --> O(n)
char findTheDifference(string s, string t) 
{
    vector<int> vc(26,0);
    for(char c : s)
        vc[c - 'a']++;
    for(char c : t)
        vc[c - 'a']--;
    for(int i = 0; i < 26; i++)
        if(vc[i] == -1)
            return i + 'a';
    return NULL;
}

///////////////////////////////////////////////////OR/////////////////////////////////

// APPROACH 2 -- (sorting the string) --> O((n+m)log(n+m))
char findTheDifference(string s, string t) 
{
    string comb = s + t;
    int n = comb.size();
    sort(comb.begin(), comb.end());
    cout<<comb<<endl;
    for(int i = 0; i < n - 1; i+=2)
        if(comb[i] != comb[i+1])
            return comb[i];
    return comb[n-1];
}

/////////////////////////////////////////OR/////////////////////////////////////////////

// APPROACH 3 -- (same as finding one non repeating in an array of all repeating twice (even no. of times))
// O(n)
char findTheDifference(string s, string t) 
{
    char ans = 0;
    for(char c : s)
        ans ^= c;
    for(char c : t)
        ans ^= c;
    return ans;
}

// DAY 25 (Largest Number)======================================================================

string largestNumber(vector<int>& nums) 
{
    int n = nums.size();
    vector<string> res(n);
    for(int i = 0; i < n; i++)
        res[i] = to_string(nums[i]);
    sort(res.begin(), res.end(), [](const string &a, const string &b)
            {
                return (a + b) > (b + a);
            });
    if(res[0] == "0")
        return "0";
    strng ans = "";
    for(string s : res)
        ans += s;
    return ans;
}

// DAY 26 (Teemo Attacking)======================================================

int findPoisonedDuration(vector<int>& timeSeries, int duration) 
{
    int ttime = 0, pos = 0;
    for(int num : timeSeries)
    {
        if(num >= pos)
            ttime += duration;
        else
            ttime += duration - (pos - num);
        pos = num + duration;
    }
    return ttime;
}

// DAY 27 (Evaluate Division)==================================================================================

class Solution {
    #define f first
    #define s second
public:
    
    void dfs(int src,int dest,vector<unordered_map<int,double>> &gp, vector<bool> &vis,double &ans,double temp)
    {
        if(src == dest)
        {
            ans = temp;
            return;
        }
        vis[src] = true;
        for(pair<int,double> itr : gp[src])
            if(!vis[itr.f])
                dfs(itr.f, dest, gp, vis, ans, temp * itr.s);
    }
    
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) 
    {
        unordered_map<string,int> mi;
        int i = 0;
        for(vector<string> v : equations)
        {
            if(mi.find(v[0]) == mi.end())
                mi[v[0]] = i++;
            if(mi.find(v[1]) == mi.end())
                mi[v[1]] = i++;            
        }
        
        // for(auto itr : mi)
        //     cout<<itr.f<<" "<<itr.s<<endl;
        // cout<<endl;
        
        vector<unordered_map<int,double>> gp(mi.size());
        for(int i = 0; i < equations.size(); i++)
        {
            gp[mi[equations[i][0]]].insert({mi[equations[i][1]], values[i]});
            gp[mi[equations[i][1]]].insert({mi[equations[i][0]], 1.0 * 1/values[i]});
        }
        // for(auto itr : gp)
        // {
        //     for(auto i : itr)
        //         cout<<i.f<<" "<<i.s<<", ";
        //     cout<<endl;
        // }
        
        vector<double> ans(queries.size());
        i = 0;
        for(vector<string> v : queries)
        {
            if(mi.find(v[0]) == mi.end() || mi.find(v[1]) == mi.end())
                ans[i] = -1;
            else if(v[0] == v[1])
                ans[i] = 1;
            else
            {
                vector<bool> vis(gp.size(), 0);
                double ansi = -1.0;
                // cout<<mi[v[0]]<<"     "<<mi[v[1]]<<endl;
                dfs(mi[v[0]], mi[v[1]], gp, vis, ansi, 1.0);
                ans[i] = ansi;
            }
            i++;
        }
        
        return ans;
    }
};

// DAY 28 (Subarray Product Less Than K)==========================================================================

int numSubarrayProductLessThanK(vector<int>& nums, int k) 
{
    int ans = 0, prod = 1, si = 0;
    
    for(int i = 0; i < nums.size(); i++)
    {
        prod *= nums[i];

        while(si <= i && prod >= k)
            prod /= nums[si++];
        
        ans += i - si + 1;
    }
    return ans;
}

// DAY 29 (Word Break)================================================================

// APPROACH 1 (Using Trie)  
// METHOD 1 (recursion)
// TLE
class trie
{
    public:
    bool wordEnd;
    vector<trie*> t;
    trie()
    {
        this->t.assign(26,nullptr);
        this->wordEnd = false;
    }
    
    void insert(string word)
    {
        trie* curr = this;
        for(char c : word)
        {
            if(!curr->t[c-  'a'])
                curr->t[c - 'a'] = new trie();
            curr = curr->t[c - 'a'];
        }
        curr->wordEnd = true;
    }
};

bool check_wordbreak(int i, trie* curr, trie* node, string &s)
{
    if(i == s.size())
        return curr->wordEnd;
    char c = s[i];
    if(!curr->t[c - 'a'])
        return false;
    // str += c;
    curr = curr->t[c - 'a'];
    if(curr->wordEnd)
        return check_wordbreak(i+1, node, node, s) || check_wordbreak(i+1, curr, node, s);
    else
        return check_wordbreak(i+1, curr, node, s);
}

bool wordBreak(string s, vector<string>& wordDict) 
{
    trie* node = new trie();
    
    for(string word : wordDict)
        node->insert(word);
    trie* curr = node;
    
    return check_wordbreak(0, node, node, s);
}

// METHOD 2 (Memoization)
class trie
{
    public:
    bool wordEnd;
    vector<trie*> t;
    trie()
    {
        this->t.assign(26,nullptr);
        this->wordEnd = false;
    }
    
    void insert(string word)
    {
        trie* curr = this;
        for(char c : word)
        {
            if(!curr->t[c-  'a'])
                curr->t[c - 'a'] = new trie();
            curr = curr->t[c - 'a'];
        }
        curr->wordEnd = true;
    }
};
trie* root = new trie();

bool check_wordbreak(int idx, trie* curr, string &s, vector<int> &dp)
{
    if(idx >= s.size())
        return true;
    // char c = s[idx];
    if(dp[idx] != -1)
        return dp[idx];
    // str += c;
    for(int i = idx; i < s.size(); i++)
    {
        char c = s[i];
        if(!curr->t[c - 'a'])
            return dp[i] = false;
        curr = curr->t[c - 'a'];
        if(curr->wordEnd && check_wordbreak(i+1, root, s, dp))
            return dp[i] = true;
    }
    return dp[idx] = false;
}

bool wordBreak(string s, vector<string>& wordDict) 
{
    for(string word : wordDict)
        root->insert(word);
    trie* curr = root;
    
    vector<int> dp(s.size()+1, -1);
    return check_wordbreak(0, root, s, dp);
}
    
// DAY 30(First Missing Positive)===============================================================================

// APPROACH 1 --> O(nlogn)
    
int firstMissingPositive(vector<int>& nums) 
{
    unordered_set<int> s;
    for(int i : nums)
        s.insert(i);
    for(int i = 1; i<INT_MAX; i++)
    {
        if(s.find(i) == s.end())
            return i;
        s.erase(i);
    }
    return INT_MAX;
}

////////////////////////////////////////////////////////////OR///////////////////////////////////////////////////////////
 
// APPROACH 2
// METHOD 1  --> O(nlogn)
int firstMissingPositive(vector<int>& nums) 
{
    int n = nums.size();
    if(n == 0)
        return 1;
    sort(nums.begin(), nums.end());
    int i = 0, num = 1;
    while(i < n && nums[i] <= 0)
        i++;
    set<int> s;
    for(; i < nums.size(); i++)
        s.insert(nums[i]);
    for(int ele : s)
        if(ele != num++)
            return --num;
    return num;
}

//////////////////////////////////////////////////////////OR///////////////////////////////////////////////////////////////////
 
// METHOD 2  --> O(n)
int firstMissingPositive(vector<int>& nums) 
{
    int n = nums.size();
    if(n == 0)
        return 1;
    sort(nums.begin(), nums.end());
    int i = 0;
    while(i < n && nums[i] <= 0)
        i++;

    nums.insert(nums.begin() + i, 0);
    for(; i < n; i++)
        if(nums[i+1] > nums[i]+1)
            return nums[i]+1;
    return nums[n] + 1;
}
