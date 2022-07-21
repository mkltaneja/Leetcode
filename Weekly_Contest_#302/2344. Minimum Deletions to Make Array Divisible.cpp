class Solution
{
public:
    int minOperations(vector<int> &nums, vector<int> &numsDivide)
    {
        int g = 0;
        for (int x : numsDivide)
            g = __gcd(x, g);

        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++)
            if (g % nums[i] == 0)
                return i;
        return -1;
    }
};

// [2,3,2,4,3]
// [9,6,9,3,15]
// [4,3,6]
// [8,2,6,10]
// [2,3,6]
// [9,6,12]
// [40,38,18,19,18,18,16]
// [430222122,345833946,609158196,173124594,25468560,990277596,295095510,354571344,931500936,636837210]
// [3,3,4]
// [232043928,756514768,302987820]