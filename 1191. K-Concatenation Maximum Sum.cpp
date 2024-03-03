
// Time Complexity = O(3*n)
// Space Complexity = O(3)

class Solution {
public:
    const int MOD = 1e9 + 7;

    int modAddition(int num1, int num2)
    {
        return ((long)(num1 % MOD) + (num2 % MOD)) % MOD;
    }

    int modMultiplication(int num1, int num2)
    {
        return ((long)(num1 % MOD) * (num2 % MOD)) % MOD;
    }

    int kedanesAlgorithm(vector<int> &arr, int times)
    {
        int size = arr.size();
        long currSum = 0, maxSum = LLONG_MIN;
        for(int idx = 0; idx < times*size; idx++)
        {
            int cidx = idx % size;
            int num = arr[cidx];

            currSum += num;
            maxSum = max(maxSum, currSum);
            if(currSum < 0) currSum = 0;
        }
        return maxSum % MOD;
    }

    int kConcatenationMaxSum(vector<int> &arr, int k)
    {
        int totalSum = 0;
        for(int num : arr)
            totalSum = modAddition(totalSum, num);

        int maxSumFor2Arrays = kedanesAlgorithm(arr, min(2, k));
        if(totalSum <= 0)
            return max(0, maxSumFor2Arrays);
        
        int restMaxSum = k > 2? (modMultiplication(totalSum, k - 2) % MOD) : 0;
        return modAddition(maxSumFor2Arrays, restMaxSum);
    }
};
