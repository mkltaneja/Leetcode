// DAY 1(First Bad Version)=============================================================================
// O(log(n))
int binarysearch(unsigned int si, unsigned int ei)
{
    if (si == ei)
        return ei;
    unsigned int mid = (si + ei) / 2;
    // if(isBadVersion(mid) && !isBadVersion(mid-1))
    //     return mid;
    if (!isBadVersion(mid))
        return binarysearch(mid + 1, ei);
    else
        return binarysearch(si, mid);
}

int firstBadVersion(int n)
{
    return binarysearch(0, n);
}

// DAY 2()=============================================================================
//O(n^2)
int numJewelsInStones(string J, string S)
{
    int count = 0;
    for (int i = 0; i < J.size(); i++)
    {
        for (int j = 0; j < S.size(); j++)
        {
            if (S[j] == J[i])
                count++;
        }
    }
    return count;
}

////////////// OR //////////////
//O(n)
int numJewelsInStones(string J, string S)
{
    unordered_set<char> jewels;
    int ans = 0;

    for (char c : J)
        jewels.insert(c);
    for (char c : S)
        ans += jewels.count(c);

    return ans;
}

// DAY 3(Ransom Note)=============================================================================
// O(n^2)
bool canConstruct(string ransomNote, string magazine)
{
    int n = ransomNote.size();
    int m = magazine.size();
    if (m < n)
        return false;
    int k = 0;
    for (int i = 0; i < n; i++)
        for (int j = k; j < m; j++)
        {
            if (magazine[j] == ransomNote[i])
            {
                swap(magazine[j], magazine[k]);
                k++;
                break;
            }
            else if (j == m - 1)
                return false;
        }
    return true;
}

////////////OR////////////
// O(n)
bool canConstruct(string ransomNote, string magazine)
{
    int n = ransomNote.size();
    int m = magazine.size();
    if (m < n)
        return false;
    vector<int> count(26, 0);
    for (int i = 0; i < m; i++)
        count[magazine[i] - 'a']++;
    for (int i = 0; i < n; i++)
        if (--count[ransomNote[i] - 'a'] < 0)
            return false;
    return true;
}

// DAY 4()=============================================================================
// O(no. of bits of num)
int findComplement(int num)
{
    int bsize = 0;
    int n = num;
    while (n)
    {
        n >>= 1;
        bsize++;
    }
    int mask = 1;
    for (int i = 0; i < bsize; i++)
        num ^= (mask << i);
    return num;
}
// DAY 5(First Unique Character in a String)=============================================================================
// O(n)
int firstUniqChar(string s)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n = s.length();
    vector<int> count(26, 0);
    for (int i = 0; i < n; i++)
        count[s[i] - 'a']++;
    for (int i = 0; i < n; i++)
        if (count[s[i] - 'a'] == 1)
            return i;
    return -1;
}

//DAY 6(Majority Element)====================================================================================
// O(n^2)
int majorityElement(vector<int> &nums)
{
    int n = nums.size();
    vector<bool> vis(n, false);
    for (int i = 0; i < n; i++)
    {
        int count = 1;
        if (count > n / 2)
            return nums[i];
        if (!vis[i])
        {
            vis[i] = true;
            for (int j = i + 1; j < n; j++)
            {
                if (nums[j] == nums[i])
                {
                    vis[j] = true;
                    if (++count > n / 2)
                        return nums[i];
                }
            }
        }
    }
    return -1;
}

//////////////OR///////////////////
// O(nlog(n))
int majorityElement(vector<int> &arr)
{
    int n = arr.size();
    sort(arr.begin(), arr.end());
    return arr[n / 2];
}

///////////////OR/////////////////////

//O(n)
//BOYER - MOORE VOTING ALGORITHM
int majorityElement(vector<int> &nums)
{
    int n = nums.size();

    int count = 0;
    int candidate;

    for (int i = 0; i < n; i++)
    {
        if (count == 0)
            candidate = nums[i];
        count += (candidate == nums[i]) ? 1 : -1;
    }
    return candidate;
}

////OR//// -> We can also use hashmap with O(n) complexity
////OR//// -> We can also use Divide And Conquer Approach of O(nlogn) complexity
////OR//// -> We can alse use Randomised Algorithm of random time complexity, ranged from O(n/2) to O(infinity)

//DAY 7(Cousins in Binary Tree)===============================================================

vector<TreeNode *> rootToNodePath(TreeNode *node, int data)
{
    if (node == nullptr)
        return {};

    if (node->val == data)
    {
        vector<TreeNode *> path;
        path.push_back(node);
        return path;
    }

    vector<TreeNode *> lnode = rootToNodePath(node->left, data);
    if (!lnode.empty())
    {
        lnode.push_back(node);
        return lnode;
    }

    vector<TreeNode *> rnode = rootToNodePath(node->right, data);
    if (!rnode.empty())
    {
        rnode.push_back(node);
        return rnode;
    }
    return {};
}

bool isCousins(TreeNode *root, int x, int y)
{
    vector<TreeNode *> xarr = rootToNodePath(root, x);
    vector<TreeNode *> yarr = rootToNodePath(root, y);

    int n = xarr.size();
    int m = yarr.size();

    if (n != m)
        return false;
    return (xarr[1]->val != yarr[1]->val);
}

////////////////OR//////////////////////
// Better approach
int xlevel = 0;
int ylevel = 0;
int xpar = -1;
int ypar = -2;

void leveloder(TreeNode *node, TreeNode *par, int x, int y, int level)
{
    if (node == nullptr)
        return;

    if (node->val == x)
    {
        xlevel = level;
        xpar = par->val;
    }
    if (node->val == y)
    {
        ylevel = level;
        ypar = par->val;
    }

    leveloder(node->left, node, x, y, level + 1);
    leveloder(node->right, node, x, y, level + 1);
}

bool isCousins(TreeNode *root, int x, int y)
{
    leveloder(root, root, x, y, 0);
    // cout<<xlevel<<" "<<ylevel<<endl;
    // cout<<xpar<<" "<<ypar<<endl;
    if (xlevel != ylevel || xpar == ypar)
        return false;
    return true;
}

//DAY 8(Check If It Is a Straight Line)===============================================================================

bool checkStraightLine(vector<vector<int>> &coordinates)
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    int n = coordinates.size();
    if (n == 2)
        return true;
    if ((coordinates[1][0] - coordinates[0][0]) == 0)
    {
        for (int i = 0; i < n - 1; i++)
        {
            // cout<<(coordinates[i+1][0]-coordinates[i][0])<<endl;
            if ((coordinates[i + 1][0] - coordinates[i][0]) != 0)
                return false;
        }
    }
    else
    {
        float m = (float)(coordinates[1][1] - coordinates[0][1]) / (coordinates[1][0] - coordinates[0][0]);
        for (int i = 0; i < n - 1; i++)
        {
            // cout<<(float)(coordinates[i+1][1]-coordinates[i][1])/(coordinates[i+1][0]-coordinates[i][0])<<endl;
            if ((coordinates[i + 1][0] - coordinates[i][0]) == 0)
                return false;
            if ((float)(coordinates[i + 1][1] - coordinates[i][1]) / (coordinates[i + 1][0] - coordinates[i][0]) != m)
                return false;
        }
    }
    return true;
}

//DAY 9(Valid Perfect Square)=============================================================
// O(sqrt(num))
bool isPerfectSquare(int num)
{
    long long int i = 1;
    while (i * i != num)
    {
        if (i * i > num)
            return false;
        i++;
    }
    return true;
}

///////////////OR//////////////////////
// O(log(sqrt(num)))
bool isPerfectSquare(int num)
{
    if (num == 1)
        return true;

    long int l = 0;
    long int h = num / 2;
    while (l <= h)
    {
        long int mid = (l + h) / 2;
        if (mid * mid == num)
            return true;
        else if (mid * mid < num)
            l = mid + 1;
        else
            h = mid - 1;
    }
    return false;
}

// DAY 10(Find The Town Judge)====================================================

// O(n)
int findJudge(int N, vector<vector<int>> &trust)
{
    if (N == 1)
        return 1;
    vector<int> childsize(N + 1, 0);

    for (vector<int> arr : trust)
    {
        childsize[arr[1]]++;
        childsize[arr[0]]--;
    }
    for (int i = 0; i <= N; i++)
        if (childsize[i] == N - 1)
            return i;
    return -1;
}

//DAY 11(Flood Fill)=====================================================================

// by DFS
void dfs(vector<vector<int>> &image, int sr, int sc, int oldColor, int newColor, int n, int m)
{
    if (sr == n || sc == m || sr == -1 || sc == -1 || image[sr][sc] != oldColor)
        return;

    image[sr][sc] = newColor;

    dfs(image, sr + 1, sc, oldColor, newColor, n, m);
    dfs(image, sr, sc + 1, oldColor, newColor, n, m);
    dfs(image, sr - 1, sc, oldColor, newColor, n, m);
    dfs(image, sr, sc - 1, oldColor, newColor, n, m);
}

vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int newColor)
{
    int n = image.size();
    int m = image[0].size();
    int oldColor = image[sr][sc];

    if (oldColor != newColor)
        dfs(image, sr, sc, oldColor, newColor, n, m);

    return image;
}

// by BFS
vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int newColor)
{
    int n = image.size();
    int m = image[0].size();
    int oldColor = image[sr][sc];

    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

    if (oldColor != newColor)
    {
        queue<int> que;
        que.push(m * sr + sc);
        image[sr][sc] = newColor;
        while (!que.empty())
        {
            int ridx = que.front();
            que.pop();
            for (int d = 0; d < 4; d++)
            {
                int i = (ridx / m) + dir[d][0];
                int j = (ridx % m) + dir[d][1];
                if (i >= 0 && j >= 0 && i < n && j < m && image[i][j] == oldColor)
                {
                    image[i][j] = newColor;
                    que.push(i * m + j);
                }
            }
        }
    }

    return image;
}

// DAY 12(Single Element in a Sorted Array)===================================================
//O(n)
int singleNonDuplicate(vector<int> &nums)
{
    for (int i = 1; i < nums.size(); i++)
    {
        nums[0] ^= nums[i];
    }
    return nums[0];
}

// O(logn)
int singleNonDuplicate(vector<int> &nums)
{
    int n = nums.size();
    int si = 0;
    int ei = n - 1;
    while (si < ei)
    {
        int mid = (si + ei) / 2;
        if (mid % 2 == 1)
        {
            if (nums[mid] == nums[mid - 1])
                si = mid + 1;
            else
                ei = mid - 2;
        }
        if (mid % 2 == 0)
        {
            if (nums[mid] == nums[mid + 1])
                si = mid + 2;
            else
                ei = mid - 1;
        }
    }
    return nums[si];
}

//DAY 13()====================================================================================
// O(num.size())
string removeKdigits(string num, int k)
{
    int n = num.size();
    stack<char> st;
    for (int i = 0; i < n; i++)
    {
        while (!st.empty() && num[i] < st.top() && k != 0)
        {
            st.pop();
            k--;
        }
        st.push(num[i]);
    }

    while (k--)
        st.pop();

    string nnum;
    while (!st.empty())
    {
        nnum += st.top();
        st.pop();
    }
    reverse(nnum.begin(), nnum.end());
    int i = 0;
    while (nnum[i] == '0')
        i++;
    return (nnum.substr(i, nnum.size()) != "") ? nnum.substr(i, nnum.size()) : "0";
}

//DAY 14()=======================================================================================

class Node
{
public:
    int wordEnd = 0;
    vector<Node *> childs;
    Node()
    {
        this->wordEnd = 0;
        this->childs.assign(26, nullptr);
    }
};

Node *root = nullptr;
Trie()
{
    root = new Node();
}

/** Inserts a word into the trie. */
void insert(string word)
{
    Node *curr = root;
    for (auto c : word)
    {
        int idx = c - 'a';
        if (curr->childs[idx] == nullptr)
            curr->childs[idx] = new Node();
        curr = curr->childs[idx];
    }
    curr->wordEnd++;
}

/** Returns if the word is in the trie. */
bool search(string word)
{
    Node *curr = root;
    for (auto c : word)
    {
        int idx = c - 'a';
        if (curr->childs[idx] == nullptr)
            return false;
        curr = curr->childs[idx];
    }
    return curr->wordEnd > 0;
}

/** Returns if there is any word in the trie that starts with the given prefix. */
bool startsWith(string prefix)
{
    Node *curr = root;
    for (auto c : prefix)
    {
        int idx = c - 'a';
        if (curr->childs[idx] == nullptr)
            return false;
        curr = curr->childs[idx];
    }
    return true;
}
}
;

/**
 * Your Trie object will be instantiated and called as such:
 * Trie* obj = new Trie();
 * obj->insert(word);
 * bool param_2 = obj->search(word);
 * bool param_3 = obj->startsWith(prefix);
 */

//DAY 15()=====================================================================================
// O(n)
int kedanes(int n, vector<int> A, int sum, int maxsum)
{
    for (int i = 0; i < n; i++)
    {
        sum += A[i];
        if (sum < 0)
            sum = 0;
        maxsum = max(sum, maxsum);
    }
    return maxsum;
}

int maxSubarraySumCircular(vector<int> &A)
{
    int n = A.size();

    bool flag = true;
    int maxi = INT_MIN;
    for (int i = 0; i < n; i++)
    {
        maxi = max(A[i], maxi);
        if (A[i] > 0)
        {
            flag = false;
            break;
        }
    }
    if (flag)
        return maxi;
    int circularsum = 0;
    int maxsum = kedanes(n, A, 0, INT_MIN);
    for (int i = 0; i < n; i++)
    {
        circularsum += A[i];
        A[i] = -A[i];
    }
    int maxnegsum = kedanes(n, A, 0, INT_MIN);
    circularsum += maxnegsum;

    return max(maxsum, circularsum);
}

//DAY 16(Odd Even Linked List)====================================================================
// O(nodes)
ListNode *oddEvenList(ListNode *head)
{
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr)
        return head;
    ListNode *evenhead = head->next;
    ListNode *node = head;
    int nodecount = 1;
    ListNode *temp = nullptr;
    while (node->next != nullptr)
    {
        temp = node;
        node = node->next;
        temp->next = nullptr;
        temp->next = node->next;
        // prev = temp;
        nodecount++;
    }
    if (nodecount % 2 == 0)
        temp->next = evenhead;
    else
        node->next = evenhead;
    return head;
}

//DAY 17(Find All Anagrams in a String)==========================================================
// (my method - O(s.size()*s.size()))
vector<int> findAnagrams(string s, string p)
{
    int n = s.size();
    int m = p.size();

    vector<int> ispres(26, 0);
    for (int i = 0; i < m; i++)
        ispres[p[i] - 'a']++;

    vector<int> ans;
    for (int i = 0; i < n; i++)
    {
        bool flag = false;
        if (ispres[s[i] - 'a'])
        {
            // cout<<s[i]<<endl;
            flag = true;
            int j = i;
            int count = 0;

            while (j != n && ispres[s[j] - 'a'])
            {
                count++;
                // cout<<j<<" "<<s[j]<<" "<<count<<endl;
                // cout<<ispres[0]<<" "<<ispres[1]<<" "<<ispres[2]<<endl;
                if (count == m)
                {
                    ans.push_back(i);
                    break;
                }
                ispres[s[j] - 'a']--;
                j++;
            }
            // i = j-1;
        }
        if (flag)
        {
            memset(&ispres[0], 0, 26);
            for (int i = 0; i < m; i++)
                ispres[p[i] - 'a']++;
        }
    }
    return ans;
}

/////////OR////////////
// O(n)
vector<int> findAnagrams(string s, string p)
{
    int m = p.size();
    int n = s.size();
    vector<int> sc(26, 0);
    vector<int> pc(26, 0);

    for (int i = 0; i < m; i++)
        pc[p[i] - 'a']++;
    vector<int> ans;
    for (int i = 0; i < n; i++)
    {
        if (i >= m)
            sc[s[i - m] - 'a']--;
        sc[s[i] - 'a']++;
        if (sc == pc)
            ans.push_back(i - m + 1);
    }
    return ans;
}

//DAY 18(Permutation in String)========================================================================

bool checkInclusion(string s1, string s2)
{
    int n = s1.size();
    int m = s2.size();
    vector<int> sc1(26, 0);
    vector<int> sc2(26, 0);

    for (int i = 0; i < n; i++)
        sc1[s1[i] - 'a']++;
    for (int i = 0; i < m; i++)
    {
        if (i >= n)
            sc2[s2[i - n] - 'a']--;
        sc2[s2[i] - 'a']++;
        if (sc2 == sc1)
            return true;
    }
    return false;
}

//DAY 19(Online Stock Span)======================================================================================

//using vector :-
class StockSpanner
{
public:
    vector<pair<int, int>> span;
    int i;
    StockSpanner()
    {
        this->span = {};
        this->i = 0;
    }
    int next(int price)
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);

        span.push_back(make_pair(price, 1));
        int j = i - 1;
        while (j >= 0)
        {
            if (span[j].first <= span[i].first)
            {
                span[i].second += span[j].second;
                j -= span[j].second;
            }
            else
                break;
        }
        cout << i << " " << span[i].first << " " << span[i].second << endl;
        i++;
        return span[i - 1].second;
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */

//////////////////OR/////////////////////
// optimized approach(using stack) :-
class StockSpanner
{
public:
    stack<pair<int, int>> span;
    StockSpanner()
    {
        ios_base::sync_with_stdio(false);
        cin.tie(nullptr);
        cout.tie(nullptr);
    }
    int next(int price)
    {
        int ans = 1;
        ;
        while (!span.empty() && span.top().first <= price)
        {
            ans += span.top().second;
            span.pop();
        }
        span.push({price, ans});
        // cout<<span.top().first<<" "<<span.top().second<<endl;

        return span.top().second;
    }
};

/**
 * Your StockSpanner object will be instantiated and called as such:
 * StockSpanner* obj = new StockSpanner();
 * int param_1 = obj->next(price);
 */

//DAY 20()====================================================================================
// O(k*nodes)
int mini = INT_MAX;
int inoder(TreeNode *node, int lastmin)
{
    if (node == nullptr)
        return INT_MAX;

    inoder(node->left, lastmin);

    if (node->val > lastmin)
        mini = min(node->val, mini);

    inoder(node->right, lastmin);

    return mini;
}

int kthSmallest(TreeNode *root, int k)
{
    int kmin = INT_MIN;
    while (k--)
    {
        kmin = inoder(root, kmin);
        mini = INT_MAX;
    }
    return kmin;
}

///////////////////OR////////////////////
// O(height of BST) - (by loops)
int kthSmallest(TreeNode *root, int k)
{
    stack<TreeNode *> mintree;
    TreeNode *kmin;
    while (k--)
    {
        for (; root != nullptr; root = root->left)
            mintree.push(root);
        kmin = mintree.top();
        mintree.pop();
        root = kmin->right;
    }
    return kmin->val;
}

////////////////OR///////////////////
// by recursion
int idx = 0;
int kmin;
void inoder(TreeNode *node, int k)
{
    if (node == nullptr)
        return;
    inoder(node->left, k);
    idx++;
    if (idx == k)
        kmin = node->val;
    else
        inoder(node->right, k);
}

int kthSmallest(TreeNode *root, int k)
{
    inoder(root, k);
    return kmin;
}

//DAY 22(Count Square Submatrices with All Ones)================================================================

// O(n^4)
int countSquares(vector<vector<int>> &matrix)
{
    int n = matrix.size();
    int m = matrix[0].size();

    int squares = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            for (int s = 0; (j + s < m) && (i + s < n); s++)
            {
                bool flag = true;
                for (int k = 0; k <= s; k++)
                {
                    // cout << matrix[i + s][j + k] << " " << matrix[i + k][j + s] << endl;
                    if (matrix[i + s][j + k] == 0 || matrix[i + k][j + s] == 0)
                    {
                        flag = false;
                        break;
                    }
                }
                if (!flag)
                    break;
                squares++;
                // cout << endl;
            }
        }
    }
    return squares;
}

//////////////OR/////////////////
// O(n^2)
int countSquares(vector<vector<int>> &matrix)
{
    int n = matrix.size();
    int m = matrix[0].size();

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int valid_sqsize = 0;
            if (i && j && matrix[i][j])
                valid_sqsize = min(min(matrix[i - 1][j], matrix[i][j - 1]), matrix[i - 1][j - 1]);
            matrix[i][j] += valid_sqsize;
        }
    }
    int squares = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            squares += matrix[i][j];
    return squares;
}

//DAY 23(Sort Characters By Frequency)==============================================================================

//     template <typename T1, typename T2>
// struct sort_by_second {
//     typedef pair<T1, T2> type;
//     bool operator ()(type const& a, type const& b) const {
//         return a.second > b.second;
//     }
// };

static bool sort_by_second(const pair<char, int> &p1, const pair<char, int> &p2)
{
    return (p1.second > p2.second);
}

string frequencySort(string s)
{
    if (s.size() == 0)
        return "";
    unordered_map<char, int> freq;
    for (int i = 0; i < s.size(); i++)
    {
        if (freq.find(s[i]) != freq.end())
            freq[s[i]]++;
        else
            freq.insert(pair<char, int>(s[i], 1));
    }
    vector<pair<char, int>> nmap(freq.begin(), freq.end());
    sort(nmap.begin(), nmap.end(), sort_by_second);

    // for (int i = 0; i < nmap.size(); i++)
    // {
    //     cout << nmap[i].first << ": " << nmap[i].second << endl;
    // }
    string str = "";
    for (auto c = nmap.begin(); c != nmap.end(); c++)
        while (c->second--)
            str += c->first;
    return str;
}