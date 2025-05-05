
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
