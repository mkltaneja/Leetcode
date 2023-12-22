
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
