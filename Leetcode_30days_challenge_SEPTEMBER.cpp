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