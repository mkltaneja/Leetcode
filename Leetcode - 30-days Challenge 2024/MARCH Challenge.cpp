
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

// DAY 11 (791. Custom Sort String)==================================================================================

// Time Complexity = O(n + m)
// Space Complexity = O(1)

string customSortString(string order, string s)
{
	vector<int> charMap(26, 0);
	for(char c : s)
		charMap[c-'a']++;
	
	int idx = 0;
	for(char c : order)
		while(charMap[c-'a']--)
			s[idx++] = c;

	for(int cIdx = 0; cIdx < 26; cIdx++)
		while(charMap[cIdx]-- > 0)
			s[idx++] = char(cIdx + 'a');

	return s;
}

// DAY 12 (1171. Remove Zero Sum Consecutive Nodes from Linked List)=====================================================

// Time Complexity = O(n^2)
// Space Complexity = O(n)

public ListNode removeZeroSumSublists(ListNode head)
{
	ArrayList<Integer> nodes = new ArrayList<>();
	ListNode itr = head;
	ListNode newHead = new ListNode(-1), newItr = newHead;
	while(itr != null)
	{
		nodes.add(itr.val);
		itr = itr.next;
	}

	while(true)
	{
		Integer rangeMin = Integer.MAX_VALUE;
		Integer rangeMax = Integer.MIN_VALUE;
		Integer rangeSize = 0;
		Integer maxSize = 0;
		HashMap<Integer, Integer> minOcc = new HashMap<>();
		Integer prefSum = 0;
		minOcc.put(0, -1);

		for(int idx = 0; idx < nodes.size(); idx++)
		{
			prefSum += nodes.get(idx);
			if(!minOcc.containsKey(prefSum))
				minOcc.put(prefSum, idx);
			else
			{
				Integer newRangeSize = idx - minOcc.get(prefSum);
				if(newRangeSize > rangeSize)
				{
					rangeMin = minOcc.get(prefSum);
					rangeMax = idx;
					rangeSize = newRangeSize;
				}
			}
		}

		ArrayList<Integer> newNodes = new ArrayList<Integer>();
		if(rangeMax != Integer.MIN_VALUE)
		{
			for(int idx = 0; idx < nodes.size(); idx++)
			{
				if(idx > rangeMin && idx <= rangeMax)
					continue;
				newNodes.add(nodes.get(idx));
			}
			nodes = newNodes;
		}
		else break;
	}

	for(int idx = 0; idx < nodes.size(); idx++)
	{
		newItr.next = new ListNode(nodes.get(idx));
		newItr = newItr.next;
	}

	newHead = newHead.next;
	return newHead;
}

// APPROACH 2 [OPTIMIZED]

// Time Complexity = O(n)
// Space Complexity = O(n)

public ListNode removeZeroSumSublists(ListNode head) 
{
	HashMap<Integer, ListNode> nodeMap = new HashMap<>();
	ListNode itr = head;
	ListNode newHead = new ListNode(0);
	nodeMap.put(0, newHead);
	newHead.next = head;
	int prefSum = 0;
	while(itr != null)
	{
		prefSum += itr.val;
		nodeMap.put(prefSum, itr);
		itr = itr.next;
	}

	itr = newHead;
	prefSum = 0;
	while(itr != null)
	{
		prefSum += itr.val;
		itr.next = nodeMap.get(prefSum).next;
		itr = itr.next;
	}

	newHead = newHead.next;
	return newHead;
}

// DAY 13 (2485. Find the Pivot Integer)===================================================================================

// Time Complexity = O(log n)
// Space Complexity = O(1)

int pivotInteger(int n) 
{
	int lo = 1, hi = n;
	while(lo <= hi)
	{
		int mid = (lo + hi) >> 1;
		int leftSum = mid * (mid + 1) >> 1;
		int rightSum = (n * (n + 1) >> 1) - leftSum + mid;
		if(leftSum == rightSum)
			return mid;
		if(leftSum < rightSum)
			lo = mid + 1;
		else hi = mid - 1;
	}
	return -1;
}

// DAY 14 (930. Binary Subarrays With Sum)==============================================================================

// APPROACH 1 (Using Queue and separately for 1 and 0)

// Time Complexity = O(n)
// Space Complexity = O(n)

int numSubarraysWithSum(vector<int>& nums, int goal) 
{
	int size = nums.size();
	int totalSubarrays = 0;
	if(goal)
	{
		int currSum = 0, prevZeros = 0;
		queue<int> que;
		for(int idx = 0; idx < size; idx++)
		{
			if(nums[idx])
			{
				que.push(prevZeros);
				prevZeros = 0;
			}
			else
				prevZeros++;
			
			currSum += nums[idx];
			if(currSum > goal)
			{
				currSum--;
				que.pop();
			}
			if(currSum == goal)
				totalSubarrays += que.front() + 1;
		}
	}
	else
	{
		int totalZeros = 0;
		for(int num : nums)
		{
			if(num)
				totalZeros = 0;
			else totalZeros++;
			totalSubarrays += totalZeros;
		}
	}

	return totalSubarrays;
}

// APPROACH 2 (Within a single loop)

// Time Complexity = O(n)
// Space Complexity = O(1)

int numSubarraysWithSum(vector<int>& nums, int goal) 
{
	int size = nums.size();
	int currSum = 0, prefZeros = 0, totalSubarrays = 0;
	for(int left = 0, right = 0; right < size; right++)
	{
		currSum += nums[right];
		while(left < right && (nums[left] == 0 || currSum > goal))
		{
			if(nums[left])
				prefZeros = 0;
			else prefZeros++;

			currSum -= nums[left++];
		}

		if(currSum == goal)
			totalSubarrays += prefZeros + 1;
	}

	return totalSubarrays;
}

// DAY 15 (238. Product of Array Except Self)========================================================================================

// Time Complexity = O(2*n)
// Space Complexity = O(n)

vector<int> productExceptSelf(vector<int>& nums) 
{
	int size = nums.size();
	vector<int> answer(size);
	int multRes = 1;
	for(int idx = 0; idx < size; idx++)
	{
		answer[idx] = multRes;
		multRes *= nums[idx];
	}
	multRes = 1;
	for(int idx = size-1; idx >= 0; idx--)
	{
		answer[idx] *= multRes;
		multRes *= nums[idx];
	}

	return answer;
}

// DAY 16 (525. Contiguous Array)=================================================================

// Time Complexity = O(n)
// Space Complexity = O(2*n)

int findMaxLength(vector<int>& nums) 
{
	int size = nums.size(), start = size;
	vector<int> minOcc(2*size + 1, -2); // -2 = not yet encountered
	int maxLen = 0;
	minOcc[start] = -1;
	for(int idx = 0; idx < size; idx++)
	{
		start += nums[idx]? 1 : -1;
		if(minOcc[start] != -2)
			maxLen = max(maxLen, idx - minOcc[start]);
		else
			minOcc[start] = idx;
	}

	return maxLen;
}

// DAY 17 (57. Insert Interval)===================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

bool doesLieBetween(int newStart, int newEnd, int idx, vector<vector<int>>& intervals)
{
	return (idx && newStart > intervals[idx-1][1] && newEnd < intervals[idx][0]);
}

vector<vector<int>> insert(vector<vector<int>>& intervals, vector<int>& newInterval) 
{
	int totalIntervals = intervals.size();
	vector<vector<int>> newIntervals;
	int newStart = newInterval[0], newEnd = newInterval[1];
	bool toBeInserted = totalIntervals == 0 || newEnd < intervals[0][0];
	bool isInserted = false;
	
	for(int idx = 0; idx < totalIntervals; idx++)
	{
		int start = intervals[idx][0], end = intervals[idx][1];
		if(newStart > end || newEnd < start) // doesn't overlap
		{
			if(toBeInserted || doesLieBetween(newStart, newEnd, idx, intervals))
			{
				newIntervals.push_back({newStart, newEnd});
				toBeInserted = false;
				isInserted = true;
			}
			newIntervals.push_back(intervals[idx]);
		}
		else // overlaps
		{
			newStart = min(newStart, start);
			newEnd = max(newEnd, end);
			toBeInserted = true;
		}
	}
	if(!isInserted)
		newIntervals.push_back({newStart, newEnd});

	return newIntervals;
}

// DAY 18 (452. Minimum Number of Arrows to Burst Balloons)==============================================================================

// Time Complexity = O(n*logn + n)
// Space Complexity = O(1)

int findMinArrowShots(vector<vector<int>>& points) 
{
	int size = points.size();
	int totalArrows = 0;
	sort(points.begin(), points.end());
	for(int idx = 0; idx < size; )
	{
		int currStart = points[idx][0], currEnd = points[idx][1];
		while(idx < size && points[idx][0] <= currEnd)
			currEnd = min(currEnd, points[idx++][1]);
		totalArrows++;
	}
	return totalArrows;
}
