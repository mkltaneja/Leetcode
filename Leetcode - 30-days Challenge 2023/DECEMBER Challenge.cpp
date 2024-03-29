
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

// DAY 13 (2482. Difference Between Ones and Zeros in Row and Column)===========================================================================

vector<vector<int>> onesMinusZeros(vector<vector<int>>& grid)
{
    int n = grid.size();
    int m = grid[0].size();
    
    vector<int> rowDiff(n, 0), colDiff(m, 0);
    vector<vector<int>> diff(n, vector<int>(m, 0));
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            rowDiff[i] += (grid[i][j] == 1) - (grid[i][j] == 0);
            colDiff[j] += (grid[i][j] == 1) - (grid[i][j] == 0);
        }
    }

    for(int i = 0; i < n; i++)
        for(int j = 0; j < m; j++)
            diff[i][j] = rowDiff[i] + colDiff[j];
    
    return diff;
}

// DAY 15 (1436. Destination City)=================================================================================================

string destCity(vector<vector<string>>& paths)
{
    unordered_map<string, int> outDegree;
    for(vector<string> &path : paths)
    {
        outDegree[path[0]]++;
        outDegree[path[1]] = outDegree[path[1]];
    }
    for(pair<string, int> city_degree : outDegree)
        if(city_degree.second == 0)
            return city_degree.first;
    return "";
}

// DAY 16 (242. Valid Anagram)========================================================================================================================

bool isAnagram(string s, string t)
{
    vector<int> sMap(26, 0), tMap(26, 0);
    for(char c : s)
        sMap[c-'a']++;
    for(char c : t)
        tMap[c-'a']++;
    
    for(int i = 0; i < 26; i++)
        if(sMap[i] != tMap[i])
            return false;
    return true;
}

// DAY 17 (2353. Design a Food Rating System)=======================================================================================================

class FoodRatings {
public:

    class FoodInfo
    {
        public:
        string name;
        string cuisine;
        int rating;

        FoodInfo(){}
        FoodInfo(string name, string cuisine, int rating)
        {
            this->name = name;
            this->cuisine = cuisine;
            this->rating = rating;
        }
        bool operator<(const FoodInfo &info) const
        {
            return info.rating == rating? name < info.name : rating > info.rating;
        }
    };

    unordered_map<string, FoodInfo> foodMap;
    unordered_map<string, set<FoodInfo>> cuisineMap;

    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings)
    {
        int size = foods.size();
        for(int i = 0; i < size; i++)
        {
            FoodInfo foodInfo(foods[i], cuisines[i], ratings[i]);
            foodMap[foods[i]] = foodInfo;
            cuisineMap[cuisines[i]].insert(foodInfo);
        }
    }


    void changeRating(string food, int newRating) 
    {
        FoodInfo &foodInfo = foodMap[food];
        cuisineMap[foodInfo.cuisine].erase(foodInfo);
        foodInfo.rating = newRating;
        cuisineMap[foodInfo.cuisine].insert(foodInfo);
        FoodInfo foodInfo2 = foodMap[food];
    }


    string highestRated(string cuisine) 
    {
        FoodInfo foodInfo = *cuisineMap[cuisine].begin();
        return foodInfo.name;
    }
};


/**
* Your FoodRatings object will be instantiated and called as such:
* FoodRatings* obj = new FoodRatings(foods, cuisines, ratings);
* obj->changeRating(food,newRating);
* string param_2 = obj->highestRated(cuisine);
*/

// DAY 18 (1913. Maximum Product Difference Between Two Pairs)=============================================================================================

int maxProductDifference(vector<int>& nums) 
{
    int max1 = INT_MIN;
    int max2 = INT_MIN;
    int min1 = INT_MAX;
    int min2 = INT_MAX;
    int size = nums.size();
    
    for(int num : nums)
    {
        if(num >= max1)
        {
            max2 = max1;
            max1 = num;
        }
        else max2 = max(max2, num);
        if(num <= min1)
        {
            min2 = min1;
            min1 = num;
        }
        else min2 = min(min2, num);
    }      
    return max1 * max2 - min1 * min2;
}

// DAY 19 (661. Image Smoother)===============================================================================================

vector<vector<int>> imageSmoother(vector<vector<int>>& img)
{
    int n = img.size(), m = img[0].size();
    vector<vector<int>> finalImage(n, vector<int>(m, 0));
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            int pixels = 1;
            pixels += i > 0;
            int top = i? img[i-1][j] : 0;
            pixels += n-i-1 > 0;
            int down = n-i-1? img[i+1][j] : 0;
            pixels += j > 0;
            int left = j? img[i][j-1] : 0;
            pixels += m-j-1 > 0;
            int right = m-j-1? img[i][j+1] : 0;
            pixels += i > 0 && j > 0;
            int topLeft = i && j? img[i-1][j-1] : 0;
            pixels += i > 0 && m-j-1 > 0;
            int topRight = i && m-j-1? img[i-1][j+1] : 0;
            pixels += n-i-1 > 0 && j > 0;
            int downLeft = n-i-1 && j? img[i+1][j-1] : 0;
            pixels += n-i-1 > 0 && m-j-1 > 0;
            int downRight = n-i-1 && m-j-1? img[i+1][j+1] : 0;
            
            finalImage[i][j] = (img[i][j] + top + down + left + right + topLeft + topRight + downLeft + downRight) / pixels;
        }
    }
    return finalImage;
}

// DAY 20 (2706. Buy Two Chocolates)==========================================================================

int buyChoco(vector<int>& prices, int money)
{
    int minPrice = INT_MAX, secondMinPrice = INT_MAX;
    for(int price : prices)
    {
        if(price <= minPrice)
        {
            secondMinPrice = minPrice;
            minPrice = price;
        }
        else secondMinPrice = min(secondMinPrice, price);
    }
    int totalMinPrice = minPrice + secondMinPrice;
    int moneySpent = totalMinPrice > money? money : money - totalMinPrice;
    
    return moneySpent;
}

// DAY 21 (1637. Widest Vertical Area Between Two Points Containing No Points)================================================================

int maxWidthOfVerticalArea(vector<vector<int>>& points) 
{
    sort(points.begin(), points.end());
    int size = points.size();
    int widestVerticalArea = 0;
    for(int index = 1; index < size; index++)
        widestVerticalArea = max(widestVerticalArea, points[index][0] - points[index-1][0]);
    return widestVerticalArea;
}

// DAY 22 (1422. Maximum Score After Splitting a String)==========================================================================================

int maxScore(string s) 
{
    int size = s.size();
    if(size < 2) return 0;

    int totalOnes = 0;
    for(char digit : s)
        totalOnes += digit == '1';
    int leftZeros = s[0] == '0';
    int rightOnes = totalOnes - (s[0] == '1');
    int maximumScore = 0;
    for(int index = 1; index < size; index++)
    {
        maximumScore = max(maximumScore, leftZeros + rightOnes);
        leftZeros += s[index] == '0';
        rightOnes -= s[index] == '1';
    }
    
    return maximumScore;
}

// DAY 23 (1496. Path Crossing)===============================================================================================================

bool isPathCrossing(string path)
{
    int verticalDistance = 0, horizontalDistance = 0;
    set<pair<int,int>> visitedPoints;
    visitedPoints.insert({0, 0});
    
    for(char direction : path)
    {
        if(direction == 'N' || direction == 'S')
            verticalDistance += direction == 'N'? 1 : -1;
        else
            horizontalDistance += direction == 'E'? 1 : -1;
    
        if(visitedPoints.count({horizontalDistance, verticalDistance}))
            return true;
        visitedPoints.insert({horizontalDistance, verticalDistance});
    }

    return false;
}

// DAY 24 (1758. Minimum Changes To Make Alternating Binary String)===================================================================================

int findCost(int start, string &bin)
{
    int cost = 0;
    for(int index = 0; index < bin.size(); index++)
    {
        cost += (bin[index]-'0') != start;
        start ^= 1;
    }
    return cost;
}

int minOperations(string s) 
{
    int cost01 = findCost(0, s);
    int cost10 = s.size() - cost01;
    return min(cost01, cost10);
}

// DAY 25 (91. Decode Ways)==========================================================================================================================

int numDecodings(string s)
{
    int size = s.size();
    vector<int> cache(size+1, 0);
    cache[size] = 1;
    for(int index = size-1; index >= 0; index--)
    {
        int singleDigit = s[index]-'0';
        if(singleDigit == 0)
        {
            cache[index] = 0;
            continue;
        }
        cache[index] = cache[index + 1];
        
        if(index+1 == size) continue;
        int doubleDigit = (s[index]-'0') * 10 + (s[index+1]-'0');
        if(doubleDigit <= 26)
            cache[index] += cache[index+2];
    }
    return cache[0];
}

// DAY 26 (1155. Number of Dice Rolls With Target Sum)==============================================================================================

const int MOD = 1e9 + 7;
int numRollsToTarget(int n, int k, int target) 
{
    if(target < n || target > n*k)
        return 0;

    vector<int> countCache(target+1, 0);
    countCache[0] = 1;
    for(int die = 1; die <= n; die++)
    {
        vector<int> nextCountCache(target+1, 0);
        for(int tar = 1; tar <= target; tar++)
        {
            if(die == 1)
            {
                if(tar <= k)
                    nextCountCache[tar] = 1;
                else break;
                continue;
            }
            for(int num = 1; num <= k && tar-num+1 >= die; num++)
            {
                int complement = tar - num;
                nextCountCache[tar] = (nextCountCache[tar] % MOD + countCache[complement] % MOD) % MOD;
            }
        }
        countCache = nextCountCache;
    }
    
    return countCache[target] % MOD;
}

// DAY 27 (1578. Minimum Time to Make Rope Colorful)===================================================================================

int minCost(string colors, vector<int>& neededTime) 
{
    int size = colors.size();
    int minimumTimeNeeded = 0;
    for(int left = 0; left < size; )
    {
        int right = left;
        int totalTime = 0, maxTime = 0;
        while(right < size && colors[right] == colors[left])
        {
            maxTime = max(maxTime, neededTime[right]);
            totalTime += neededTime[right++];
        }
        minimumTimeNeeded += totalTime - maxTime;
        left = right;
    }
    return minimumTimeNeeded;
}

// DAY 28 (1531. String Compression II)=======================================================================================

// APPROACH 1 (Either deleting or Choosing a character with storing previous character and its count) --> Time = O(n^3*k), Space = O(n^3*k)

int cache[101][101][101][27];

class Solution {
public:

    int getMinimumLengthDFS(int idx, char prevChar, int prevCnt, int k, string &s)
    {
        if(k < 0) return INT_MAX;
        if(idx == s.size()) return 0;
        if(cache[idx][prevCnt][k][prevChar-'a'] != -1)
            return cache[idx][prevCnt][k][prevChar-'a'];

        int deleteRes = getMinimumLengthDFS(idx+1, prevChar, prevCnt, k-1, s);
        int keepRes = INT_MAX;
        if(s[idx] == prevChar)
        {
            int increasedCount = (prevCnt == 1 || prevCnt == 9 || prevCnt == 99);
            keepRes = getMinimumLengthDFS(idx+1, prevChar, prevCnt+1, k, s) + increasedCount;
        }
        else keepRes = getMinimumLengthDFS(idx+1, s[idx], 1, k, s) + 1;

        return
         cache[idx][prevCnt][k][prevChar-'a'] = 
        min(deleteRes, keepRes);
    }

    int getLengthOfOptimalCompression(string s, int k)
    {
        int size = s.size();
        memset(cache, -1, sizeof(cache));
        return getMinimumLengthDFS(0, 'z'+1, 0, k, s);
    }
};

// APPROACH 2 (Either deleting or Looping for a particular character) --> Time = O(n*k), Space = O(n*k)

int cache[101][101];

class Solution {
public:

    int getMinimumLengthDFS(int itr1, int k, string &s)
    {
        if(k < 0) return INT_MAX;
        if(itr1 == s.size()) return 0;
        if(cache[itr1][k] != -1)
            return cache[itr1][k];

        int deleteRes = getMinimumLengthDFS(itr1+1, k-1, s);
        int keepRes = INT_MAX;
        int keepCnt = 0;
        int kTemp = k;
        
        for(int itr2 = itr1; itr2 < s.size(); itr2++)
        {
            if(s[itr2] == s[itr1])
                keepCnt++;
            else if(--kTemp < 0) break;
            int numCnt = (keepCnt > 99? 3 : (keepCnt > 9? 2 : (keepCnt > 1? 1 : 0)));
            
            keepRes = min(keepRes, getMinimumLengthDFS(itr2+1, kTemp, s) + numCnt + 1);
        }

        return cache[itr1][k] = min(deleteRes, keepRes);
    }

    int getLengthOfOptimalCompression(string s, int k)
    {
        int size = s.size();
        memset(cache, -1, sizeof(cache));
        return getMinimumLengthDFS(0, k, s);
    }
};

// DAY 29 (1335. Minimum Difficulty of a Job Schedule)============================================================================

// APPROACH 1 (DFS and memoization)
// Time = O(n^2 * d), Space = O(n*d)

int minDifficultyDFS(int idx1, int d, vector<int> &jobDiff, vector<vector<int>> &cache)
{
    if(idx1 == jobDiff.size())
        return d == 0? 0 : INT_MAX;
    if(d == 0) return INT_MAX;
    if(cache[idx1][d] != -1)
        return cache[idx1][d];

    int partitionRes = INT_MAX;
    int maxDiff = -1;
    for(int idx2 = idx1; idx2 < jobDiff.size(); idx2++)
    {
        maxDiff = max(maxDiff, jobDiff[idx2]);
        int nextParitionRes = minDifficultyDFS(idx2+1, d-1, jobDiff, cache);

        partitionRes = min(partitionRes, nextParitionRes == INT_MAX? INT_MAX : (nextParitionRes + maxDiff));
    }
    return cache[idx1][d] = partitionRes;
}

int minDifficulty(vector<int>& jobDifficulty, int d)
{
    int jobSize = jobDifficulty.size();
    vector<vector<int>> cache(jobSize, vector<int>(d+1, -1));
    int minAns = minDifficultyDFS(0, d, jobDifficulty, cache);
    return minAns == INT_MAX? -1 : minAns;
}

// APPROACH 2 (Tabulation with 1D DP)
// Time = O(n^2 * d), Space = O(n)

int minDifficulty(vector<int>& jobDifficulty, int d)
{
    int jobSize = jobDifficulty.size();

    if(jobSize < d)
        return -1;

    vector<int> cache(jobSize);
    cache[0] = jobDifficulty[0];
    int jobSum = jobDifficulty[0];
    for(int idx = 1; idx < jobSize; idx++)
    {
        cache[idx] = max(cache[idx-1], jobDifficulty[idx]);
        jobSum += jobDifficulty[idx];
    }
    if(jobSize == d)
        return jobSum;
    
    vector<int> prevCache = cache;
    for(int day = 2; day <= d; day++)
    {
        int threshold = day - 1;
        for(int idx1 = threshold; idx1 < jobSize; idx1++)
        {
            int maxDiff = INT_MIN;
            int minAns = INT_MAX;
            for(int idx2 = idx1; idx2 >= threshold; idx2--)
            {
                maxDiff = max(maxDiff, jobDifficulty[idx2]);
                minAns = min(minAns, maxDiff + prevCache[idx2-1]);
            }
            cache[idx1] = minAns;
        }
        prevCache = cache;
    }
    return cache[jobSize-1];
}

// DAY 30 (1897. Redistribute Characters to Make All Strings Equal)=============================================================================

bool makeEqual(vector<string>& words)
{
    int expectedOcc = words.size();
    vector<int> charFreq(26, 0);
    for(string word : words)
        for(char c : word)
            charFreq[c-'a']++;
    for(int i = 0; i < 26; i++)
        if(charFreq[i] % expectedOcc)
            return false;
    return true;
}

// DAY 31 (1624. Largest Substring Between Two Equal Characters)=====================================================================================

int maxLengthBetweenEqualCharacters(string &s)
{
    vector<int> firstOcc(26, -1);
    int maxLen = -1;
    for(int i = 0; i < s.size(); i++)
    {
        if(firstOcc[s[i]-'a'] != -1)
            maxLen = max(maxLen, i - firstOcc[s[i]-'a'] - 1);
        else
            firstOcc[s[i]-'a'] = i;
    }
    return maxLen;
}
