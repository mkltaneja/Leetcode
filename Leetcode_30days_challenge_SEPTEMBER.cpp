// DAY 1 (Largest Time For Given Digits)===================================================

string largestTimeFromDigits(vector<int>& A) 
{
    string res = "";
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            for(int k=0; k<4; k++)
            {
                if(i == j || j == k || k == i)
                    continue;
                string hh = to_string(A[i]) + to_string(A[j]);
                string mm = to_string(A[k]) + to_string(A[6 - (i+j+k)]);
                string time = hh + ":" + mm;
                if(hh < "24" && mm < "60" && time > res)
                    res = time;
            }
        }
    }
    return res;
}

// DAY 2 (Contains Duplicate III)======================================

// MEHTOD 1 
// TLE
bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t)
{
    int n = nums.size();
    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<=(i+k) && j<n; j++)
        {
            long diff = abs((long)nums[i] - (long)nums[j]);
            if(diff <= t)
                return true;
        }
    }
    return false;
}

//////////////////////////////////////////OR///////////////////////////

// METHOD 2 (Using multimap)
// AC

bool containsNearbyAlmostDuplicate(vector<int>& nums, int k, int t) {
    multimap <int,int> mp;
    for(int i=0;i<nums.size();i++) mp.insert(pair< int, int >(nums[i], i));
    
    multimap <int,int>::iterator it;
    multimap <int,int>::iterator itnext;
    
    for(it=mp.begin();it!=mp.end();it++){
        itnext = it;
        while(true){
            itnext++;
            if(itnext == mp.end()) break;
            long long a = (*it).first;
            long long b = (*itnext).first;
            if(abs(a-b) <= t)  
            {
                if(abs((*it).second - (*itnext).second) <= k) 
                    return true;
            }
            else break;
        }
    }            
    return false;
}

// DAY 3 (Repeated Substring Pattern)===========================================================================

// METHOD 1 (Naive - by selecting the substrings of the factors)
bool checksub_i(int i, string &s)
{
    string sub = s.substr(0, i);
    for(int j = 0; j < s.size(); j += i)
        if(s.substr(j, i) != sub)
            return false;
    return true;
}

bool repeatedSubstringPattern(string &s) 
{
    int n = s.size();
    if(n == 0 || n == 1)
        return false;
    
    for(int i=1; i*i <= n; i++)
    {
        if(n % i == 0)
        {
            if(checksub_i(i,s))
                return true;
            if(i != 1 && checksub_i(n/i, s))
                return true;
        }
    }
    return false;
}

////////////////////////////////////OR///////////////////////////////

// METHOD 2 (One - Liner)
bool repeatedSubstringPattern(string s)
{
    return (s+s).substr(1, 2*s.size()-2).find(s) != -1;
}

// DAY 4 (Partition Labels)===============================================================================

vector<int> partitionLabels(string S) 
{
    int n = S.size();
    vector<int> lastocc(26,0);
    for(int i = 0; i < n; i++)
        lastocc[S[i] - 'a'] = i;
    // for(int i=0; i<26; i++)
    //     cout<<(char)(i + 'a')<<" "<<lastocc[i]<<endl;
    
    vector<int> slen;
    int lo = lastocc[S[0] - 'a'];
    int i = 0;
    while(true)
    {
        int st = i;
        while(i++ < lo)
            if(lastocc[S[i] - 'a'] > lo)
                lo = lastocc[S[i] - 'a'];
        slen.push_back(i - st);
        if(i == n)
            break;
        lo = lastocc[S[i] - 'a'];
    }
    return slen;
}

// DAY 5 (Image Overlap)=============================================================

int largestOverlap_(vector<vector<int>>& A, vector<vector<int>>& B) 
{
    int n = A.size();
    int maxcount = 0;
    for(int x = 0; x < n; x++)
    {
        for(int y = 0; y < n; y++)
        {
            int count = 0;
            for(int i = x; i < n; i++)
                for(int j = y; j < n; j++)
                    if(A[i][j] == 1 && B[i-x][j-y] == 1)
                        count++;
            maxcount = max(maxcount, count);
        }
    }
    return maxcount;
}

public:
int largestOverlap(vector<vector<int>>& A, vector<vector<int>>& B) 
{
    return max(largestOverlap_(A,B), largestOverlap_(B,A));
}

// DAY 7 (Word Pattern) ===========================================================================

bool wordPattern(string pattern, string str) 
{
    vector<string> map(26);
    stringstream ss(str);
    int count = 0;
    string word;
    while(ss >> word)
        count++;
    if(pattern.size() != count)
        return false;
    
    stringstream ss1(str);
    set<string> st;
    int i = 0;
    while(ss1 >> word)
    {
        char c = pattern[i++];
    
        if(map[c - 'a'] != "" && map[c - 'a'] != word)
            return false;
        
        if(map[c - 'a'] == "")
        {
            if(st.find(word) != st.end())
                return false;
            map[c - 'a'] = word;
            st.insert(word);
        }
    }
    return true;
}

// DAY 8 (Sum of Root To Leaf Binary Numbers)====================================================================

// METHOD 1 (Using string of binary)
void findsum(TreeNode* node, string bin, int &sum)
{
    if(!node)
        return;
    
    bin += to_string(node->val);
    
    if(!node->left && !node->right)
    {
        int num = 0, t = 1;
        for(int i = bin.size()-1; i >= 0; i--)
        {
            num += (bin[i]-'0') * t;
            t *= 2;
        }
        // cout<<bin<<" "<<num<<endl;
        sum += num;
        return;
    }
    findsum(node->left, bin, sum);
    findsum(node->right, bin, sum);
    
    bin[bin.size()-1] = NULL;
}

public:
int sumRootToLeaf(TreeNode* root) 
{
    int sum = 0;
    findsum(root, "", sum);
    return sum;
}