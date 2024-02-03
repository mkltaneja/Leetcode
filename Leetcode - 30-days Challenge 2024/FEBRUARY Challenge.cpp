
// DAY 1 (2966. Divide Array Into Arrays With Max Difference)===========================================================

// Time Complexity = O(n*logn)
// Space Complexity = O(n)

vector<vector<int>> divideArray(vector<int> &nums, int k)
{
    int size = nums.size();
    vector<vector<int>> ans;
    sort(nums.begin(), nums.end());
    for(int idx = 0; idx+2 < size; idx+=3)
    {
        if(nums[idx+2] - nums[idx] > k)
            return {};
        ans.push_back({nums[idx], nums[idx+1], nums[idx+2]});
    }
    return ans;
}

// Week 1 (293. Flip Game)=================================================================================================

// APPROACH 1 (Altering the strings while adding)

// Time Complexity = O(n^2)
// Space Complexity = O(n)

vector<string> generatePossibleNextMoves(string currentState)
{
    vector<string> possibleStates;
    for(int idx = 0; idx+1 < currentState.size(); idx++)
    {
        if(currentState[idx] == '+' && currentState[idx+1] == '+')
        {
            string tempState = currentState;
            tempState[idx] = tempState[idx+1] = '-';
            possibleStates.push_back(tempState);
        }
    }

    return possibleStates;
}

// APPROACH 2 (Adding the indices first then changing the strings separately)

// Time Complexity = O(2*n)
// Space Complexity = O(2*n)

vector<string> generatePossibleNextMoves(string currentState)
{
    vector<int> possibleStatesIdx;
    for(int idx = 0; idx+1 < currentState.size(); idx++)
        if(currentState[idx] == '+' && currentState[idx+1] == '+')
            possibleStatesIdx.push_back(idx);

    vector<string> possibleStates(possibleStatesIdx.size(), currentState);
    for(int idx = 0; idx < possibleStatesIdx.size(); idx++)
    {
        int convertIdx = possibleStatesIdx[idx];
        possibleStates[idx][convertIdx] = '-';
        possibleStates[idx][convertIdx+1] = '-';
    }

    return possibleStates;
}

// DAY 2 (1291. Sequential Digits)=========================================================================================

// APPROACH 1

// Time Complexity = ((log10(high) + 1)^2 * ((9 + (9 - log10(high))) / 2)) - ((log10(low) + 1)^2 * ((9 + (9 - log10(low))) / 2))
// Space Complexity = O((log10(high) + 1) * ((9 + (9 - log10(high))) / 2))

vector<int> sequentialDigits(int low, int high)
{
    vector<int> ans;
    int lowDigs = log10(low) + 1;
    int highDigs = log10(high) + 1;
    for(int digs = lowDigs; digs <= highDigs; digs++)
    {
        for(int start = 1; start + digs - 1 <= 9; start++)
        {
            int num = 0;
            for(int dig = start, idx = 0; idx < digs; dig++, idx++)
                num = num*10 + dig;
            if(num >= low && num <= high)
                ans.push_back(num);
        }
    }
    return ans;
}

// APPROACH 2

// Time Complexity = O(9*9 + 9*9*log2(9*9))
// Space Complexity = O(9*9)

vector<int> sequentialDigits(int low, int high)
{
    vector<int> ans;
    for(int start = 1; start <= 9; start++)
    {
        for(int end = start, num = start; end <= 9 && num <= high; )
        {
            if(num >= low)
                ans.push_back(num);
            num = num*10 + ++end;
        }
    }
    sort(ans.begin(), ans.end());
    return ans;
}

// DAY 3 (1043. Partition Array for Maximum Sum)===================================================================================

// Time Complexity = O(n*k)
// Space Complexity = O(n)

int maxSumAfterPartitioning(vector<int> &arr, int k)
{
    int size = arr.size();
    vector<int> maxSumDP(size, 0);

    for(int idx1 = size-1; idx1 >= 0; idx1--)
    {
        int maxNum = 0, tot = 1;
        for(int idx2 = idx1; idx2 < size && tot <= k; idx2++, tot++)
        {
            maxNum = max(maxNum, arr[idx2]);
            int nextMaxSum = idx2 != size-1? maxSumDP[idx2 + 1] : 0;
            maxSumDP[idx1] = max(maxSumDP[idx1], maxNum*tot + nextMaxSum);
        }
    }
    return maxSumDP[0];
}
