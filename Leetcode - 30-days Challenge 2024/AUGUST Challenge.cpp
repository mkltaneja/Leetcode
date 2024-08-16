// DAY 1 (2678. Number of Senior Citizens)=================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int countSeniors(vector<string>& details)
{
    int totalPassengers = 0;
    for(string detail : details)
        totalPassengers += (detail[11]-'0') * 10 + (detail[12]-'0') > 60;
    
    return totalPassengers;
}

// DAY 2 (2134. Minimum Swaps to Group All 1's Together II)========================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int minSwaps(vector<int>& nums)
{
    int size = nums.size();
    int totalOnes = 0;
    for(int num : nums)
        totalOnes += num;
    
    int currOnes = 0;
    for(int idx = 0; idx < totalOnes; idx++)
        currOnes += nums[idx];
    
    int minSwaps = totalOnes - currOnes;
    for(int idx = 0; idx < size; idx++)
    {
        currOnes += nums[(idx + totalOnes) % size];
        currOnes -= nums[idx];
        minSwaps = min(minSwaps, totalOnes - currOnes);
    }

    return minSwaps;
}

// DAY 3 (1460. Make Two Arrays Equal by Reversing Subarrays)=================================================================================

// Time Complexity = O(n + 1000)
// Space Complexity = O(1000)

bool canBeEqual(vector<int>& target, vector<int>& arr)
{
    vector<int> freq(1001, 0);
    for(int num : arr)
        freq[num]++;
    for(int num : target)
        freq[num]--;
    for(int num = 1; num <= 1000; num++)
        if(freq[num])
            return false;

    return true;
}

// DAY 4 (1508. Range Sum of Sorted Subarray Sums)=====================================================================================================

// APPROACH 1 (Brute Force)

// Time Complexity = O(n^2)
// Space Complexity = O(n^2)

const int MOD = 1e9 + 7;
int rangeSum(vector<int>& nums, int n, int left, int right)
{
    vector<int> narr;
    for(int i = 0; i < n; i++)
    {
        int currSum = 0;
        for(int j = i; j < n; j++)
        {
            currSum += nums[j];
            narr.push_back(currSum);
        }
    }
    sort(narr.begin(), narr.end());

    int ans = 0;
    for(int i = left-1; i < right; i++)
        ans = (ans % MOD + narr[i] % MOD) % MOD;

    return ans;
}

// APPROACH 2 (Binary Search)

// Time Complexity = O(n*log(sum))
// Space Complexity = O(1)

const int MOD = 1e9 + 7;
int rangeSum(vector<int>& nums, int n, int left, int right)
{
    long long ans = getSumOfFirstK(nums, n, right) % MOD - getSumOfFirstK(nums, n, left-1) % MOD;
    return (ans + MOD) % MOD;
}

pair<int, long long> totalSubarraysLessThanMaxsum(vector<int>& nums, int n, int maxSum)
{
    int count = 0;
    long long currSum = 0, windowSum = 0, totalSum = 0;
    for(int i = 0, j = 0; i < n; i++)
    {
        currSum += nums[i];
        windowSum += nums[i] * (i - j + 1);
        while(currSum > maxSum)
        {
            windowSum -= currSum;
            currSum -= nums[j++];
        }
        count += i - j + 1;
        totalSum += windowSum;
    }

    return {count, totalSum};
}

long long getSumOfFirstK(vector<int>& nums, int n, int k)
{
    int minSum = *min_element(nums.begin(), nums.end());
    int maxSum = accumulate(nums.begin(), nums.end(), 0);
    long long lo = minSum, hi = maxSum;

    while(lo <= hi)
    {
        int mid = lo + ((hi - lo) >> 1);

        if(totalSubarraysLessThanMaxsum(nums, n, mid).first >= k)
            hi = mid - 1;
        else lo = mid + 1;
    }

    auto [count, sum] = totalSubarraysLessThanMaxsum(nums, n, lo);

    return sum - lo * (count - k);
}

// DAY 5 (2053. Kth Distinct String in an Array)==============================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

string kthDistinct(vector<string>& arr, int k)
{
    int size = arr.size();
    unordered_map<string, int> freqMap;
    for(int idx = 0; idx < size; idx++)
        freqMap[arr[idx]]++;
    
    int visited = 0;
    for(int idx = 0; idx < size; idx++)
        if(freqMap[arr[idx]] == 1 && ++visited == k)
            return arr[idx];
    
    return "";
}

// DAY 6 (3016. Minimum Number of Pushes to Type Word II)=======================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int minimumPushes(string word)
{
    vector<int> charFreqMap(26, 0);
    for(char c : word)
        charFreqMap[c-'a']++;
    sort(charFreqMap.rbegin(), charFreqMap.rend());
    
    int numKeysPushed = 0;
    for(int idx = 0; idx < 26 && charFreqMap[idx]; idx++)
        numKeysPushed += charFreqMap[idx] * ((idx / 8) + 1);
    
    return numKeysPushed;
}

// DAY 8 (885. Spiral Matrix III)================================================================================================

// Time Complexity = O(n*m)
// Space Complexity = O(n*m)

vector<vector<int>> spiralMatrixIII(int rows, int cols, int rStart, int cStart)
{
    int totalNums = rows * cols;
    int dir[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    int minRow = rStart, minCol = cStart, maxRow = rStart, maxCol = cStart;
    int currRow = rStart, currCol = cStart;
    int numsCovered = 0;
    int currDir = 0;
    vector<vector<int>> ans;

    while(numsCovered < totalNums)
    {
        while(numsCovered < totalNums && currCol >= minCol && currCol <= maxCol && currRow >= minRow && currRow <= maxRow)
        {
            if(currRow >= 0 && currRow < rows && currCol >= 0 && currCol < cols)
            {
                ans.push_back({currRow, currCol});
                numsCovered++;
            }
            
            currRow += dir[currDir][0];
            currCol += dir[currDir][1];
        }

        if(currDir == 0)
            maxCol++;
        else if(currDir == 1)
            maxRow++;
        else if(currDir == 2)
            minCol--;
        else minRow--;

        currDir = (currDir + 1) % 4;
    }

    return ans;
}

// DAY 9 (840. Magic Squares In Grid)=============================================================================

// Time Compexity = O(n*m)
// Space Compexity = O(1)

bool isMagicSquare(int row, int col, vector<vector<int>> &grid)
{
    unordered_set<int> st;
    int rowSum[3] = {0}, colSum[3] = {0}, diagSum[2] = {0};
    for(int r = row; r < row + 3; r++)
    {
        for(int c = col; c < col + 3; c++)
        {
            if(grid[r][c] < 1 || grid[r][c] > 9)
                return false;
            st.insert(grid[r][c]);

            int ridx = r - row;
            int cidx = c - col;
            rowSum[ridx] += grid[r][c];
            colSum[cidx] += grid[r][c];
            if(ridx == cidx)
                diagSum[0] += grid[r][c];
            if(ridx + cidx == 2)
                diagSum[1] += grid[r][c];
        }
    }
    if((rowSum[0] != rowSum[1] || rowSum[0] != rowSum[2]) || (colSum[0] != colSum[1] || colSum[0] != colSum[2]) || (diagSum[0] != diagSum[1]) || st.size() != 9)
        return false;
    return true;
}

int numMagicSquaresInside(vector<vector<int>>& grid)
{
    int rows = grid.size(), cols = grid[0].size();
    int magicSquares = 0;
    for(int row = 0; row <= rows-3; row++)
        for(int col = 0; col <= cols-3; col++)
            if(isMagicSquare(row, col, grid))
                magicSquares++;

    return magicSquares;
}

// DAY 13 (40. Combination Sum II)============================================================

// Time Complexity = O(2^n)
// Space Complexity = O(2^n)

vector<vector<int>> ans;

void getCombinations(int i, vector<int> &candidates, int target, vector<int> &curr)
{
    if(target <= 0)
    {
        if(target == 0)
            ans.push_back(curr);
        return;
    }
    for(int j = i; j < candidates.size(); j++)
    {
        if(j == i || candidates[j] != candidates[j-1])
        {
            curr.push_back(candidates[j]);
            getCombinations(j+1, candidates, target - candidates[j], curr);
            curr.pop_back();
        }
    }
}

vector<vector<int>> combinationSum2(vector<int>& candidates, int target)
{
    sort(candidates.begin(), candidates.end());
    vector<int> curr;
    getCombinations(0, candidates, target, curr);
    return ans;
}

// DAY 15 (860. Lemonade Change)===================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

bool lemonadeChange(vector<int>& bills)
{
    int fives = 0, tens = 0;
    for(int bill : bills)
    {
        if(bill == 5)
            fives++;
        else if(bill == 10)
        {
            if(!fives)
                return false;
            fives--;
            tens++;
        }
        else
        {
            if(tens && fives)
                tens--, fives--;
            else if(fives >= 3)
                fives -= 3;
            else return false;
        }
    }

    return true;
}

// DAY 16 (624. Maximum Distance in Arrays)======================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int maxDistance(vector<vector<int>>& arrays)
{
    int st1 = -1, st2 = -1, end1 = -1, end2 = -1;
    for(int idx = 0; idx < arrays.size(); idx++)
    {
        if(st1 == -1 || arrays[st1][0] >= arrays[idx][0])
        {
            st2 = st1;
            st1 = idx;
        }
        else if(st2 == -1 || arrays[st2][0] >= arrays[idx][0])
            st2 = idx;
        
        if(end1 == -1 || arrays[end1].back() <= arrays[idx].back())
        {
            end2 = end1;
            end1 = idx;
        }
        else if(end2 == -1 || arrays[end2].back() <= arrays[idx].back())
            end2 = idx;
    }

    return st1 == end1? max(arrays[end1].back() - arrays[st2][0], arrays[end2].back() - arrays[st1][0]) : arrays[end1].back() - arrays[st1][0];
}
