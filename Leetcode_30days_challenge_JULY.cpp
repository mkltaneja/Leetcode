// DAY 1 (Arranging coins)=======================================

// Brute force
// O(sqrt(n))
int arrangeCoins(int n)
{
    int i = 1, count = 0;
    while ((n - i) >= 0)
    {
        count++;
        n -= i;
        i++;
    }
    return count;
}

// O(logn)
int arrangeCoins(int n)
{
    int si = 0, ei = n;
    while (si <= ei)
    {
        long int mid = si + (ei - si) / 2;
        if ((mid * (mid + 1)) / 2 == n)
            return mid;
        else if ((mid * (mid + 1)) / 2 < n)
            si = mid + 1;
        else
            ei = mid - 1;
    }
    return ei;
}

///////////////////OR////////////////////\

// O(1)
int arrangeCoins(int n)
{
    return (int)(-0.5 + sqrt(0.25 + (long int)2 * n));
}

// DAY 2 (Binary Tree Level Order Traversal 2)====================================================================

// BFS
vector<vector<int>> levelOrderBottom(TreeNode *root)
{
    if (root == nullptr)
        return {};
    queue<TreeNode *> que;
    que.push(root);
    vector<vector<int>> ans;
    ans.push_back({root->val});
    while (!que.empty())
    {
        vector<int> level;
        int size = que.size();
        while (size--)
        {
            TreeNode *top = que.front();
            que.pop();
            TreeNode *l = top->left;
            TreeNode *r = top->right;
            if (l)
            {
                que.push(l);
                level.push_back(l->val);
            }
            if (r)
            {
                que.push(r);
                level.push_back(r->val);
            }
        }
        if (level.size())
            ans.push_back(level);
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

///////////////////////////OR//////////////////////

// recursion
int height(TreeNode *node)
{
    if (!node)
        return 0;
    return max(height(node->left), height(node->right)) + 1;
}

void level_rec(TreeNode *node, int level, int h, vector<vector<int>> &ans)
{
    if (!node)
        return;
    ans[level].push_back(node->val);
    if (node->left)
        level_rec(node->left, level + 1, h, ans);
    if (node->right)
        level_rec(node->right, level + 1, h, ans);
}

vector<vector<int>> levelOrderBottom(TreeNode *root)
{
    int h = height(root);
    // cout<<h<<endl;
    vector<vector<int>> ans(h, vector<int>());
    level_rec(root, 0, h, ans);
    reverse(ans.begin(), ans.end());
    return ans;
}

// DAY 3 (Prison Cells After N Days)============================================================
// O(8*N)
// TLE
vector<int> prisonAfterNDays(vector<int> &cells, int N)
{
    while (N--)
    {
        int prev, curr = cells[0];
        for (int i = 0; i < 6; i++)
        {
            prev = curr;
            curr = cells[i + 1];
            cells[i + 1] = !(prev ^ cells[i + 2]);
            // cout<<prev<<" "<<cells[i+1]<<" "<<cells[i+2]<<endl;
        }
        cells[0] = 0;
        cells[7] = 0;
    }
    return cells;
}

////////////////////////////////OR//////////////////////////////

// O(index of repetetion)
vector<int> prisonAfterNDays(vector<int> &cells, int N)
{
    unordered_map<string, int> m;
    for (int n = 0; n < N; n++)
    {
        string s(cells.begin(), cells.end());
        if (m.find(s) == m.end())
        {
            m.insert({s, n});
            int prev, curr = cells[0];
            for (int i = 0; i < 6; i++)
            {
                prev = curr;
                curr = cells[i + 1];
                cells[i + 1] = !(prev ^ cells[i + 2]);
                // cout<<prev<<" "<<cells[i+1]<<" "<<cells[i+2]<<endl;
            }
            cells[0] = 0;
            cells[7] = 0;
            for (int i = 0; i < 8; i++)
                cout << cells[i] << " ";
            cout << endl;
        }
        else
        {
            int len_of_repetetion = n - m[s];
            int rem_days = (N - n) % len_of_repetetion;
            return prisonAfterNDays(cells, rem_days);
        }
    }
    return cells;
}

// DAY 4 (Ugly number 2)===============================================================

// TLE
int nthUglyNumber(int n)
{
    long int i = 1;
    while (n)
    {
        int num = i;
        bool flag = true;
        while (num != 1)
        {
            if (num % 2 == 0)
                num /= 2;
            else if (num % 3 == 0)
                num /= 3;
            else if (num % 5 == 0)
                num /= 5;
            else
            {
                flag = false;
                break;
            }
        }
        if (flag)
            n--;
        i++;
    }
    return i - 1;
}

///////////////OR////////////////

int nthUglyNumber(int n)
{
    int ugly[n];
    ugly[0] = 1;
    int i = 1, i2 = 0, i3 = 0, i5 = 0;

    while (i < n)
    {
        int next2 = ugly[i2] * 2;
        int next3 = ugly[i3] * 3;
        int next5 = ugly[i5] * 5;
        int next = min(next2, min(next3, next5));
        if (next == next2)
            i2++;
        if (next == next3)
            i3++;
        if (next == next5)
            i5++;
        ugly[i++] = next;
    }
    // for(int i=0;i<n;i++)
    //     cout<<ugly[i]<<" ";
    return ugly[n - 1];
}

// DAY 5 (Hamming Distance)=====================================================================================

int hammingDistance(int x, int y)
{
    int ham_dist = 0;
    while (x || y)
    {
        if ((x & 1) ^ (y & 1))
            ham_dist++;
        x >>= 1;
        y >>= 1;
    }
    return ham_dist;
}

// DAY 6 (Plus One)===============================================================

vector<int> plusOne(vector<int> &digits)
{
    int n = digits.size();
    if (n == 0)
        return {1};

    int i = n - 1;
    while (i >= 0 && digits[i] == 9)
        digits[i--] = 0;
    if (i >= 0)
        digits[i]++;
    else
        digits.insert(digits.begin(), 1);
    return digits;
}

// DAY 7 (Island Perimeter)======================================================================

// O(4*n^2)
int islandPerimeter(vector<vector<int>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();

    int ones = 0, commreg = 0;
    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 1)
            {
                ones++;
                for (int d = 0; d < 4; d++)
                {
                    int r = i + dir[d][0];
                    int c = j + dir[d][1];
                    if (r >= 0 && c >= 0 && r < n && c < m && grid[r][c] == 1)
                        commreg++;
                }
            }
        }
    }
    return 4 * ones - commreg;
}

///////////////////OR///////////////////

// O(2*n^2)
int islandPerimeter(vector<vector<int>> &grid)
{
    int n = grid.size();
    int m = grid[0].size();

    int ones = 0, commreg = 0;
    int dir[4][2] = {{1, 0}, {0, 1}};
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (grid[i][j] == 1)
            {
                ones++;
                for (int d = 0; d < 2; d++)
                {
                    int r = i + dir[d][0];
                    int c = j + dir[d][1];
                    if (r < n && c < m && grid[r][c] == 1)
                        commreg++;
                }
            }
        }
    }
    return 4 * ones - 2 * commreg;
}

// DAY 8 (3Sum)=============================================================================

// O(n^3)
// TLE
vector<vector<int>> threeSum(vector<int> &nums)
{
    int n = nums.size();
    set<vector<int>> s;

    for (int i = 0; i < n - 2; i++)
    {
        int a = nums[i];
        for (int j = i + 1; j < n - 1; j++)
        {
            int b = nums[j];
            for (int k = j + 1; k < n; k++)
            {
                int c = nums[k];
                if (a + b + c == 0)
                {
                    vector<int> ar{a, b, c};
                    sort(ar.begin(), ar.end());
                    s.insert(ar);
                }
            }
        }
    }
    vector<vector<int>> ans;
    for (auto itr : s)
        ans.push_back(itr);

    return ans;
}

//////////////////OR//////////////////////

// O(N^3)  recursively
// TLE
void rec_sol(vector<int> &nums, int n, int count, int idx, int sum, vector<int> res, set<vector<int>> &ans)
{
    if (count == 3 || idx == n)
    {
        if (sum == 0)
        {
            ans.insert(res);
        }
        return;
    }
    int m;
    if (count == 0)
        m = n - 2;
    else if (count == 1)
        m = n - 1;
    else if (count == 2)
        m = n;

    for (int i = idx; i < m; i++)
    {
        res.push_back(nums[i]);
        rec_sol(nums, n, count + 1, i + 1, sum + nums[i], res, ans);
        res.pop_back();
    }
}

vector<vector<int>> threeSum(vector<int> &nums)
{
    int n = nums.size();
    if (n == 0)
        return {};
    sort(nums.begin(), nums.end());

    vector<vector<int>> ans;
    set<vector<int>> s;
    vector<int> a;
    rec_sol(nums, n, 0, 0, 0, a, s);

    for (auto itr : s)
        ans.push_back(itr);

    return ans;
}

//////////////OR//////////////

// O(n^2 * logn)
// TLE
vector<vector<int>> threeSum(vector<int> &nums)
{
    int n = nums.size();
    if (n == 0)
        return {};
    // cout<<n;
    sort(nums.begin(), nums.end()); // it makes sure that elements, adding in the set will be sorted (to                                                 check the repetetion of every vector in the set)
    vector<vector<int>> ans;
    set<vector<int>> s;

    for (int i = 0; i < n - 2; i++)
    {
        int a = nums[i];
        for (int j = i + 1; j < n - 1; j++)
        {
            int b = nums[j];
            int c = -(a + b);
            unordered_set<int> st(nums.begin() + j + 1, nums.end());
            if (st.find(c) != st.end())
                s.insert({a, b, c});
        }
    }

    for (auto itr : s)
        ans.push_back(itr);

    return ans;
}

//////////OR//////////

// O(n^2)
__ATOMIC_ACQ_REL
vector<vector<int>> threeSum(vector<int> &nums)
{
    int n = nums.size();
    if (n == 0)
        return {};
    // cout<<n;
    sort(nums.begin(), nums.end()); // it makes sure that elements, adding in the set will be sorted (to                                                 check the repetetion of every vector in the set)
    vector<vector<int>> ans;
    set<vector<int>> s;
    // vector<int> a;
    // vector<vector<set<vector<int>>>> dp(3, vector<set<vector<int>>>(n+1, set<vector<int>>()));
    // rec_sol(nums,n,0,0,0,a,s,dp);

    for (int i = 0; i < n - 2; i++)
    {
        int a = nums[i];
        int j = i + 1;
        int k = n - 1;
        while (j < k)
        {
            int b = nums[j];
            int c = nums[k];
            if (b + c < -a)
                j++;
            else if (b + c > -a)
                k--;
            else
            {
                s.insert({a, b, c});
                j++, k--;
            }
        }
    }

    for (auto itr : s)
        ans.push_back(itr);

    return ans;
}

////////////////OR////////////////

// O(n^2)  MOST OPTIMIZED
vector<vector<int>> threeSum(vector<int> &nums)
{
    int n = nums.size();
    if (n < 3)
        return {};
    // cout<<n;
    sort(nums.begin(), nums.end()); // it makes sure that elements, adding in the set will be sorted (to                                                 check the repetetion of every vector in the set)
    vector<vector<int>> ans;
    // vector<int> a;
    // vector<vector<set<vector<int>>>> dp(3, vector<set<vector<int>>>(n+1, set<vector<int>>()));
    // rec_sol(nums,n,0,0,0,a,s,dp);

    for (int i = 0; i < n - 2; i++)
    {
        int a = nums[i];
        int j = i + 1;
        int k = n - 1;
        if (i == 0 || nums[i] != nums[i - 1])
        {
            while (j < k)
            {
                int b = nums[j];
                int c = nums[k];
                if (b + c < -a)
                    j++;
                else if (b + c > -a)
                    k--;
                else
                {
                    ans.push_back({a, b, c});
                    while (j < k && nums[j] == b)
                        j++;
                    while (j < k && nums[k] == c)
                        k--;
                }
            }
        }
    }
    return ans;
}

// DAY 9 (Maximum Width Of Binary Tree)================================================================

// by using long to prevent signed integer overflow(Runtoime Error)
int widthOfBinaryTree(TreeNode *root)
{
    if (root == nullptr)
        return 0;
    queue<pair<TreeNode *, long>> que;
    que.push({root, 0});

    int maxwidth = 1;
    while (!que.empty())
    {
        int size = que.size();
        int start = que.front().second;
        int end = que.back().second;
        while (size--)
        {
            pair<TreeNode *, long> par = que.front();
            que.pop();

            if (par.first->left)
                que.push({par.first->left, (long)2 * par.second + 1});
            if (par.first->right)
                que.push({par.first->right, (long)2 * par.second + 2});
        }
        // cout<<start<<" "<<end<<endl;
        maxwidth = max(maxwidth, end - start + 1);
    }
    return maxwidth;
}

//////////////////////////OR//////////////////////////

// without using long to prevent signed integer overflow (Runtime error)
int widthOfBinaryTree(TreeNode *root)
{
    if (root == nullptr)
        return 0;
    queue<pair<TreeNode *, int>> que;
    que.push({root, 0});

    int maxwidth = 1;
    while (!que.empty())
    {
        int size = que.size();
        int start = que.front().second;
        int end = que.back().second;
        while (size--)
        {
            pair<TreeNode *, int> par = que.front();
            que.pop();
            int idx = par.second - start;

            if (par.first->left)
                que.push({par.first->left, 2 * idx + 1});
            if (par.first->right)
                que.push({par.first->right, 2 * idx + 2});
        }
        // cout<<start<<" "<<end<<endl;
        maxwidth = max(maxwidth, end - start + 1);
    }
    return maxwidth;
}
// DAY 10 (Flatten a Multilevel Doubly Linked List)===========================================================

Node *flatten(Node *head)
{
    Node *itr = head;
    while (itr)
    {
        if (itr->child)
        {
            Node *temp = itr->next;
            itr->next = nullptr;
            if (temp)
                temp->prev = nullptr;

            Node *chtemp = itr->child;
            itr->next = chtemp;
            chtemp->prev = itr;
            while (chtemp->next != nullptr)
                chtemp = chtemp->next;
            chtemp->next = temp;

            if (temp)
                temp->prev = chtemp;

            itr->child = nullptr;
        }
        itr = itr->next;
    }
    return head;
}

///////////////////////////OR////////////////////////////////

// by recursion
Node *flatten(Node *head)
{
    Node *itr = head;
    while (itr)
    {
        if (itr->child)
        {
            Node *temp = itr->next;
            itr->next = nullptr;
            if (temp)
                temp->prev = nullptr;

            Node *chtemp = itr->child;
            itr->next = flatten(chtemp);

            itr->next->prev = itr;
            while (chtemp->next != nullptr)
                chtemp = chtemp->next;
            chtemp->next = temp;

            if (temp)
                temp->prev = chtemp;

            itr->child = nullptr;
        }
        itr = itr->next;
    }
    return head;
}

///////////////OR///////////////////

// by combination
void subset_combi(vector<int> &nums, int idx, vector<vector<int>> &ans, vector<int> sub)
{
    ans.push_back(sub);
    for (int i = idx; i < nums.size(); i++)
    {
        sub.push_back(nums[i]);
        subset_combi(nums, i + 1, ans, sub);
        sub.pop_back();
    }
}

vector<vector<int>> subsets(vector<int> &nums)
{
    vector<vector<int>> ans;
    subset_combi(nums, 0, ans, {});
    return ans;
}
// DAY 12 (Reverse Bits)======================================================

uint32_t reverseBits(uint32_t n)
{
    uint32_t nn = 0;
    for (int i = 0; i < 32; i++)
    {
        uint32_t lsb = (n & 1);
        n >>= 1;

        nn <<= 1;
        nn |= lsb;
    }
    return nn;
}

// DAY 13(Same Tree)==========================================================

// recursion
bool checkisSameTree(TreeNode *p, TreeNode *q)
{
    bool res = true;

    if (p->val != q->val)
        return false;

    if (p->left && q->left)
        res &= checkisSameTree(p->left, q->left);
    else if (!p->left && q->left || p->left && !q->left)
        return false;

    if (p->right && q->right)
        res &= checkisSameTree(p->right, q->right);
    else if (!p->right && q->right || p->right && !q->right)
        return false;

    return res;
}

bool isSameTree(TreeNode *p, TreeNode *q)
{
    if (p == nullptr && q == nullptr)
        return true;
    else if ((p && !q) || (!p && q))
        return false;

    return checkisSameTree(p, q);
}

/////////////////////OR/////////////////////////////

// short recursion
bool isSameTree(TreeNode *p, TreeNode *q)
{
    if (!p && !q)
        return true;
    if (!p || !q)
        return false;
    if (p->val != q->val)
        return false;
    return isSameTree(p->left, q->left) && isSameTree(p->right, q->right);
}

// DAY 15 (Angle Between Hands of a Clock)==================================================

double angleClock(int hour, int minutes)
{
    double minute_angle = minutes * 6;
    double hour_angle = hour * 30;
    hour_angle += minute_angle / 12;
    // cout<<minute_angle<<" "<<hour_angle<<endl;

    return min(abs(hour_angle - minute_angle), 360 - abs(hour_angle - minute_angle));
}

///////////////////////OR//////////////////////////

double angleClock(int hour, int minutes)
{
    double minute_angle = minutes * 6;
    double hour_angle = (hour * 30) + (minutes / 2.0);

    return min(abs(hour_angle - minute_angle), 360 - abs(hour_angle - minute_angle));
}

// DAY 15(Reverse Words in a String)====================================================================

// Method 1 (naive method)
string reverseWords(string s)
{
    int n = s.size();
    int si = 0;
    while (isspace(s[si]))
        si++;
    int i = n - 1;
    string rev = "";
    while (i >= si)
    {
        string word = "";
        while (i >= si && !isspace(s[i]))
        {
            word += s[i];
            i--;
        }
        if (word.size() > 0)
        {
            reverse(word.begin(), word.end());
            rev += word;
            cout << i << endl;
            if (i > si)
                rev += " ";
        }
        i--;
    }
    cout << endl;
    return rev;
}

///////////////////////OR//////////////////////

// Method 2 (using stringstream)
string reverseWords(string s)
{
    int n = s.size();
    stringstream ss(s);
    string word;
    vector<string> rev;

    while (ss >> word)
        rev.push_back(word);

    string revstr = "";
    for (int i = rev.size() - 1; i >= 0; i--)
    {
        revstr += rev[i];
        if (i != 0)
            revstr += " ";
    }
    return revstr;
}

// DAY 16 (Pow(x,n))====================================

// Method 1 -> using pow() function
double myPow(double x, int n)
{
    return pow(x, n);
}

////////////////////OR/////////////////////

// Method 2 -> naive approach O(n)
// TLE

double pow(double x, int n)
{
    double x1 = x;
    while (--n)
        x1 *= x;
    return x1;
}

double myPow(double x, int n)
{
    if (n == 0)
        return 1;
    else if (n > 0)
        return pow(x, n);
    else
        return pow(1 / x, -n);
}

/////////////////OR///////////////////////

// Method 3 (Divide and Conquer) -> O(log n)==================================================

double pow(double x, unsigned int n)
{
    if (n == 0)
        return 1;
    double ans = pow(x, n / 2);
    ans *= ans;
    if (n & 1)
        ans *= x;
    return ans;
}

double myPow(double x, int n)
{
    if (n == 0 || x == 1)
        return 1;

    else if (n > 0)
        return pow(x, n);
    else
        return pow(1 / x, -(unsigned)n);
}

//////////////////////////OR////////////////////////////

// same as prev without conditions
double pow(double x, int n)
{
    if (n == 0)
        return 1;
    double ans = pow(x, n / 2);
    ans *= ans;
    if (n & 1)
        ans *= x;
    return ans;
}

double myPow(double x, int n)
{
    if (n == 0 || x == 1)
        return 1;
    if (n == -1)
        return 1 / x;

    double ans = pow(x, n);

    return (n < 0) ? 1 / ans : ans;
}

///////////////////OR//////////////////

// Method 4 (Iterative) -> O(log n)
double myPow(double x, int n)
{
    if (n == 0 || x == 1)
        return 1;
    if (n == -1)
        return 1 / x;

    double ans = 1;
    for (int i = n; i != 0; i /= 2)
    {
        if (i & 1)
            ans *= x;
        x *= x;
    }
    return (n < 0) ? 1 / ans : ans;
}

// DAY 17(Top K frequent elements)========================================

// Method 1 (using map with custom comparator) -> O(n)
static bool sortby_Second(pair<int, int> &a, pair<int, int> &b)
{
    return a.second < b.second;
}
vector<int> topKFrequent(vector<int> &nums, int k)
{
    int n = nums.size();
    map<int, int> m;
    for (int i : nums)
        m[i]++;

    vector<pair<int, int>> freqarr(m.begin(), m.end());
    sort(freqarr.begin(), freqarr.end(), sortby_Second);

    vector<int> kfreq;
    while (k--)
    {
        kfreq.push_back(freqarr.back().first);
        freqarr.erase(freqarr.end());
        if (freqarr.empty())
            break;
    }
    return kfreq;
}

////////////////////////////OR//////////////////////////////

// Method 2 (using map with lambda function)  O(n)
vector<int> topKFrequent(vector<int> &nums, int k)
{
    int n = nums.size();
    map<int, int> m;
    for (int i : nums)
        m[i]++;

    vector<pair<int, int>> freqarr(m.begin(), m.end());
    sort(freqarr.begin(), freqarr.end(), [](pair<int, int> &a, pair<int, int> &b) {
        return a.second < b.second;
    });

    vector<int> kfreq;
    while (k--)
    {
        kfreq.push_back(freqarr.back().first);
        freqarr.erase(freqarr.end());
        if (freqarr.empty())
            break;
    }
    return kfreq;
}

//////////////////////////////OR//////////////////////

// Method 3 (using hashmap and heap(priority queue)) O(nlogn)
struct customCompare
{
    bool operator()(const pair<int, int> &a, const pair<int, int> &b)
    {
        return a.second > b.second;
    }
};

vector<int> topKFrequent(vector<int> &nums, int k)
{
    int n = nums.size();
    unordered_map<int, int> m;
    for (int i : nums)
        m[i]++;
    priority_queue<pair<int, int>, vector<pair<int, int>>, customCompare> pq;
    for (pair<int, int> p : m)
    {
        pq.push(p);
        if (pq.size() > k)
            pq.pop();
    }

    vector<int> kfreq(k, 0);
    int i = 0;
    while (i < k && !pq.empty())
    {
        kfreq[i++] = pq.top().first;
        pq.pop();
    }
    return kfreq;
}

// DAY 18 (Course Schedule 2)==================================================================

vector<int> findOrder(int numCourses, vector<vector<int>> &prerequisites)
{
    vector<vector<int>> graph(numCourses, vector<int>());
    for (vector<int> ar : prerequisites)
        graph[ar[0]].push_back(ar[1]);

    queue<int> que;
    vector<int> inDegree(numCourses, 0);
    for (vector<int> g : graph)
        for (int vert : g)
            inDegree[vert]++;
    for (int i = 0; i < inDegree.size(); i++)
        if (inDegree[i] == 0)
            que.push(i);

    vector<int> result;
    while (!que.empty())
    {
        int v = que.front();
        que.pop();
        result.push_back(v);
        for (int vert : graph[v])
        {
            inDegree[vert]--;
            if (inDegree[vert] == 0)
                que.push(vert);
        }
    }
    reverse(result.begin(), result.end());
    return (result.size() < numCourses) ? vector<int>() : result;
}

// DAY 19 (Add Binary)===================================================

// Method 1 (naive approach)
string addBinary(string a, string b)
{
    int n = a.size() - 1;
    int m = b.size() - 1;
    int carry = 0;
    string sum = "";
    while (n >= 0 && m >= 0)
    {
        if (carry == 0)
        {
            if ((a[n] - '0') ^ (b[m] - '0'))
                sum += '1';
            else
                sum += '0';
            if (a[n] == '1' && b[m] == '1')
                carry = 1;
            n--, m--;
        }
        else
        {
            if ((a[n] - '0') ^ (b[m] - '0'))
                sum += '0';
            else
                sum += '1';
            if (a[n] == '0' && b[m] == '0')
                carry = 0;
            n--, m--;
        }
    }

    while (n >= 0)
    {
        if (carry == 1)
        {
            if (a[n] == '0')
            {
                sum += '1';
                carry = 0;
            }
            else
                sum += '0';
            n--;
        }
        else
            sum += a[n--];
    }
    while (m >= 0)
    {
        if (carry == 1)
        {
            if (b[m] == '0')
            {
                sum += '1';
                carry = 0;
            }
            else
                sum += '0';
            m--;
        }
        else
            sum += b[m--];
    }
    if (carry == 1)
        sum += '1';

    reverse(sum.begin(), sum.end());

    return sum;
}

////////////////////////OR////////////////////////////

// Method 2 (shortcut approach)
string addBinary(string a, string b)
{
    int n = a.size() - 1;
    int m = b.size() - 1;
    int carry = 0;

    string binsum = "";

    while (n >= 0 || m >= 0)
    {
        int sum = carry;
        if (n >= 0)
            sum += a[n--] - '0';
        if (m >= 0)
            sum += b[m--] - '0';
        binsum += (sum % 2) + '0';
        carry = sum / 2;
    }

    if (carry == 1)
        binsum += '1';

    reverse(binsum.begin(), binsum.end());

    return binsum;
}

// DAY 20 (Remove Linked List Elements)==============================================================

// Method 1
ListNode *removeElements(ListNode *head, int val)
{
    ListNode *node = head;
    ListNode *prev = nullptr;
    while (node)
    {
        bool ff = false;
        while (node != nullptr && node->val == val)
        {
            ff = true;
            node = node->next;
        }
        if (ff)
        {
            if (!prev)
                head = node;
            else
                prev->next = node;
        }
        prev = node;
        if (node)
            node = node->next;
    }
    return head;
}

////////////////////////OR//////////////////////////

// Method 2 - Standard Approach
ListNode *removeElements(ListNode *head, int val)
{
    ListNode *node = head;
    ListNode *prev = nullptr;
    while (node)
    {
        if (node->val == val)
        {
            ListNode *temp = node;
            if (!prev)
            {
                node = node->next;
                head = node;
            }
            else
            {
                prev->next = node->next;
                node = node->next;
            }
            delete temp;
        }
        else
        {
            prev = node;
            node = node->next;
        }
    }
    return head;
}

///////////////////////////////OR////////////////////////////////

// Method 3 (by taking double pointer)
ListNode *removeElements(ListNode *head, int val)
{
    ListNode **node = &head;
    while (*node)
    {
        if ((*node)->val == val)
        {
            ListNode **temp = node;
            (*node) = (*node)->next; // like  6->4->5  changed to 4->5
            delete &temp;            // deleting that address
        }
        else
            node = &((*node)->next); // just gave the address of next node to the prev
    }
    return head;
}

// DAY 21 (Word Search)==============================================

// Method 1 (DFS)
// TLE

bool dfs(string &word, int k, int i, int j, int n, int m, vector<vector<char>> &board)
{
    if (i == n || j == m || i == -1 || j == -1 || board[i][j] == '#' || board[i][j] != word[k])
        return false;
    if (k == word.size() - 1)
        return true;
    // cout<<i<<" "<<j<<" "<<board[i][j]<<"   "<<k<<" "<<word[k]<<endl;

    char c = board[i][j];
    board[i][j] = '#';

    bool res = false;
    res |= dfs(word, k + 1, i + 1, j, n, m, board);
    res |= dfs(word, k + 1, i, j + 1, n, m, board);
    res |= dfs(word, k + 1, i - 1, j, n, m, board);
    res |= dfs(word, k + 1, i, j - 1, n, m, board);

    board[i][j] = c;

    return res;
}

bool exist(vector<vector<char>> &board, string word)
{
    int n = board.size();
    int m = board[0].size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j] == word[0])
                if (dfs(word, 0, i, j, n, m, board))
                    return true;
    return false;
}

////////////////////////////OR///////////////////////////

// Method 2 (same as prev) -> more optimized by using calls as the conditions
bool dfs(string &word, int k, int i, int j, int n, int m, vector<vector<char>> &board)
{
    // cout<<i<<" "<<j<<" "<<board[i][j]<<"   "<<k<<" "<<word[k]<<endl;
    if (k == word.size() - 1)
        return true;

    char c = board[i][j];
    board[i][j] = '#';

    if (i + 1 < n && board[i + 1][j] == word[k + 1] && dfs(word, k + 1, i + 1, j, n, m, board))
        return true;
    if (j + 1 < m && board[i][j + 1] == word[k + 1] && dfs(word, k + 1, i, j + 1, n, m, board))
        return true;
    if (i - 1 >= 0 && board[i - 1][j] == word[k + 1] && dfs(word, k + 1, i - 1, j, n, m, board))
        return true;
    if (j - 1 >= 0 && board[i][j - 1] == word[k + 1] && dfs(word, k + 1, i, j - 1, n, m, board))
        return true;

    board[i][j] = c;

    return false;
}

bool exist(vector<vector<char>> &board, string word)
{
    int n = board.size();
    int m = board[0].size();
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j] == word[0])
                if (dfs(word, 0, i, j, n, m, board))
                    return true;
    return false;
}

// DAY 22(Binary Tree Zig Zag Level order Traversal)==================================================================

vector<vector<int>> zigzagLevelOrder(TreeNode *root)
{
    if (root == nullptr)
        return {};
    queue<TreeNode *> que;
    que.push(root);

    vector<vector<int>> larr;
    int l = 0;

    while (!que.empty())
    {
        int sz = que.size();
        vector<int> arr;
        while (sz--)
        {
            TreeNode *node = que.front();
            que.pop();
            arr.push_back(node->val);
            if (node->left)
                que.push(node->left);
            if (node->right)
                que.push(node->right);
        }
        larr.push_back(arr);
        if (l & 1)
            reverse(larr[l].begin(), larr[l].end());
        l++;
    }
    return larr;
}

// DAY 23 (Single Number 3)===================================================

// Method 1 (using map)
vector<int> singleNumber(vector<int> &nums)
{
    unordered_map<int, int> m;
    for (int i : nums)
        m[i]++;
    vector<int> once;
    for (auto itr : m)
        if (itr.second == 1)
            once.push_back(itr.first);
    return once;
}

////////////////////OR////////////////////

// Method 2 (by sorting)
vector<int> singleNumber(vector<int> &nums)
{
    int n = nums.size();
    sort(nums.begin(), nums.end());

    vector<int> once;
    for (int i = 0; i < n;)
    {
        // cout<<i<<endl;
        if (i + 1 == n)
        {
            once.push_back(nums[i++]);
            continue;
        }
        if (nums[i + 1] != nums[i])
        {
            once.push_back(nums[i]);
            i++;
        }
        else
            i += 2;
    }
    return once;
}

///////////////////////////OR/////////////////////////////////////

// Method 3 (by XOR)
vector<int> singleNumber(vector<int> &nums)
{
    int xor2 = 0;
    for (int i : nums)
        xor2 ^= i; // gives xor of 2 unique elements

    xor2 &= -xor2; // will only ON the first ON bit of xor2 from LSB

    vector<int> once(2, 0);
    for (int i : nums)
        if (i & xor2)     // check if the first ON bit is ON in "i"
            once[1] ^= i; // XOR of all elements with ON bit
        else
            once[0] ^= i; // XOR of all elements with OFF bit
    return once;
}

// DAY 25 (Find Minimum Using Rotated Sorted Array)===============================================

// Method 1 (traverse and find min)  -> O(n)
int findMin(vector<int> &nums)
{
    int mini = nums[0];
    for (int i : nums)
        mini = min(mini, i);
    return mini;
}

//////////////////////OR////////////////////////

// Method 2 (sort) -> O(nlogn)
int findMin(vector<int> &nums)
{
    sort(nums.begin(), nums.end());
    return nums[0];
}

////////////////////////OR///////////////////////

// Method 3 (finding pivot) -> O(n)
int findMin(vector<int> &nums)
{
    for (int i = 1; i < nums.size(); i++)
        if (nums[i - 1] > nums[i])
            return nums[i];
    return nums[0];
}

////////////////////////OR////////////////////////

// Method 4 (finding pivot through binary search) -> O(logn)
int findMin(vector<int> &nums)
{
    int l = 0, h = nums.size() - 1;
    if (nums[l] < nums[h]) // CHECK if already sorted
        return nums[l];

    while (l <= h)
    {
        int mid = (l + h) / 2;
        if (nums[mid] > nums[h])
            l = mid + 1;
        else if (nums[mid] > nums[h])
            h = mid;
        else
            h--;
    }
    return nums[h + 1];
}

// DAY 26 (Add Digits)==================================

// Method 1 (naive) --> O(n)
int addDigits(int num)
{
    // cout<<num<<endl;
    if (num - 9 <= 0)
        return num;
    int n = 0;
    while (num)
    {
        n += num % 10;
        num /= 10;
    }
    return addDigits(n);
}

//////////////////////////////OR/////////////////////////////

// Method 2 (using mathematical formula) --> O(1)
int addDigits(int num)
{
    if (num == 0)
        return 0;
    if (num % 9 == 0)
        return 9;
    return num % 9;
}

/////////////////////////////////OR///////////////////////////

// subMethod 2 (shortcut way) --> O(1)
int addDigits(int num)
{
    if (num == 0)
        return 0;
    return 1 + (num - 1) % 9;
}

// DAY 27 (Construct Binary Tree from Inorder and Postorder Traversal)===================================================

TreeNode *construct(vector<int> &in, vector<int> &post, int psi, int pei, int isi, int iei)
{
    // cout<<isi<<" "<<iei<<endl;
    // cout<<psi<<" "<<pei<<endl;
    if (isi == iei)
        return new TreeNode(in[isi]);
    if (isi > iei)
        return nullptr;
    TreeNode *root = new TreeNode(post[pei]);

    int ri = isi;
    for (; ri <= iei; ri++)
        if (in[ri] == post[pei])
            break;
    int diff = ri - isi;
    // cout<<ri<<endl;
    root->left = construct(in, post, psi, psi + diff - 1, isi, ri - 1);
    root->right = construct(in, post, psi + diff, pei - 1, ri + 1, iei);

    return root;
}

TreeNode *buildTree(vector<int> &inorder, vector<int> &postorder)
{
    return construct(inorder, postorder, 0, postorder.size() - 1, 0, inorder.size() - 1);
}

// DAY 28 (Task Scheduler)=============================================

int leastInterval(vector<char> &tasks, int n)
{
    map<char, int> s;
    for (char c : tasks)
        s[c]++;

    priority_queue<int> pq;
    for (auto p : s)
        pq.push(p.second);

    int count = 0, countz = 0;
    while (!pq.empty())
    {
        int lasttime = 0;
        vector<int> temp;
        for (int i = 0; i <= n; i++)
        {
            if (!pq.empty())
            {
                temp.push_back(pq.top() - 1);
                pq.pop();
                lasttime++;
            }
        }
        for (int i : temp)
            if (i)
                pq.push(i);
        count += !pq.empty() ? n + 1 : lasttime;
    }
    return count;
}

// DAY 29 (Best Time to Buy and Sell Stock with Cooldown)=========================================

int maxProfit(vector<int> &prices)
{
    if (prices.size() <= 1)
        return 0;
    int SA = 0, SB = -prices[0], SC = 0;
    for (int i = 1; i < prices.size(); i++)
    {
        int temp = SA;
        SA = max(SA, SC);
        SC = SB + prices[i];
        SB = max(SB, temp - prices[i]);
    }
    return max(SA, SC);
}

// DAY 30 (Word Break 2)====================================================

// Method 1 (without using cache)
// TLE
vector<string> wordBreak(string s, vector<string> &wordDict)
{
    vector<string> sentences;

    for (string word : wordDict)
    {
        if (word == s.substr(0, word.size()))
        {
            if (word.size() == s.size())
                sentences.push_back(word);
            else
            {
                vector<string> temp = wordBreak(s.substr(word.size()), wordDict);

                for (string t : temp)
                    sentences.push_back(word + " " + t);
            }
        }
    }
    return sentences;
}