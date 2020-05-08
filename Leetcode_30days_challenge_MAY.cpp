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

class Solution {
public:
    bool checkStraightLine(vector<vector<int>>& coordinates) 
    {
        ios::sync_with_stdio(0);
        cin.tie(0);
        cout.tie(0);
        
        int n = coordinates.size();
        if(n == 2)
            return true;
        if((coordinates[1][0]-coordinates[0][0]) == 0)
        {
            for(int i=0;i<n-1;i++)
            {
                // cout<<(coordinates[i+1][0]-coordinates[i][0])<<endl;
                if((coordinates[i+1][0]-coordinates[i][0]) != 0)
                    return false;
            }
        }
        else
        {
            float m = (float)(coordinates[1][1]-coordinates[0][1])/(coordinates[1][0]-coordinates[0][0]);    
            for(int i=0;i<n-1;i++)
            {
                // cout<<(float)(coordinates[i+1][1]-coordinates[i][1])/(coordinates[i+1][0]-coordinates[i][0])<<endl;
                if((coordinates[i+1][0]-coordinates[i][0]) == 0)
                    return false;
                if((float)(coordinates[i+1][1]-coordinates[i][1])/(coordinates[i+1][0]-coordinates[i][0]) != m)
                    return false;
            }
        }
        return true;
    }
};