
// DAY 1 (2864. Maximum Odd Binary Number)======================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

string maximumOddBinaryNumber(string s)
{
    int size = s.size();
    int lastOnePos = -1;
    for(int p1 = 0, p2 = 0; p1 < size; p1++)
    {
        if(s[p1] == '1')
        {
            lastOnePos = p2;
            swap(s[p1], s[p2++]);
        }
    }
    if(lastOnePos != -1)
        swap(s[lastOnePos], s[size-1]);
    return s;
}

// DAY 2 (977. Squares of a Sorted Array)=============================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

vector<int> sortedSquares(vector<int> &nums)
{
    int size = nums.size();
    int positiveIdx = size-1, negativeIdx = 0, currentIdx = size-1;
    vector<int> squaredNums(size, 0);
    
    while(currentIdx >= 0)
    {
        if(abs(nums[positiveIdx]) > abs(nums[negativeIdx]))
            squaredNums[currentIdx--] = nums[positiveIdx] * nums[positiveIdx--];
       else squaredNums[currentIdx--] = nums[negativeIdx] * nums[negativeIdx++];
    }

    return squaredNums;
}

// DAY 3 (19. Remove Nth Node From End of List)=======================================================================================

// Time Complexity = O(2*n)
// Space Complexity = O(1)

int getSize(ListNode* head)
{
    int size = 0;
    ListNode* itr = head;
    while(itr)
    {
        itr = itr->next;
        size++;
    }
    return size;
}

ListNode* getPreviousPointer(ListNode* head, int targetPos)
{
    ListNode* itr = head, *prev = nullptr;
    while(targetPos--)
    {
        prev = itr;
        itr = itr->next;
    }
    return prev;
}

ListNode* removeNthFromEnd(ListNode* head, int n)
{
    int listSize = getSize(head);
    int targetPos = listSize - n;

    ListNode* prevNode = getPreviousPointer(head, targetPos);

    ListNode* nodeToRemove = nullptr;
    if(prevNode == nullptr)
    {
        nodeToRemove = head;
        head = head->next;
    }
    else 
    {
        nodeToRemove = prevNode->next;
        prevNode->next = nodeToRemove->next;
    }
    
    delete nodeToRemove;

    return head;
}

// DAY 4 (948. Bag of Tokens)===========================================================================================

// Time Complexity = O(n*logn + n)
// Space Complexity = O(1)

int bagOfTokensScore(vector<int> &tokens, int power)
{
    int size = tokens.size();
    sort(tokens.begin(), tokens.end());
    int start = 0, end = size-1;
    int score = 0, maxScore = 0;
    while(start <= end)
    {
        if(power >= tokens[start])
        {
            power -= tokens[start++];
            score++;
        }
        else if(score)
        {
            power += tokens[end--];
            score--;
        }
        else break;
        maxScore = max(maxScore, score);
    }
    return maxScore;
}

// DAY 5 (1750. Minimum Length of String After Deleting Similar Ends)===============================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int minimumLength(string s)
{
    int size = s.size();
    int idx1 = 0, idx2 = size-1;
    int minLen = size;
    while(true)
    {
        if(idx1 >= idx2 || s[idx1] != s[idx2])
        {
            minLen = idx2 - idx1 + 1;
            break;
        }

        int itr1 = idx1, itr2 = idx2;
        while(itr1 <= itr2 && s[itr1] == s[idx1])
            itr1++;
        while(itr2 >= itr1 && s[itr2] == s[idx2])
            itr2--;

        idx1 = itr1, idx2 = itr2;
    }
    return minLen;
}

// DAY 6 (141. Linked List Cycle)======================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

bool hasCycle(ListNode* head)
{
    ListNode* fast = head, *slow = head;
    while(fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
        if(fast == slow)
            return true;
    }

    return false;
}

// DAY 7 (876. Middle of the Linked List)===========================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

ListNode* middleNode(ListNode* head)
{
    ListNode* fast = head, *slow = head;
    while(fast && fast->next)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}

// DAY 8 (3005. Count Elements With Maximum Frequency)=============================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int maxFrequencyElements(vector<int> &nums)
{
	int maxFreq = 0, totalSum = 0;
	unordered_map<int, int> numFreq;

	for(int num : nums)
	{
		int freq = ++numFreq[num];
		if(freq > maxFreq)
		{
			maxFreq = freq;
			totalSum = freq;
		}
		else if(freq == maxFreq)
			totalSum += freq;
	}
	return totalSum;
}

// DAY 9 (2540. Minimum Common Value)======================================================================================

// Time Complexity = O(n + m)
// Space Complexity = O(1)

int getCommon(vector<int> &nums1, vector<int> &nums2)
{
	int itr1 = 0, itr2 = 0;
	int size1 = nums1.size(), size2 = nums2.size();
	while(itr1 != size1 && itr2 != size2)
	{
		if(nums1[itr1] == nums2[itr2])
			return nums1[itr1];
		if(nums1[itr1] < nums2[itr2])
			itr1++;
		else itr2++;
	}
	return -1;
}

// DAY 10 (349. Intersection of Two Arrays)=============================================================================

// Time Complexity = O(n + m)
// Space Complexity = O(min(n, m))

vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
{
	vector<int> common;
	unordered_set<int> numsSet;
	int size1 = nums1.size(), size2 = nums2.size();
	if(size2 < size1)
	{
		swap(nums1, nums2);
		swap(size1, size2);
	}

	for(int num : nums1)
		numsSet.insert(num);
	for(int num : nums2)
	{
		if(numsSet.count(num))
		{
			common.push_back(num);
			numsSet.erase(num);
		}
	}

	return common;
}
