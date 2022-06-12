// DAY 1 (1480. Running Sum of 1d Array)=========================================================================================================================

vector<int> runningSum(vector<int>& nums) 
{
    for(int i = 0; i < nums.size(); i++)
        nums[i] += i? nums[i-1] : 0;
    return nums;
}

// DAY 2 (867. Transpose Matrix)=========================================================================================================================

vector<vector<int>> transpose(vector<vector<int>>& matrix) 
{
    int n = matrix.size(), m = matrix[0].size();
    vector<vector<int>> ans(m, vector<int>(n));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            ans[j][i] = matrix[i][j];
    return ans;
}

// DAY 3 (304. Range Sum Query 2D - Immutable)=========================================================================================================================

class NumMatrix {
public:
    
    vector<vector<int>> msum;
    int n, m;
    NumMatrix(vector<vector<int>>& matrix) 
    {
        n = matrix.size();
        m = matrix[0].size();
        msum.resize(n, vector<int>(m));
        
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < m; j++)
            {
                int u = i? msum[i-1][j] : 0;
                int l = j? msum[i][j-1] : 0;
                int d = i && j? msum[i-1][j-1] : 0;
                msum[i][j] = l + u + matrix[i][j] - d;
            }
        }
    }
    
    int sumRegion(int row1, int col1, int row2, int col2) 
    {
        return msum[row2][col2] - (row1? msum[row1-1][col2] : 0) - (col1? msum[row2][col1-1] : 0) + (row1 && col1? msum[row1-1][col1-1] : 0);
    }
};

/**
 * Your NumMatrix object will be instantiated and called as such:
 * NumMatrix* obj = new NumMatrix(matrix);
 * int param_1 = obj->sumRegion(row1,col1,row2,col2);
 */

// DAY 4 (51. N-Queens)=========================================================================================================================

vector<vector<string>> ans;
void dfs(int i, int c, int ld, int rd, int n, vector<string> &board)
{
    if(i == n)
    {
        ans.push_back(board);
        return;
    }
    for(int j = 0; j < n; j++)
    {
        if(!(c & (1 << j)) && !(ld & (1 << (i+j))) && !(rd & (1 << (i-j+n))))
        {
            c ^= (1 << j);
            ld ^= (1 << (i+j));
            rd ^= (1 << (i-j+n));
            board[i][j] = 'Q';
            dfs(i+1, c, ld, rd, n, board);
            c ^= (1 << j);
            ld ^= (1 << (i+j));
            rd ^= (1 << (i-j+n));
            board[i][j] = '.';
        }
    }
}

vector<vector<string>> solveNQueens(int n) 
{
    vector<string> board(n, string(n, '.'));
    dfs(0, 0, 0, 0, n, board);

    return ans;
}

// DAY 5 (52. N-Queens II)=========================================================================================================================

int dfs(int i, int c, int ld, int rd, int n)
{
    if(i == n) return 1;

    int ans = 0;
    for(int j = 0; j < n; j++)
    {
        if(!(c & (1 << j)) && !(ld & (1 << (i + j))) && !(rd & (1 << (i - j + n))))
        {
            c ^= (1 << j);
            ld ^= (1 << (i+j));
            rd ^= (1 << (i-j+n));
            ans += dfs(i+1, c, ld, rd, n);
            c ^= (1 << j);
            ld ^= (1 << (i+j));
            rd ^= (1 << (i-j+n));
        }
    }

    return ans;
}

int totalNQueens(int n) 
{
    return dfs(0, 0, 0, 0, n);
}

// DAY 6 (160. Intersection of Two Linked Lists)=========================================================================================================================

// APPROACH 1

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) 
{
    ListNode* tailA = headA;

    while(tailA && tailA->next) tailA = tailA->next;
    tailA->next = headB;

    ListNode* slow = headA, *fast = headA;

    do {
        slow = slow->next;
        fast = fast->next->next;
    }
    while(fast && fast->next && fast->next->next && slow != fast);

    if(!fast || !fast->next || !fast->next->next) 
    {
        tailA->next = nullptr;
        return nullptr;
    }

    slow = headA;
    while(slow != fast) slow = slow->next, fast = fast->next;

    tailA->next = nullptr;

    return slow;
}

// APPROACH 2 (Concise)

ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) 
{
    ListNode* p1 = headA, *p2 = headB;
    while(p1 != p2)
    {
        p1 = p1? p1->next : headB;
        p2 = p2? p2->next : headA;
    }
    return p1;
}

// DAY 7 (88. Merge Sorted Array)=========================================================================================================================

void merge(vector<int>& nums1, int n, vector<int>& nums2, int m)
{
    while(n || m)
        nums1[n+m] = ((n && m && (nums1[n-1] > nums2[m-1])) || (n && !m))? nums1[--n] : nums2[--m];
}

// DAY 8 (1332. Remove Palindromic Subsequences)=========================================================================================================================

bool ispal(string &s)
{
    int i = 0, j = s.size() - 1;
    while(i < j)
        if(s[i++] != s[j--])
            return false;
    return true;
}

int removePalindromeSub(string s) 
{
    if(s.empty()) return 0;
    if(ispal(s)) return 1;
    return 2;
}

// DAY 9 (167. Two Sum II - Input Array Is Sorted)=========================================================================================================================

vector<int> twoSum(vector<int>& numbers, int target) 
{
    int i = 0, j = numbers.size() - 1;
    while(i < j)
    {
        int sum = numbers[i] + numbers[j];
        if(sum == target) return {i+1, j+1};
        if(sum < target) i++;
        else j--;
    }
    return {0,0};
}

// DAY 10 (3. Longest Substring Without Repeating Characters)=========================================================================================================================

int lengthOfLongestSubstring(string s) 
{
    int ans = 0, mxi = -1;
    vector<int> li(256, -1);
    for(int i = 0; i < s.size(); i++)
    {
        mxi = max(mxi, li[s[i] - ' ']);
        ans = max(ans, i - mxi);
        li[s[i] - ' '] = i;
    }
    return ans;
}

// DAY 11 (1658. Minimum Operations to Reduce X to Zero)=========================================================================================================================

int minOperations(vector<int>& nums, int x) 
{
    int tot = 0;
    for(int num : nums)
        tot += num;
    int tar = tot - x;
    if(tar < 0) return -1;

    int i = 0, j = 0, sum = 0, ans = INT_MAX;
    while(i < nums.size())
    {
        sum += nums[i++];
        while(sum > tar) sum -= nums[j++];
        if(sum == tar) ans = min(ans, (int)nums.size() - (i-j));
    }
    return ans == INT_MAX? -1 : ans;
}

// DAY 12 (1695. Maximum Erasure Value)=========================================================================================================================

int maximumUniqueSubarray(vector<int>& nums) 
{
    int score = 0, maxscore = 0;
    unordered_map<int,int> mp;

    for(int i = 0, j = 0; i < nums.size(); i++)
    {
        mp[nums[i]]++;
        while(mp[nums[i]] == 2)
        {
            mp[nums[j]]--;
            score -= nums[j++];
        }
        score += nums[i];
        maxscore = max(maxscore, score);
    }
    return maxscore;
}
