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

// DAY 13 (120. Triangle)=========================================================================================================================

int minimumTotal(vector<vector<int>>& triangle) 
{
    int n = triangle.size();
    for(int i = n-2; i >= 0; i--)
        for(int j = 0; j < triangle[i].size(); j++)
            triangle[i][j] += min(triangle[i+1][j], triangle[i+1][j+1]);
    return triangle[0][0];
}

// DAY 14 (583. Delete Operation for Two Strings)=========================================================================================================================

int maxComSubseq(int i, int j, int n, int m, string &s, string &t)
{
    vector<vector<int>> dp(n, vector<int>(m, 0));
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            int ip1 = i? dp[i-1][j] : 0;
            int jp1 = j? dp[i][j-1] : 0;
            int ijp1 = 0;
            ijp1 = ((i && j)? dp[i-1][j-1] : 0) + ((s[i] == t[j])? 1 : 0);

            dp[i][j] = max({ip1, jp1, ijp1});
        }
    }
    return dp[n-1][m-1];
}

int minDistance(string word1, string word2) 
{
    int n = word1.size(), m = word2.size();
    int mlen = maxComSubseq(0, 0, n, m, word1, word2);

    return (n + m) - 2*mlen;
}

// DAY 16 (5. Longest Palindromic Substring)=========================================================================================================================

// APPROACH 1 -> O(n^2)

string longestPalindrome(string s) 
{
    int n = s.size();
    vector<vector<bool>> dp(n,vector<bool>(n));
    int l = 0, r = 0;
    for(int len = 1; len <= n; len++)
    {
        for(int i = 0, j = len-1; j < n; i++, j++)
        {
            dp[i][j] = (len == 1) || (len == 2 && s[i] == s[j]) || (len > 2 && s[i] == s[j] && dp[i+1][j-1]);
            l = dp[i][j]? i : l;
            r = dp[i][j]? len : r;
        }
    }

    return s.substr(l, r);
}

// APPROACH 2 -> O(n)

string longestPalindrome(string s) 
{
    int i = 0, n = s.size();
    int st = 0, end = 0;
    while(i < n)
    {
        int l = i;
        while(i+1 < n && s[i] == s[i+1]) i++;
        int r = i;
        while(l-1 >= 0 && r+1 < n && s[l-1] == s[r+1]) l--, r++;

        if(r - l + 1 > end - st + 1) st = l, end = r;
        i++;
    }

    return s.substr(st, end-st+1);
}

// DAY 21 (1642. Furthest Building You Can Reach)=========================================================================================================================

int furthestBuilding(vector<int>& heights, int bricks, int ladders) 
{
    priority_queue<int> pq;
    int i = 0;
    while(i < heights.size()-1)
    {
        int hdiff = heights[i+1] - heights[i];

        if(hdiff <= 0) 
        {
            i++;
            continue;
        }

        if(hdiff <= bricks)
        {
            bricks -= hdiff;
            pq.push(hdiff);
            i++;
        }
        else 
        {
            if(!ladders--) break;
            if(pq.empty() || hdiff > pq.top())
            {
                i++;
                continue;
            }
            bricks += pq.top();
            pq.pop();
        }
    }

    return i;
}

// DAY 22 (215. Kth Largest Element in an Array)=========================================================================================================================

int findKthLargest(vector<int>& nums, int k) 
{
    sort(nums.rbegin(), nums.rend());
    return nums[k-1];
}

// DAY 23 (630. Course Schedule III)=========================================================================================================================

int scheduleCourse(vector<vector<int>>& courses) 
{
    sort(courses.begin(), courses.end(), [](auto const &a, auto const &b){
        return a[1] == b[1]? a[0] < b[0] : a[1] < b[1];
    });

    int n = courses.size();
    priority_queue<int> pq;
    int t = 0;
    for(int i = 0; i < n; i++)
    {
        int dur = courses[i][0], ld = courses[i][1];
        t += dur;
        pq.push(dur);

        if(t > ld)
        {
            t -= pq.top();
            pq.pop();
        }
    }
    return pq.size();
}

// DAY 24 (1354. Construct Target Array With Multiple Sums)=========================================================================================================================

bool isPossible(vector<int>& target) 
{
    long tot = 0;
    priority_queue<int> pq;
    for(int x : target)
    {
        tot += x;
        pq.push(x);
    }

    while(pq.top() != 1)
    {
        int mx = pq.top();
        pq.pop();
        tot -= mx;

        if(tot <= 0 || mx-tot <= 0) 
            return false;

        mx %= tot;
        tot += mx;
        pq.push(mx > 0? mx : tot);
    }
    return true;
}

// DAY 25 (665. Non-decreasing Array)=========================================================================================================================

bool checkPossibility(vector<int>& nums) 
{
    int n = nums.size();
    bool changed = false;
    int prev = nums[0];
    for(int i = 1; i < n; i++)
    {
        if(nums[i] >= prev)
        {
            prev = nums[i];
            continue;
        }
        if(changed) return false;
        changed = true;
        if(i-2 == -1 || nums[i] >= nums[i-2])
            prev = nums[i];
    }
    return true;
}

// DAY 26 (1423. Maximum Points You Can Obtain from Cards)=========================================================================================================================

int maxScore(vector<int>& cardPoints, int k) 
{
    int n = cardPoints.size();
    int sum = 0;
    for(int x : cardPoints)
        sum += x;

    int minsum = sum, currsum = 0;
    int x = n-k;
    for(int i = 0; i < n; i++)
    {
        currsum += cardPoints[i];
        if(i >= x)
            currsum -= cardPoints[i-x];
        if(i >= x-1)
            minsum = min(minsum, currsum);
    }
    return sum - minsum;
}

// DAY 27 (1689. Partitioning Into Minimum Number Of Deci-Binary Numbers)=========================================================================================================================

int minPartitions(string n) 
{
    int ans = 0;
    for(char c : n)
        ans = max(ans, c-'0');
    return ans;
}

// DAY 28 (1647. Minimum Deletions to Make Character Frequencies Unique)====================================================================

// APPROACH 1 (Using Hashmap) --> time - O(n), space - O(n)

int minDeletions(string s) 
{
    vector<int> map(26,0);
    for(char c : s)
        map[c-'a']++;
    
    unordered_map<int,int> cntmp;
    for(int x : map)
        if(x) cntmp[x]++;
    
    int ans = 0, i = 0;
    for(int x : map)
    {
        if(cntmp[x] <= 1) continue;
        
        cntmp[x--]--, ans++;
        while(cntmp[x])
            x--, ans++;
        if(x) cntmp[x] = 1;
    }
    return ans;
}

// APPROACH 2 (Without hashmap) --> time - O(n), space - O(1)

int minDeletions(string s) 
{
    vector<int> map(26,0);
    for(char c : s)
        map[c-'a']++;
    sort(map.rbegin(), map.rend());
    
    int prev = map[0];
    int ans = s.size() - map[0];
    for(int i = 1; i < 26; i++)
    {
        if(map[i] == 0 || prev == 0) break;
        prev = min(map[i], prev-1);
        ans -= prev;
    }
    return ans;
}

// DAY 29 (406. Queue Reconstruction by Height)=========================================================================================================================

vector<vector<int>> reconstructQueue(vector<vector<int>>& people) 
{
    int n = people.size();
    sort(people.begin(), people.end());

    vector<vector<int>> que(n, vector<int>(2,-1));
    for(int i = 0; i < n; i++)
    {
        int k = people[i][1];
        for(int j = 0; j < n; j++)
        {
            if(k == 0 && que[j][0] == -1)
            {
                que[j] = people[i];
                break;
            }
            else if(k && (que[j][0] == -1 || que[j][0] >= people[i][0]))
                k--;
        }
    }
    return que;
}

// DAY 30 (462. Minimum Moves to Equal Array Elements II)=========================================================================================================================

int minMoves2(vector<int>& nums) 
{
    sort(nums.begin(), nums.end());
    int ans = 0, med = nums[nums.size()/2];
    for(int x : nums)
        ans += abs(x - med);
    return ans;
}
