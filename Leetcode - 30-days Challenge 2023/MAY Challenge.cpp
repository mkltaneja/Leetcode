// DAY 1 (1491. Average Salary Excluding the Minimum and Maximum Salary)===================================================================

double average(vector<int>& salary) 
{
    int minSalary = INT_MAX, maxSalary = INT_MIN, sumSalary = 0;
    for(int x : salary)
    {
        minSalary = min(minSalary, x);
        maxSalary = max(maxSalary, x);
        sumSalary += x;
    }
    sumSalary -= (minSalary + maxSalary);

    return 1.0*sumSalary / (salary.size()-2);
}

// DAY 2 (1822. Sign of the Product of an Array)==========================================================================================

int arraySign(vector<int>& nums) 
{
    int ans = 1;
    for(int x : nums)
        ans *= (x == 0)? 0 : (x > 0? 1 : -1);

    return ans;
}

// DAY 3 (2215. Find the Difference of Two Arrays)==================================================================================

vector<vector<int>> findDifference(vector<int>& nums1, vector<int>& nums2) 
{
    int n = nums1.size(), m = nums2.size();

    unordered_set<int> st1, st2;
    for(int x : nums1)
        st1.insert(x);
    for(int x : nums2)
        st2.insert(x);

    vector<vector<int>> answer(2);
    for(int x : st1)
        if(!st2.count(x))
            answer[0].push_back(x);
    for(int x : st2)
        if(!st1.count(x))
            answer[1].push_back(x);

    return answer;
}

// DAY 5 (1456. Maximum Number of Vowels in a Substring of Given Length)=====================================================================

bool isVowel(char c)
{
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u');
}

int maxVowels(string s, int k) 
{
    int ans = 0;
    unordered_map<char,int> cnt;
    for(int i = 0; i < s.size(); i++)
    {
        if(isVowel(s[i]))
            cnt[s[i]]++;
        if(i >= k && isVowel(s[i-k]))
            cnt[s[i-k]]--;
        ans = max({ans, cnt['a'] + cnt['e'] + cnt['i'] + cnt['o'] + cnt['u']});
    }
    return ans;
}

// DAY 6 (1498. Number of Subsequences That Satisfy the Given Sum Condition)=========================================================================

int mod = 1e9 + 7;

int binpowmod(int a, int b)
{
    long ans = 1;
    while(b)
    {
        if(b & 1)
            ans = (ans % mod * a % mod) % mod;
        a = ((long)a % mod * a % mod) % mod;
        b >>= 1;
    }

    return ans % mod;
}

int numSubseq(vector<int>& nums, int target) 
{
    int n = nums.size();
    sort(nums.begin(), nums.end());

    int ans = 0;
    for(int i = 0; i < n; i++)
    {
        int j = upper_bound(nums.begin() + i, nums.end(), target - nums[i]) - nums.begin();
        if(i == j) continue;
        int x = binpowmod(2, j - i - 1);
        ans = (ans % mod + x % mod) % mod;
    }

    return ans;
}

// DAY 9 (1572. Matrix Diagonal Sum)======================================================================================

int diagonalSum(vector<vector<int>>& mat) 
{
    int n = mat.size();
    int sum = 0;
    for(int i = 0; i < n; i++)
        sum += mat[i][i] + mat[i][n-i-1];
    return sum - ((n&1)? mat[n/2][n/2] : 0);
}
