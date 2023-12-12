
// DAY 1 (1662. Check If Two String Arrays are Equivalent)========================================================================================

bool arrayStringsAreEqual(vector<string>& word1, vector<string>& word2) 
{
    int i = 0, j = 0, ii = 0, jj = 0, n = word1.size(), m = word2.size();
    while(i < n && j < m)
    {
        if(ii < word1[i].size() && jj < word2[j].size() && word1[i][ii] != word2[j][jj]) 
            return false;
        ii++, jj++;
        if(ii == word1[i].size()) i++, ii = 0;
        if(jj == word2[j].size()) j++, jj = 0;
    }
    return i == n && j == m;
}

// DAY 2 (1160. Find Words That Can Be Formed by Characters)=====================================================================================================

int countCharacters(vector<string>& words, string chars) 
{
    vector<int> map(26, 0);
    for(char c : chars)
        map[c - 'a']++;
    
    int ans = 0;
    for(string word : words)
    {
        vector<int> tmp = map;
        bool isValid = true;
        for(char c : word)
        {
            if(--tmp[c-'a'] < 0)
            {
                isValid = false;
                break;
            }
        }
        if(isValid) ans += word.size();
    }
    return ans;
}

// DAY 3 (1266. Minimum Time Visiting All Points)========================================================================================================

int minTimeToVisitAllPoints(vector<vector<int>>& points) 
{
    int n = points.size();
    int time = 0;
    for(int i = 1; i < n; i++)
    {
        int di = abs(points[i][0] - points[i-1][0]);
        int dj = abs(points[i][1] - points[i-1][1]);
        time += max(di, dj);
    }
    return time;
}

// DAY 4 (2264. Largest 3-Same-Digit Number in String)=========================================================================================

string largestGoodInteger(string num) 
{
    int n = num.size();
    int maxDig = -1;
    string maxNum = "";
    
    if(n < 3) return maxNum;

    for(int i = 2; i < n; i++)
        if(num[i] == num[i-1] && num[i] == num[i-2])
            maxDig = max(maxDig, num[i]-'0');
    maxNum = maxDig == -1? "" :
        maxDig == 0? "000" : to_string(maxDig*100 + maxDig*10 + maxDig);
    return maxNum;
}

// DAY 5 (1688. Count of Matches in Tournament)=================================================================================================

int numberOfMatches(int n) 
{
    int totalMatches = 0;
    while(n != 1)
    {
        totalMatches += n/2;
        n = (n+1)/2;
    }
    return totalMatches;
}

// DAY 6 (1716. Calculate Money in Leetcode Bank)========================================================================================

int totalMoney(int n) 
{
    int properGroups = n / 7;
    int lastGroupCount = n % 7;
    int sumOfFirstSeven = (7 * (7 + 1)) / 2;
    
    int ans = properGroups * sumOfFirstSeven + (properGroups * (properGroups - 1) / 2) * 7;
    ans += (lastGroupCount * (lastGroupCount + 1)) / 2 + lastGroupCount * properGroups;

    return ans;
}

// DAY 7 (1903. Largest Odd Number in String)=================================================================================================

string largestOddNumber(string num)
{
    int lastOddIdx = -1;
    for(int index = num.size()-1; index >= 0 && lastOddIdx == -1; index--)
        lastOddIdx = ((num[index] - '0') & 1)? index : lastOddIdx;
    string ansSubstring = num.substr(0, lastOddIdx+1);
    return ansSubstring;
}

// DAY 8 (606. Construct String from Binary Tree)======================================================================================

string ans = "";
void tree2strHelper(TreeNode* node)
{
    if(!node) return;
    if(!node->left && !node->right)
    {
        ans += to_string(node->val);
        return;
    }

    ans += to_string(node->val);
    ans += "(";
    tree2strHelper(node->left);
    ans += ")";
    if(node->right)
    {
        ans += "(";
        tree2strHelper(node->right);
        ans += ")";
    }
}


string tree2str(TreeNode* root)
{
    tree2strHelper(root);
    return ans;
}

// DAY 9 (94. Binary Tree Inorder Traversal)==============================================================================================

vector<int> inorderTraversal(TreeNode* root) 
{
    vector<int> ans;
    while(root)
    {
        if(!root->left)
        {
            ans.push_back(root->val);
            root = root->right;
        }
        else
        {
            TreeNode* prev = root->left;
            while(prev->right && prev->right != root)
                prev = prev->right;
            if(prev->right == nullptr)
            {
                prev->right = root;
                root = root->left;
            }
            else 
            {
                ans.push_back(root->val);
                prev->right = nullptr;
                root = root->right;
            }
        }
    }
    return ans;
}

// DAY 10 (867. Transpose Matrix)=============================================================================

vector<vector<int>> transpose(vector<vector<int>>& matrix) 
{
    int n = matrix.size(), m = matrix[0].size();
    vector<vector<int>> ansMatrix(m, vector<int>(n));
    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            ansMatrix[j][i] = matrix[i][j];
    return ansMatrix;
}

// DAY 11 (1287. Element Appearing More Than 25% In Sorted Array)===============================================================

int findSpecialInteger(vector<int>& arr) 
{
    int n = arr.size();
    int threshold = ceil(n/4);
    for(int idx = 0; idx < n; idx++)
        if(arr[idx] == arr[idx + threshold])
            return arr[idx];
    return -1;
}

// DAY 12 (1464. Maximum Product of Two Elements in an Array)==========================================================================

int maxProduct(vector<int>& nums)
{
    int maxNum = 0, maxNum2 = 0;
    for(int x : nums)
    {
        if(x > maxNum)
        {
            maxNum2 = maxNum;
            maxNum = x;
        }
        else maxNum2 = max(maxNum2, x);
    }
    return (maxNum - 1) * (maxNum2 - 1);
}
