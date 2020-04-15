// ##  WEEK 1 ##

//day 1 (single number)================================================

int singleNumber(vector<int>& nums) 
{
    for(int i=1;i<nums.size();i++)
    {
        nums[0] ^= nums[i];
    }
    return nums[0];
}

//day 2 (happy number)==================================================

bool isHappy(int n) 
{
    int i = 0;
    while(i < 1000)
    {
        int num = 0;
        while(n != 0)
        {
            num += pow(n%10,2);
            n /= 10;
        }
        n = num;
        // cout<<num<<endl;
        if(num == 1)
            return true;
        i++;
    }
    return false;
}

//day 3 (maximum subarray)==========================================================

int maxSubArray(vector<int>& nums) 
{
    int sum = 0, maxsum = sum;
    
    int i=0,max=INT_MIN;
    while(nums[i] < 0 && i < nums.size())
    {
        if(nums[i] > max)
            max = nums[i];
        if(i == nums.size()-1)
            return max;
        i++;
    }
    
    for(;i<nums.size();i++)
    {
        sum += nums[i];
        if(sum < 0)
            sum = 0;
        else if(sum > maxsum)
            maxsum = sum;
    }
    return maxsum;
}

//day 4 (move zeroes)=====================================================================

void moveZeroes(vector<int>& nums) 
{
    for(int lastnonzeroFoundAt=0, itr=0; itr<nums.size();itr++)
        if(nums[itr] != 0)
            swap(nums[lastnonzeroFoundAt++],nums[itr]);
}

//day 5 (best time to buy and sell stock 2)==================================================

int maxProfit(vector<int>& prices) 
{
    if(prices.size() == 0)
        return 0;
    
    int profit = 0;
    for(int i=0;i<prices.size()-1;i++)
    {
        if(prices[i+1] > prices[i])
            profit += prices[i+1] - prices[i];
    }
    return profit;
}

//day 6 (group anagrams)====================================================================

vector<vector<string>> groupAnagrams(vector<string>& strs) 
{
    vector<vector<string>> output;
    map<string, vector<string>> dict;
    
    for(string s : strs)
    {
        string str = s;
        sort(str.begin(),str.end());
        dict[str].push_back(s);
    }
    
    for(auto i=dict.begin();i!=dict.end();i++)
    {
        output.push_back(i->second);
    }
    return output;
}

//day 7 (counting elements)======================================================================

int countElements(vector<int>& arr) 
{
    int count = 0;
    
    set<int> values;
    for(int ele : arr)
        values.insert(ele);
    
    for(int ele : arr)
    {
        if(values.find(ele+1) != values.end())
            count++;
    }
    
    return count;
}

// ## WEEK 2 ##

//day 8 (middle of the linked list)=================================================================

ListNode* middleNode(ListNode* head) 
{
    ListNode* slow = head;    
    ListNode* fast = head;
    
    while(fast != nullptr && fast->next != nullptr)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

