//DAY 1(Invert Binary Tree)

// Method 1 (by saving the right at every step)
TreeNode *invertTree(TreeNode *root)
{
    if (root == nullptr)
        return nullptr;

    TreeNode *r = root->right;
    root->right = invertTree(root->left);
    root->left = invertTree(r);

    return root;
}

///////////////OR//////////////
// Method 2 (by swaping the left and right at every step)
TreeNode *invertTree(TreeNode *root)
{
    if (root == nullptr)
        return nullptr;

    invertTree(root->left);
    invertTree(root->right);
    swap(root->left, root->right);

    return root;
}

//DAY 2(Delete Node in a Linked List)===============================================

void deleteNode(ListNode *&node)
{
    node->val = node->next->val;
    node->next = node->next->next;
}

///////////////OR///////////////

void deleteNode(ListNode *&node)
{
    *node = *(node->next);
}

//DAY 3()===============================================================================

// (by custom comparator)
static bool sort_bydiff(vector<int> &a, vector<int> &b)
{
    return (a[0] - a[1]) < (b[0] - b[1]);
}

int twoCitySchedCost(vector<vector<int>> &costs)
{
    int n = costs.size();
    int sum = 0;
    sort(costs.begin(), costs.end(), sort_bydiff);

    for (int i = 0; i < n / 2; i++)
        sum += costs[i][0];
    for (int i = n / 2; i < n; i++)
        sum += costs[i][1];

    return sum;
}

/////////////OR//////////////////

// (by LAMBDA OPERATION custom operator)

int twoCitySchedCost(vector<vector<int>> &costs)
{
    int n = costs.size();
    int sum = 0;
    sort(costs.begin(), costs.end(), [](const vector<int> &a, const vector<int> &b) {
        return (a[0] - a[1]) < b[0] - b[1];
    });

    for (int i = 0; i < n / 2; i++)
        sum += costs[i][0];
    for (int i = n / 2; i < n; i++)
        sum += costs[i][1];

    return sum;
}

//DAY 4(Reverse String)==============================================================================

// (using swap function)
void reverseString(vector<char> &s)
{
    for (int i = 0; i < s.size() / 2; i++)
        swap(s[i], s[s.size() - i - 1]);
}

////////////////OR/////////////////
// (using reverse function)
void reverseString(vector<char> &s)
{
    reverse(s.begin(), s.end());
}

///////////////OR/////////////////
// (using 2 pointer approach)
void reverseString(vector<char> &s)
{
    int l = 0, h = s.size() - 1;
    while (l < h)
    {
        char c = s[l];
        s[l] = s[h];
        s[h] = c;
        l++, h--;
    }
}

// DAY 5( Random Pick with Weight)=================================================================

class Solution
{
public:
    vector<int> wsum;
    int sum;
    Solution(vector<int> &w)
    {
        sum = 0;
        for (int i : w)
        {
            sum += i;
            wsum.push_back(sum);
        }
    }

    int binary_search(int val)
    {
        int l = 0, h = wsum.size() - 1;
        while (l < h)
        {
            int mid = (l + h) / 2;
            if (wsum[mid] < val)
                l = mid + 1;
            else
                h = mid;
        }
        return l;
    }

    int pickIndex()
    {
        int idx = rand() % sum;
        return binary_search(idx + 1);
    }
};

/**
 * Your Solution object will be instantiated and called as such:
 * Solution* obj = new Solution(w);
 * int param_1 = obj->pickIndex();
 */

// DAY 6()==========================================================================================
// (by sorting a[0] in ascending order)
// O(n^2)
vector<vector<int>> reconstructQueue(vector<vector<int>> &people)
{
    int n = people.size();

    sort(people.begin(), people.end(), [](const vector<int> &a, const vector<int> &b) {
        return a[0] < b[0];
    });

    // for(int i=0;i<n;i++)
    //     cout<<people[i][0]<<" "<<people[i][1]<<endl;

    vector<vector<int>> qu(n, vector<int>(2, -1));

    for (int i = 0; i < n; i++)
    {
        int foll = people[i][1];
        for (int j = 0; j < n; j++)
        {
            if (foll == 0 && qu[j][0] == -1)
            {
                qu[j][0] = people[i][0];
                qu[j][1] = people[i][1];
                break;
            }
            else if (foll > 0 && (qu[j][0] == -1 || qu[j][0] >= people[i][0]))
                foll--;
        }
    }
    return qu;
}

/////////////////////OR//////////////////////////
// (by sorting a[0] in descending order and a[1] in ascending order)
// <O(n^2) & >O(n)
vector<vector<int>> reconstructQueue(vector<vector<int>> &people)
{
    int n = people.size();

    sort(people.begin(), people.end(), [](const vector<int> &a, const vector<int> &b) {
        if (a[0] == b[0])
            return a[1] < b[1];
        else
            return a[0] > b[0];
    });

    vector<vector<int>> qu;
    for (vector<int> ar : people)
        qu.insert(qu.begin() + ar[1], ar);

    return qu;
}

// DAY 7()====================================================================

// Method 1 -> by combinations
// <O(tar^n)
// this code msay give TLE
int count_change(int amount, int idx, vector<int> &coins)
{
    if (amount == 0)
        return 1;
    int count = 0;
    for (int i = idx; i < coins.size(); i++)
        if (amount - coins[i] >= 0)
            count += count_change(amount - coins[i], i, coins);
    return count;
}

int change(int amount, vector<int> &coins)
{
    return count_change(amount, 0, coins);
}

///////////////////OR/////////////////

// Method 2 -> by subsequences
// O(2^n)
// this may also TLE
int count_change(int amount, int idx, vector<int> &coins)
{
    if (idx == coins.size() || amount == 0)
    {
        if (amount == 0)
            return 1;
        return 0;
    }

    int count = 0;
    if (amount - coins[idx] >= 0)
        count += count_change(amount - coins[idx], idx, coins);
    count += count_change(amount, idx + 1, coins);

    return count;
}

int change(int amount, vector<int> &coins)
{
    return count_change(amount, 0, coins);
}

////////////////OR//////////////////

// by DP(2D) of subsequence
// O(n^2)
int count_change(int tar, vector<int> &coins, vector<vector<int>> &dp, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= tar; j++)
        {
            if (j == 0)
            {
                dp[i][j] = 1;
                continue;
            }
            if (i == 0)
            {
                dp[i][j] = 0;
                continue;
            }
            if (j - coins[i - 1] >= 0)
                dp[i][j] += dp[i][j - coins[i - 1]] + dp[i - 1][j];
            else
                dp[i][j] += dp[i - 1][j];
        }
    }
    return dp[n - 1][tar];
}

int change(int amount, vector<int> &coins)
{
    vector<vector<int>> dp(coins.size() + 1, vector<int>(amount + 1, 0));

    return count_change(amount, coins, dp, coins.size() + 1);
}

/////////////////OR/////////////////////

// Method->4(1D DP)
int change(int amount, vector<int> &coins)
{
    vector<int> dp(amount + 1, 0);
    dp[0] = 1;
    for (int coin : coins)
        for (int i = coin; i <= amount; i++)
            dp[i] += dp[i - coin];
    return dp[amount];
}

// DAY 8(Power of Two)===================================================================

bool isPowerOfTwo(int n)
{
    return n > 0 && !(n & (n - 1));
}

// DAY 9(Is Subsequence)======================================================================

// (in 2 loops but O(t.size()))
bool isSubsequence(string s, string t)
{
    int l = 0;
    for (int i = 0; i < s.size(); i++)
    {
        bool f = false;
        for (int j = l; j < t.size(); j++)
        {
            if (t[j] == s[i])
            {
                f = true;
                l = j + 1;
                break;
            }
        }
        if (!f)
            return false;
    }
    return true;
}

//////////////////OR///////////////

// (by 1 loop and O(t.size()))
bool isSubsequence(string s, string t)
{
    int n = s.size();
    int m = t.size();

    if (n > m)
        return false;

    if (n == m && s != t)
        return false;
    else if (n == m && s == t)
        return true;

    int j = 0;
    if (n < m)
    {
        for (int i = 0; i < m; i++)
        {
            if (t[i] == s[j])
                j++;
        }
    }
    return (j == n);
}

// DAY 10(Search Insert Position)=====================================================================

// O(n)
int searchInsert(vector<int> &nums, int target)
{
    for (int i = -0; i < nums.size(); i++)
    {
        if (target <= nums[i])
            return i;
    }
    return nums.size();
}

/////////////////OR//////////////////

// O(log(n))
int searchInsert(vector<int> &nums, int target)
{
    int n = nums.size();
    int l = 0, r = n;
    while (l < r)
    {
        int mid = l + (r - l) / 2;
        if (nums[mid] < target)
            l = mid + 1;
        else
            r = mid;
    }
    return l;
}

/////////////////////OR////////////////////

// <=O(logn)
int searchInsert(vector<int> &nums, int target)
{
    int l = 0;
    int r = nums.size() - 1;

    while (l <= r)
    {
        int mid = l + (r - l) / 2;
        if (nums[mid] == target)
            return mid;
        else if (nums[mid] < target)
            l = mid + 1;
        else if (nums[mid] > target)
            r = mid - 1;
    }
    return l;
}

//DAY 11(Sort colors)=======================================================================================

// O(n)
// by counting 0,1,2 --> (O(n)) space
void sortColors(vector<int> &nums)
{
    int count0 = 0;
    int count1 = 0;
    int count2 = 0;
    for (int i : nums)
    {
        if (i == 0)
            count0++;
        else if (i == 1)
            count1++;
        else
            count2++;
    }
    for (int i = 0; i < nums.size(); i++)
    {
        if (count0 > 0)
        {
            nums[i] = 0;
            count0--;
            continue;
        }
        else if (count1 > 0)
        {

            nums[i] = 1;
            count1--;
            continue;
        }
        else if (count2 > 0)
        {

            nums[i] = 2;
            count2--;
            continue;
        }
    }
}

/////////////////OR////////////////

// O(n)
// by swapping
void sortColors(vector<int> &nums)
{
    int i = 0, p1 = 0, p2 = nums.size() - 1;
    while (i < nums.size())
    {
        if (nums[i] == 0)
        {
            swap(nums[i], nums[p1]);
            i++;
            p1++;
        }
        else if (nums[i] == 1)
        {
            i++;
        }
        else if (nums[i] == 2)
        {
            while (nums[p2] == 2)
            {
                if (p2 == i)
                    return;
                p2--;
            }
            swap(nums[i], nums[p2]);
        }
    }
}