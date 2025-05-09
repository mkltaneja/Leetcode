
// DAY 2 (838. Push Dominoes)==============================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

void fillDominoes(char op, int st, int end, string &dominoes) {
    for(int idx = st; idx <= end; idx++) {
        dominoes[idx] = op;
    }
}

string pushDominoes(string dominoes) {
    int size = dominoes.size();
    char prevOp = '#';
    for(int idx = 0; idx < size; idx++) {
        if(dominoes[idx] == '.') {
            int tempItr = idx;
            while(tempItr < size && dominoes[tempItr] == '.') {
                tempItr++;
            }
            char currOp = tempItr == size? '#' : dominoes[tempItr];
            if((prevOp == 'R' && currOp != 'L') || (prevOp != 'R' && currOp == 'L')) {
                char op = prevOp == 'R'? prevOp : currOp;
                fillDominoes(op, idx, tempItr-1, dominoes);
            }
            else if(prevOp == 'R' && currOp == 'L') {
                int intervalSize = tempItr-idx;
                int halfInterval = intervalSize/2;
                int st1 = idx, st2 = idx + halfInterval + (intervalSize & 1);
                int end1 = st1 + halfInterval - 1, end2 = st2 + halfInterval - 1;
                fillDominoes('R', st1, end1, dominoes);
                fillDominoes('L', st2, end2, dominoes);
            }
            idx = tempItr;
            prevOp = currOp;
        } else {
            prevOp = dominoes[idx];
        }
    }
    return dominoes;
}

// DAY 4 (1128. Number of Equivalent Domino Pairs)=======================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

int numEquivDominoPairs(vector<vector<int>>& dominoes) {
    vector<vector<int>> dominoPair(10, vector<int>(10, 0));
    int pairCount = 0;
    for(vector<int> &domino : dominoes) {
        int minVal = min(domino[0], domino[1]);
        int maxVal = max(domino[0], domino[1]);
        if(dominoPair[minVal][maxVal]) {
            pairCount += dominoPair[minVal][maxVal];
        }
        dominoPair[minVal][maxVal]++;
    }
    return pairCount;
}

// DAY 6 (1920. Build Array from Permutation)================================================================================

// Time Complexity = O(n)
// Space Complexity = O(1)

vector<int> buildArray(vector<int>& nums) {
    int size = nums.size();
    vector<int> ans(size);
    for(int idx = 0; idx < size; idx++) {
        ans[idx] = nums[nums[idx]];
    }
    return ans;
}

// DAY 7 (3341. Find Minimum Time to Reach Last Room I)===========================================================================

// Time Complexity = O(n^2 * logn)
// Space Complexity = O(n^2)

int minTimeToReach(vector<vector<int>>& moveTime) {
    int rows = moveTime.size(), cols = moveTime[0].size();
    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    priority_queue<pair<int, pair<int,int>>, vector<pair<int, pair<int,int>>>, greater<pair<int, pair<int,int>>>> minPq;
    minPq.push({0, {0, 0}});
    moveTime[0][0] = -1;

    while(!minPq.empty()) {
        int ctime = minPq.top().first;
        int crow = minPq.top().second.first;
        int ccol = minPq.top().second.second;
        minPq.pop();

        for(int d = 0; d < 4; d++) {
            int nrow = crow + dir[d][0];
            int ncol = ccol + dir[d][1];
            if(nrow == -1 || ncol == -1 || nrow == rows || ncol == cols || moveTime[nrow][ncol] == -1) {
                continue;
            }
            int ntime = max(ctime + 1, moveTime[nrow][ncol] + 1);
            if(nrow == rows - 1 && ncol == cols - 1) {
                return ntime;
            }
            minPq.push({ntime, {nrow, ncol}});
            moveTime[nrow][ncol] = -1;
        }
    }
    return -1;
}

// DAY 8 (3342. Find Minimum Time to Reach Last Room II)================================================================================

// Time Complexity = O(n*m * log(n*m))
// Space Complexity = O(n*m)

int minTimeToReach(vector<vector<int>>& moveTime) {
    int rows = moveTime.size(), cols = moveTime[0].size();
    int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
    priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> minPq;
    minPq.push({0, 0, 0, 0});
    moveTime[0][0] = -1;
    while(!minPq.empty()) {
        int ctime = minPq.top()[0];
        int crow = minPq.top()[1];
        int ccol = minPq.top()[2];
        int cmove = minPq.top()[3];
        minPq.pop();

        for(int d = 0; d < 4; d++) {
            int nrow = crow + dir[d][0];
            int ncol = ccol + dir[d][1];
            int nmove = cmove ^ 1;
            if(nrow == -1 || ncol == -1 || nrow == rows || ncol == cols || moveTime[nrow][ncol] == -1) {
                continue;
            }
            int stepTime = (cmove & 1) + 1;
            int ntime = max(moveTime[nrow][ncol] + stepTime, ctime + stepTime);
            if(nrow == rows - 1 && ncol == cols - 1) {
                return ntime;
            }
            minPq.push({ntime, nrow, ncol, nmove});
            moveTime[nrow][ncol] = -1;
        }
    }
    return -1;
}
