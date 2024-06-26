
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

// DAY 19 (621. Task Scheduler)===========================================================================================

// APPROACH 1 (Solved using Priority Queue)

// Time Complexity = O(n + 26*log(26) + n*log(26))
// Space Complexity = O(26 + n)

int leastInterval(vector<char>& tasks, int n) 
{
	int minIntervals = 0;
	vector<int> countMap(26, 0);
	priority_queue<int> countPq;
	for(char c : tasks)
		countMap[c-'A']++;
	
	for(int c = 0; c < 26; c++)
		if(countMap[c])
			countPq.push(countMap[c]);

	while(!countPq.empty())
	{
		int intervalSize = n + 1;
		priority_queue<int> tempPq;
		while(intervalSize--)
		{
			if(!countPq.empty())
			{
				int topCount = countPq.top();
				countPq.pop();
				if(topCount - 1)
					tempPq.push(topCount-1);
				minIntervals++;
			}
			else
			{
				if(!tempPq.empty())
					minIntervals += intervalSize + 1;
				break;
			}
		}
		while(!tempPq.empty())
		{
			countPq.push(tempPq.top());
			tempPq.pop();
		}
	}
	return minIntervals;
}

// APPROACH 2 (Solved Mathematically) [OPTIMIZED]

// Time Complexity = O(n + 26)
// Space Complexity = O(26)

int leastInterval(vector<char>& tasks, int n) 
{
	int totalTasks = tasks.size();
	vector<int> freqMap(26, 0);
	int maxFreq = 0, maxFreqCount = 0;
	for(char c : tasks)
		freqMap[c-'A']++;
	for(int freq : freqMap)
	{
		if(freq > maxFreq)
			maxFreq = freq, maxFreqCount = 1;
		else if(freq == maxFreq) maxFreqCount++;
	}

	int gaps = maxFreq - 1;
	int gapSize = n - (maxFreqCount - 1);
	int availSlots = gapSize * gaps;
	int availTasks = totalTasks - maxFreq * maxFreqCount;
	int idles = max(0, availSlots - availTasks);
	int minIntervals = totalTasks + idles;

	return minIntervals;
}

// DAY 20 (1669. Merge In Between Linked Lists)==================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

ListNode* getListTail(ListNode* list)
{
	ListNode* itr = list, *tail = list;
	while(itr)
	{
		tail = itr;
		itr = itr->next;
	}
	return tail;
}

ListNode* mergeInBetween(ListNode* list1, int a, int b, ListNode* list2) 
{
	ListNode* list2Tail = getListTail(list2);
	ListNode* node1 = nullptr, *node2 = nullptr;
	ListNode* itr = list1;
	for(int idx = 0; idx <= b+1 && itr; idx++)
	{
		if(idx == a-1)
			node1 = itr;
		else if(idx == b+1)
			node2 = itr;
		itr = itr->next;
	}
	if(node1) node1->next = list2;
	if(list2Tail) list2Tail->next = node2;

	return list1;
}

// DAY 21 (206. Reverse Linked List)===========================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

ListNode* reverseList(ListNode* head) 
{
	ListNode* curr = head, *prev = nullptr;
	while(curr)
	{
		ListNode* next = curr->next;
		curr->next = prev;
		prev = curr;
		curr = next;
	}
	return prev;
}

// DAY 22 (234. Palindrome Linked List)=======================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

ListNode* getMidNode(ListNode* head)
{
	ListNode* slow = head, *fast = head;
	while(fast && fast->next)
	{
		slow = slow->next;
		fast = fast->next->next;
	}
	return slow;
}

ListNode* reverseSecondHalfAndGetHead(ListNode* node)
{
	ListNode* curr = node, *prev = nullptr;
	while(curr)
	{
		ListNode* forw = curr->next;
		curr->next = prev;
		prev = curr;
		curr = forw;
	}
	return prev;
}

bool isPalindrome(ListNode* head) 
{
	ListNode* midNode = getMidNode(head);
	ListNode* head2 = reverseSecondHalfAndGetHead(midNode);
	
	ListNode* itr1 = head, *itr2 = head2;
	while(itr1 && itr2)
	{
		if(itr1->val != itr2->val)
			return false;
		itr1 = itr1->next;
		itr2 = itr2->next;
	}
	return true;
}

// DAY 23 (143. Reorder List)========================================================================================================

ListNode* getMidNode(ListNode* head)
{
	ListNode* slow = head, *fast = head, *midNode = nullptr;
	while(fast->next && fast->next->next)
	{
		fast = fast->next->next;
		slow = slow->next;
	}
	midNode = slow->next;
	slow->next = nullptr;
	return midNode;
}

ListNode* reverseSecondHalfAndGetHead(ListNode* head)
{
	ListNode* curr = head, *prev = nullptr;
	while(curr)
	{
		ListNode* forw = curr->next;
		curr->next = prev;
		prev = curr;
		curr = forw;
	}
	return prev;
}

void reorderList(ListNode* head) 
{
	if(!head || !head->next || !head->next->next)
		return;
	ListNode* midNode = getMidNode(head);
	ListNode* head2 = reverseSecondHalfAndGetHead(midNode);
	ListNode* itr1 = head, *itr2 = head2, *tail = head;
	while(itr1 && itr2)
	{
		tail = itr2;
		ListNode* next1 = itr1->next, *next2 = itr2->next;
		itr1->next = itr2;
		itr2->next = next1;
		itr1 = next1;
		itr2 = next2;
	}
	if(itr1) tail->next = itr1;
}

// DAY 24 (287. Find the Duplicate Number)========================================================================================

// Time Complexity  O(n)
// Space Complexity  O(1)

int findDuplicate(vector<int>& nums) 
{
	int slow = 0, fast = 0;
	while(true)
	{
		slow = nums[slow];
		fast = nums[nums[fast]];
		if(slow == fast) break;
	}

	slow = 0;
	while(slow != fast)
	{
		slow = nums[slow];
		fast = nums[fast];
	}
	return slow;
}

// DAY 25 (442. Find All Duplicates in an Array)======================================================================================

// Time Compolexity = O(n)
// Space Compolexity = O(1)

vector<int> findDuplicates(vector<int>& nums) 
{
	vector<int> ans;
	for(int num : nums)
	{
		if(nums[abs(num)-1] < 0)
			ans.push_back(abs(num));
		nums[abs(num)-1] *= -1;
	}
	return ans;
}

// DAY 26 (41. First Missing Positive)=========================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int firstMissingPositive(vector<int>& nums) 
{
	int last = nums.size();
	for(int idx = 0; idx < last; idx++)
		while(nums[idx] >= 1 && nums[idx] <= last && nums[idx] != nums[nums[idx]-1])
			swap(nums[idx], nums[nums[idx]-1]);
	for(int idx = 0; idx < last; idx++)
		if(nums[idx] != idx+1)
			return idx + 1;
	return last+1;
}

// DAY 27 (713. Subarray Product Less Than K)=================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int numSubarrayProductLessThanK(vector<int>& nums, int k) 
{
	int size = nums.size();
	int ans = 0;
	for(int curr = 0, prev = 0, currProd = 1; curr < size; curr++)
	{
		currProd *= nums[curr];
		while(prev <= curr && currProd >= k)
			currProd /= nums[prev++];
		if(curr >= prev)
			ans += curr - prev + 1;
	}
	return ans;
}

// DAY 28 (2958. Length of Longest Subarray With at Most K Frequency)===========================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int maxSubarrayLength(vector<int>& nums, int k) 
{
	int maxLen = 0;
	unordered_map<int,int> numFreq;
	for(int curr = 0, prev = 0; curr < nums.size(); curr++)
	{
		numFreq[nums[curr]]++;
		while(numFreq[nums[curr]] > k)
			numFreq[nums[prev++]]--;
		maxLen = max(maxLen, curr - prev + 1);
	}

	return maxLen;
}

// DAY 29 (2962. Count Subarrays Where Max Element Appears at Least K Times)=====================================================================

// Time Complexity = O(2*n)
// Space Complexity = O(1)

long long countSubarrays(vector<int>& nums, int k) 
{
	int size = nums.size();
	if(k == 0)
		return (size * (size + 1)) / 2;
	
	int maxNum = *max_element(nums.begin(), nums.end());
	long long totalSubarrays = 0;

	for(int curr = 0, prev = 0, maxNumFreq = 0; curr < size; curr++)
	{
		maxNumFreq += nums[curr] == maxNum;
		while(maxNumFreq >= k)
			maxNumFreq -= nums[prev++] == maxNum;
		totalSubarrays += (long long)prev;
	}

	return totalSubarrays;
}

// DAY 30 (992. Subarrays with K Different Integers)============================================================================================

// Time Complexity = O(n)
// Space Complexity = O(n)

int subarraysWithKDistinct(vector<int>& nums, int k) 
{
	int ans = 0;
	unordered_map<int,int> numCount;
	for(int right = 0, left1 = 0, left2 = 0; right < nums.size(); right++)
	{
		numCount[nums[right]]++;
		while(numCount.size() > k)
		{
			if(--numCount[nums[left2]] == 0)
				numCount.erase(nums[left2]);
			left1 = ++left2;
		}
		while(numCount.size() == k && numCount[nums[left2]] > 1)
		{
			if(--numCount[nums[left2]] == 0)
				numCount.erase(nums[left2]);
			left2++;
		}
		if(numCount.size() == k)
			ans += left2 - left1 + 1;
	}

	return ans;
}

// DAY 31 (2444. Count Subarrays With Fixed Bounds)=================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

#define ll long long
long long countSubarrays(vector<int>& nums, int minK, int maxK) 
{
	ll subarrays = 0;
	for(int lastMinkIdx = -1, lastMaxkIdx = -1, start = -1, curr = 0; curr < nums.size(); curr++)
	{
		if(nums[curr] == minK)
			lastMinkIdx = curr;
		if(nums[curr] == maxK)
			lastMaxkIdx = curr;
		if(nums[curr] < minK || nums[curr] > maxK)
			lastMinkIdx = lastMaxkIdx = start = curr;
		
		int minLastIdx = min(lastMinkIdx, lastMaxkIdx);
		subarrays += (ll)minLastIdx - start;
	}

	return subarrays;
}
