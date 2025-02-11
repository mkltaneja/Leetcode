
// DAY 1 (3151. Special Array I)==========================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

bool isArraySpecial(vector<int>& nums) {
    for(int idx = 0; idx < nums.size()-1; idx++) {
        if((nums[idx] + nums[idx+1]) & 1 ^ 1) {
            return false;
        }
    }
    return true;
}

// DAY 2 (1752. Check if Array Is Sorted and Rotated)======================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

bool check(vector<int>& nums) {
    int size = nums.size();
    int partitionCount = 0;
    for(int idx = 0; idx < size; idx++) {
        if(nums[idx] > nums[(idx+1) % size]) {
            partitionCount++;
        }
    }
    return partitionCount < 2;
}

// DAY 3 (3105. Longest Strictly Increasing or Strictly Decreasing Subarray)==============================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int largestIncreasingOrDecreasingSubarray(vector<int> &nums, int size, bool checkForIncreasing) {
    int largestSubarray = 0;
    for(int curr = 0; curr < size; ) {
        int forw = curr + 1;
        while(forw < size && (checkForIncreasing? nums[forw] > nums[forw-1] : nums[forw] < nums[forw-1])) {
            forw++;
        }
        largestSubarray = max(largestSubarray, forw - curr);
        curr = forw;
    }
    return largestSubarray;
}

int longestMonotonicSubarray(vector<int>& nums) {
    int size = nums.size();
    int largestIncreasingSubarray = largestIncreasingOrDecreasingSubarray(nums, size, true);
    int largestDecreasingSubarray = largestIncreasingOrDecreasingSubarray(nums, size, false);
    return max(largestIncreasingSubarray, largestDecreasingSubarray);
}

// DAY 4 (1800. Maximum Ascending Subarray Sum)========================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int maxAscendingSum(vector<int>& nums) {
    int size = nums.size();
    int maxSum = 0;
    for(int curr = 0; curr < size; ) {
        int forw = curr + 1;
        int currSum = nums[curr];
        while(forw < size && nums[forw] > nums[forw-1]) {
            currSum += nums[forw++];
        }
        maxSum = max(maxSum, currSum);
        curr = forw;
    }
    return maxSum;
}

// DAY 5 (1790. Check if One String Swap Can Make Strings Equal)==================================================================

// time Complexity = O(n)
// Space Complexity = O(1)

bool areAlmostEqual(string s1, string s2) {
    int invalidIdx1 = -1, invalidIdx2 = -1;
    for(int idx = 0; idx < s1.size(); idx++) {
        if(s1[idx] != s2[idx]) {
            if(invalidIdx1 == -1) {
                invalidIdx1 = idx;
            }
            else if(invalidIdx2 == -1) {
                invalidIdx2 = idx;
            }
            else {
                return false;
            }
        }
    }
    if(invalidIdx1 != -1) {
        if(invalidIdx2 == -1) {
            return false;
        }
        swap(s1[invalidIdx1], s1[invalidIdx2]);
    }

    return s1 == s2;
}

// DAY 6 (1726. Tuple with Same Product)==============================================================================

// Time Complexity = O(n^2)
// Space Complexity = O(n^2)

int tupleSameProduct(vector<int>& nums) {
    int tuples = 0;
    int size = nums.size();
    unordered_map<int,int> prodCount;
    for(int idx1 = 0; idx1 < size; idx1++) {
        for(int idx2 = idx1+1; idx2 < size; idx2++) {
            int prod = nums[idx1] * nums[idx2];
            prodCount[prod]++;
        }
    }
    for(auto pc : prodCount) {
        int pairs = pc.second;
        tuples += pairs * (pairs - 1) / 2; // nC2
    }
    return 8 * tuples;
}

// DAY 7 (3160. Find the Number of Distinct Colors Among the Balls)==========================================================

// Time Complexity = O(q)
// Space Complexity = O(q)

vector<int> queryResults(int limit, vector<vector<int>>& queries) {
    unordered_map<int,int> color;
    vector<int> ans;
    unordered_map<int,int> colorCnt;
    for(vector<int> &query : queries) {
        int currentColor = color[query[0]];
        int newColor = query[1];
        if(currentColor && --colorCnt[currentColor] == 0) {
            colorCnt.erase(currentColor);
        }
        colorCnt[newColor]++;
        color[query[0]] = newColor;
        ans.push_back(colorCnt.size());
    }
    return ans;
}

// DAY 8 (2349. Design a Number Container System)=============================================================

// APPROACH 1 (Using Map of Set)

// Time Complexity = O(q*logq)
// Space Complexity = O(q)

class NumberContainers {
public:

    unordered_map<int,int> idxNum;
    unordered_map<int,set<int>> numIdx;
    NumberContainers() {
        
    }
    
    void change(int index, int number) {
        numIdx[idxNum[index]].erase(index);
        numIdx[number].insert(index);
        idxNum[index] = number;
    }
    
    int find(int number) {
        return numIdx[number].empty()? -1 : *numIdx[number].begin();
    }
};

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */

// APPROACH 2 (Using Map of Min Heap)

// Time Complexity = O(q*logq)
// Space Complexity = O(q)

class NumberContainers {
public:

    unordered_map<int,int> idxNum;
    unordered_map<int,priority_queue<int, vector<int>, greater<int>>> numIdx;
    NumberContainers() {
        
    }
    
    void change(int index, int number) {
        numIdx[number].push(index);
        idxNum[index] = number;
    }
    
    int find(int number) {
        priority_queue<int, vector<int>, greater<int>> &minPq = numIdx[number];
        while(!minPq.empty() && idxNum[minPq.top()] != number) {
            minPq.pop();
        }
        return minPq.empty()? -1 : minPq.top();
    }
};

/**
 * Your NumberContainers object will be instantiated and called as such:
 * NumberContainers* obj = new NumberContainers();
 * obj->change(index,number);
 * int param_2 = obj->find(number);
 */

// DAY 9 (2364. Count Number of Bad Pairs)===================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

long long countBadPairs(vector<int>& nums) {
    int size = nums.size();
    long long totalPairs = 0;
    unordered_map<int,int> diffCnt, pairCnt;
    for(int idx = size-1; idx >= 0; idx--) {
        int diff = idx - nums[idx];
        pairCnt[diff] += (size - idx - 1) - diffCnt[diff]++;
    }
    for(auto &pair : pairCnt) {
        totalPairs += pair.second;
    }

    return totalPairs;
}

// DAY 10 (3174. Clear Digits)========================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

string clearDigits(string s) {
    string ans = "";
    for(char c : s) {
        if(isdigit(c)) {
            if(!ans.empty()) {
                ans.pop_back();
            }
        }
        else {
            ans += c;
        }
    }
    return ans;
}

// DAY 11 (1910. Remove All Occurrences of a Substring)===================================================

// METHOD 1 (Naive)

// Time Complexity = O(n*m)
// Space Complexity = O(n)

void removeSuffix(int size, string &ans) {
    while(size--) {
        ans.pop_back();
    }
}

string removeOccurrences(string s, string part) {
    int psize = part.size();
    string ans = "";
    for(char c : s) {
        ans += c;
        if(ans.size() >= psize && ans.substr(ans.size() - psize, psize) == part) {
            removeSuffix(psize, ans);
        }
    }
    return ans;
}

// METHOD 2 (More concise)

// Time Complexity = O(n*m)
// Space Complexity = O(n)

string removeOccurrences(string s, string part) {
    while(s.size() >= part.size() && s.find(part) != string::npos) {
        s.erase(s.find(part), part.size());
    }
    return s;
}
