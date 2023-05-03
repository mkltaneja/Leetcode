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
