
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
