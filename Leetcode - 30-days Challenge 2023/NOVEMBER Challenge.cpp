
// DAY 1 (501. Find Mode in Binary Search Tree)=======================================================================================

vector<int> ans;
int maxCnt = 0, cnt = 0, prev = INT_MIN;

void inorder(TreeNode* node)
{
    if(!node) return;

    inorder(node->left);

    if(node->val == prev) cnt++;
    else cnt = 1;
    if(cnt >= maxCnt)
    {
        if(cnt > maxCnt)
            ans.clear();
        ans.push_back(node->val);
        maxCnt = cnt;
    }
    prev = node->val;

    inorder(node->right);
}

vector<int> findMode(TreeNode* root)
{
    inorder(root);
    return ans;
}

// DAY 2 (2265. Count Nodes Equal to Average of Subtree)=================================================================================================================

int ans = 0;

pair<int,int> dfs(TreeNode* node)
{
    if(!node) return {0, 0};

    pair<int,int> lAns = dfs(node->left);
    pair<int,int> rAns = dfs(node->right);

    int sum = lAns.first + rAns.first + node->val;
    int tot = lAns.second + rAns.second + 1;
    
    ans += (sum / tot) == node->val;

    return {sum, tot};
}

int averageOfSubtree(TreeNode* root) 
{
    dfs(root);
    return ans;
}

// DAY 3 (1441. Build an Array With Stack Operations)===========================================================================

const string PUSH = "Push";
const string POP = "Pop";
vector<string> buildArray(vector<int>& target, int n) 
{
    vector<string> ans;
    for(int in = 1, i = 0, pops = 0; in <= n && i < target.size(); in++)
    {
        if(in == target[i])
        {
            while(pops--)
                ans.push_back(POP);
            ans.push_back(PUSH);
            i++;
            pops = 0;
        }
        else 
        {
            ans.push_back(PUSH);
            pops++;
        }
    }
    return ans;
}

// DAY 4 (1503. Last Moment Before All Ants Fall Out of a Plank)==========================================================================================

int getLastMoment(int n, vector<int>& left, vector<int>& right) 
{
    int ans = 0;
    for(int x : left)
        ans = max(ans, x);
    for(int x : right)
        ans = max(ans, n-x);
    return ans;
}

// DAY 5 (1535. Find the Winner of an Array Game)=========================================================================================

// APPROACH 2 (Using Deque) --> Time = O(n+k), Space = O(n)

int getWinner(vector<int>& arr, int k) 
{
    int n = arr.size();
    if(k >= n-1) 
        return *max_element(arr.begin(), arr.end());
    
    deque<int> que;
    for(int x : arr)
        que.push_back(x);
    
    int prev = -1, prevCnt = 0;
    while(true)
    {
        int top1 = que.front();
        que.pop_front();
        int top2 = que.front();
        que.pop_front();

        int topMax = max(top1, top2);
        int topMin = min(top1, top2);
        if(prev == topMax) prevCnt++;
        else
        {
            prevCnt = 1;
            prev = topMax;
        }
        
        if(prevCnt == k) return topMax;

        que.push_front(topMax);
        que.push_back(topMin);
    }

    return -1;
}

// APPROACH 2 (2 Pointer) --> Time = O(n), Space = O(1) [OPTIMIZED]

int getWinner(vector<int>& arr, int k) 
{
    int n = arr.size();
    int left = 0, right = 1;
    
    if(k == 1) return max(arr[left], arr[right]);

    int win_count = 0;
    while(right < n)
    {
        if(arr[left] > arr[right])
        {
            right++;
            if(++win_count == k) return arr[left];
        }
        else
        {
            left = right++;
            win_count = 1;
        }
    }
    return arr[left];
}
